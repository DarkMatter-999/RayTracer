#version 440 core
out vec4 FragColor;
 
in vec4 vertexColor; 

uniform vec2 iResolution;
uniform vec3 position;
uniform vec2 dimension;
uniform vec2 delta;
uniform vec3 rotation;

mat4 m_Projection = mat4(1.0);
mat4 m_View = mat4(1.0);
mat4 m_InverseProjection = mat4(1.0);
mat4 m_InverseView = mat4(1.0);

float m_VerticalFOV = 45.0;
float m_NearClip = 0.1;
float m_FarClip = 100.0;
vec3 m_Position = position;
vec3 m_ForwardDirection = vec3(0.0, 0.0, 0.0);

struct Ray {
  vec3 Origin;
  vec3 Direction;
};
struct Material {
  vec3 Color;
  vec3 emissionColor;
  float emmisionStrength;
  float smoothness;
  vec3 specularColor;
  float specProb;
  float transparency;
  float refractiveIndex;
};

struct Sphere {
  vec3 position;
  float radius;
  Material material;
};

struct HitInfo {
  bool didHit;
  float dist;
  vec3 hitPoint;
  vec3 normal;
  Material material;
};

uint pcg_hash(inout uint inp);
float pcg_hash_to_float(inout uint inp);
float randomNormalDistribution(inout uint inp);
vec3 randomDirection(inout uint state);
vec3 randomHemisphereDirection(vec3 normal, inout uint state);

mat4 perspective(float fovy, float aspect, float near, float far);
mat4 lookAt(vec3 eye, vec3 at, vec3 up);
void RecalculateProjection();
mat4 translate(vec3 translation);
mat4 rotate(float angle, vec3 axis);
mat4 view(vec3 position, vec3 rotation);
void RecalculateView();
HitInfo RaySphere(Ray ray, vec3 spherePosition, float radius);
HitInfo CalculateRayCollision(Ray ray);
vec3 TraceRay(Ray ray, inout uint state);
vec3 RefractRay(vec3 incidentDir, vec3 normal, float refractiveIndex);

uniform int maxBounces;
uniform int raysPerPixel;
uniform int frameNo;
uniform float focus;
int NumSphere = 7;
Sphere Spheres[7] = Sphere[](// Position,Radius,DiffuseColor,EmmisionColor,EmmisionStrength,Smoothness,SpecularColor,SpecularProb,Transparency,RefractiveIndex
                            Sphere(vec3(1, -8, -3), 3, Material(vec3(1.0,1.0,1.0), vec3(1), 5, 1,vec3(1), 0, 0, 0)), // background light
                            Sphere(vec3(0, -2.5, 3), 2.85, Material(vec3(1.0,1.0,1.0), vec3(0), 0, 0.75, vec3(0), 0, 0, 0)), // ground
                            Sphere(vec3(-0.5, -2, 0), 0.25, Material(vec3(0.0,0.0,1.0), vec3(0), 0, 1, vec3(0,0,1), 1, 0, 0)),   // Blue
                            Sphere(vec3(-1, -2, 0), 0.25, Material(vec3(1.0,0.0,0.0), vec3(0), 0, 1, vec3(1), 0.15, 0, 0)), // Red
                            Sphere(vec3(-1.5, -2, 0), 0.25, Material(vec3(0.0,1.0,0.0), vec3(0), 0, 0, vec3(0), 0, 0, 0)), // Green
                            Sphere(vec3(0, -2, -0.0625), 0.25, Material(vec3(1.0,1.0,1.0), vec3(0), 0, 1, vec3(0), 0, 1, 2.4)),     // Glass
                            Sphere(vec3(1, 8, -3), 2, Material(vec3(1.0,0.85,0.15), vec3(1,0.85, 0.15), 2, 1,vec3(1), 0, 0, 0)) // foreground light
                            ); 

bool envEnable = true;
vec3 GroundColour = vec3(0.50, 0.49, 0.48);
vec3 SkyColourHorizon = vec3(0.760, 0.895, 0.99);
vec3 SkyColourZenith = vec3(0.550, 0.880, 1);
vec3 SunDirection = vec3(0, 1.0, 0);
float SunFocus = 0.75;
float SunIntensity = 0.1;

float AirRefractiveIndex = 1.0;

float focusSensitivity = 1000;

vec3 Envirnoment(Ray ray) {
  float skyGradientT = pow(smoothstep(0, 0.4, ray.Direction.y), 0.35);
  vec3 skyGradient = mix(SkyColourHorizon, SkyColourZenith, skyGradientT);
  float sun = pow(max(0, dot(ray.Direction, -SunDirection)), SunFocus) * SunIntensity;
  // Combine ground, sky, and sun
  float groundToSkyT = smoothstep(-0.01, 0, ray.Direction.y);
  vec3 composite = mix(GroundColour, skyGradient, groundToSkyT) + sun * float(groundToSkyT>=1);
  return composite;
}

void main()
{
    RecalculateProjection();
    RecalculateView();
    //vec3 lightDir = normalize(vec3(-1));
    //vec3 normal = normalize(h1);
    //float d = max(dot(normal, -lightDir) ,0);
    //  s1.material.Color *= d;
    //color = s1.material.Color;

    vec2 coord = (gl_FragCoord.xy / iResolution) * 2.0 - 1.0;
    vec4 target = m_InverseProjection * vec4(coord.x, coord.y, 1, 1);

    // ray.Direction = normalize( - ray.Origin);
    uint pixelIndex = uint(gl_FragCoord.y * dimension.x) + uint(gl_FragCoord.x) * uint(frameNo);

    vec3 totalLight = vec3(0);

    for(int i=0; i < raysPerPixel; i++) {
      Ray ray = Ray(position, vec3(0));
      ray.Direction = vec3(m_InverseView * vec4(normalize(vec3(target) / target.w), 0)) - randomDirection(pixelIndex) * (focus/focusSensitivity); // World space  
      totalLight += TraceRay(ray, pixelIndex);
    }

    vec3 pixelColor = totalLight / raysPerPixel;
    FragColor = vec4(pixelColor, 1.0);
}

mat4 perspective(float fovy, float aspect, float near, float far) {
  float f = 1.0 / tan(fovy / 2.0);
  float rangeInv = 1.0 / (near - far);

  return mat4(
    f / aspect, 0.0,                 0.0,                           0.0,
    0.0,        f,                   0.0,                           0.0,
    0.0,        0.0,  (near + far) * rangeInv,   2.0 * near * far * rangeInv,
    0.0,        0.0,                -1.0,                           0.0
  );
}

mat4 lookAt(vec3 eye, vec3 at, vec3 up)
{
  vec3 zaxis = normalize(at - eye);    
  vec3 xaxis = normalize(cross(zaxis, up));
  vec3 yaxis = cross(xaxis, zaxis);

  zaxis = -zaxis;

  mat4 viewMatrix = {
    vec4(xaxis.x, xaxis.y, xaxis.z, -dot(xaxis, eye)),
    vec4(yaxis.x, yaxis.y, yaxis.z, -dot(yaxis, eye)),
    vec4(zaxis.x, zaxis.y, zaxis.z, -dot(zaxis, eye)),
    vec4(0, 0, 0, 1)
  };

  return viewMatrix;
}

void RecalculateProjection()
{
	m_Projection = perspective(m_VerticalFOV,dimension.x / dimension.y, m_NearClip, m_FarClip);
	m_InverseProjection = inverse(m_Projection);
}

mat4 translate(vec3 translation) {
    mat4 res = mat4(1.0);
    res[3][0] = translation.x;
    res[3][1] = translation.y;
    res[3][2] = translation.z;
    
    return res;
}

mat4 rotate(float angle, vec3 axis) {
    mat4 result = mat4(1.0);
    
    float cos = cos(radians(angle));
    float sin = sin(radians(angle));
    float C = 1.0 - cos;
    
    result[0][0] = cos + axis.x * axis.x * C;
    result[0][1] = axis.x * axis.y * C - axis.z * sin;
    result[0][2] = axis.x * axis.z * C + axis.y * sin;
    result[1][0] = axis.y * axis.x * C + axis.z * sin;
    result[1][1] = cos + axis.y * axis.y * C;
    result[1][2] = axis.y * axis.z * C - axis.x * sin;
    result[2][0] = axis.z * axis.x * C - axis.y * sin;
    result[2][1] = axis.z * axis.y * C + axis.x * sin;
    result[2][2] = cos + axis.z * axis.z * C;
    
    return result;
}

mat4 view(vec3 position, vec3 rotation) {
		mat4 result = mat4(1.0);
		
		vec3 negposition = -position;

		mat4 translationMatrix = translate(negposition);
		mat4 rotXMatrix = rotate(rotation.x, vec3(1, 0, 0));
		mat4 rotYMatrix = rotate(rotation.y, vec3(0, 1, 0));
		mat4 rotZMatrix = rotate(rotation.z, vec3(0, 0, 1));
		
		mat4 rotationMatrix = rotYMatrix * (rotZMatrix * rotXMatrix);

		result = translationMatrix * rotationMatrix;
		
		return result;
	}

void RecalculateView()
{
  m_View = view(position, rotation);
  m_InverseView = inverse(m_View);
}

HitInfo RaySphere(Ray ray, vec3 spherePosition, float radius) { 
  HitInfo rayHit = HitInfo(false, 0, vec3(0), vec3(0), Material(vec3(0), vec3(0), 0, 0, vec3(0), 0, 0, 0));
  vec3 rayOriginOffset = ray.Origin - spherePosition;

  float a = dot(ray.Direction, ray.Direction);
  float b = 2.0 * dot(rayOriginOffset, ray.Direction);
  float c = dot(rayOriginOffset, rayOriginOffset) - radius * radius;

  float D = b*b - 4.0*a*c;

  if (D >= 0.0) { 
      float dist = (-b - sqrt(D)) / (2.0 * a);

      if(dist >= 0) {
        rayHit.didHit = true;
        rayHit.dist = dist;
        rayHit.hitPoint = ray.Origin + ray.Direction * dist;
        rayHit.normal = normalize(rayHit.hitPoint - spherePosition);
      }
  }

  return rayHit;
}

HitInfo CalculateRayCollision(Ray ray) {
  HitInfo closestHit = HitInfo(false, 0, vec3(0), vec3(0), Material(vec3(0), vec3(0), 0, 0, vec3(0), 0, 0, 0));

  closestHit.dist = 1000000.0;

  for(int i = 0; i < NumSphere; i++) {
    Sphere s = Spheres[i];
    HitInfo hit = RaySphere(ray, s.position, s.radius);

    if(hit.didHit && hit.dist < closestHit.dist) {
      closestHit = hit;
      closestHit.material = s.material;
    }
  }
  return closestHit;
}


uint pcg_hash(inout uint state) {
    state = state * 747796405u + 2891336453u;
    uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

float pcg_hash_to_float(inout uint state) {
    state = state * 747796405u + 2891336453u;
    uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    uint hash_value = (word >> 22u) ^ word;
    float random_float = float(hash_value) / 4294967296.0;
    return random_float;
}

float randomNormalDistribution(inout uint inp) {
    float theta = 2.0 * 3.1415926 * pcg_hash_to_float(inp);
    float rho = sqrt(-2 * log(pcg_hash_to_float(inp)));
    return rho * cos(theta);
}

vec3 randomDirection(inout uint state) {
    float x = randomNormalDistribution(state);
    float y = randomNormalDistribution(state);
    float z = randomNormalDistribution(state);

    return vec3(normalize(vec3(x, y, z)));
} 

vec3 randomHemisphereDirection(vec3 normal, inout uint state) {
    float u = pcg_hash_to_float(state);
    float v = pcg_hash_to_float(state);
    float theta = 2 * 3.1415629 * u;
    float phi = acos(2 * v - 1);
    vec3 dir = vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
    dir *= sign(dot(normal, dir));
    return dir;
}

vec3 RefractRay(vec3 incidentDir, vec3 normal, float refractiveIndex, inout uint state) {
  float cosTheta1 = dot(incidentDir, normal);
  float eta;

  if (cosTheta1 < 0) {
    // Entering the medium
    eta = AirRefractiveIndex / refractiveIndex;
    cosTheta1 = -cosTheta1;
  } else {
    // Exiting the medium
    eta = refractiveIndex;
    normal = -normal;
  }

  float k = 1.0 - eta * eta * (1.0 - cosTheta1 * cosTheta1);

  if (k < 0.0) {
    // Total internal reflection
    return reflect(incidentDir, normal);
  } else {
    // Schlick approximation
    float R0 = pow((AirRefractiveIndex - refractiveIndex) / (AirRefractiveIndex + refractiveIndex), 2.0);
    float schlickTerm = R0 + (1.0 - R0) * pow(1.0 - cosTheta1, 5.0);
    if (pcg_hash_to_float(state) < schlickTerm) {
      return reflect(incidentDir, normal);
    } else {
      vec3 refractedDir = eta * incidentDir + (eta * cosTheta1 - sqrt(k)) * normal;
      return refractedDir;
    }
  }
}

vec3 TraceRay(Ray ray, inout uint state) {
    vec3 raycolor = vec3(1);
    vec3 light = vec3(0);
    vec3 accumulatedColor = vec3(0);
    float attenuation = 1.0;


    for(int i=0; i <= maxBounces; i++) {
      HitInfo hit = CalculateRayCollision(ray);
      Material material = hit.material;
      if(hit.didHit) {
        ray.Origin = hit.hitPoint;
        vec3 diffuseDir = normalize(hit.normal + randomDirection(state));

        if(material.transparency > 0.0) {
            vec3 incidentDir = ray.Direction;
            vec3 normal = hit.normal;
            float refractiveIndex = material.refractiveIndex;
            ray.Direction = RefractRay(incidentDir, normal, refractiveIndex, state);

            vec3 emmittedLight = material.emissionColor * material.emmisionStrength;
            light += emmittedLight * raycolor * attenuation;

            raycolor *= material.Color;
            attenuation *= material.Color.x;

       } else {
            vec3 specularDir = reflect(ray.Direction, hit.normal);
            bool makespec = material.specProb >= pcg_hash_to_float(state);
            ray.Direction = mix(diffuseDir, specularDir, material.smoothness * float(makespec));

            vec3 emmittedLight = material.emissionColor * material.emmisionStrength;
            float lightStrength = dot(hit.normal, ray.Direction);
            light += emmittedLight * raycolor * attenuation;
            raycolor *= mix(material.Color, material.specularColor, float(makespec)); 
        }

        if(material.transparency < 1.0) {
            vec3 transparentColor = vec3(1.0) - material.Color;
            accumulatedColor += transparentColor * raycolor * attenuation;
        }

      } else {
        if(envEnable) {
          light += Envirnoment(ray) * raycolor;
        }
        break;
      }
    }
    return light + accumulatedColor;
}