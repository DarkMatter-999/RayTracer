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
};

struct Sphere {
  vec3 position;
  float radius;
  Material material;
};

mat4 perspective(float fovy, float aspect, float near, float far);

mat4 lookAt(vec3 eye, vec3 at, vec3 up);
void RecalculateProjection();
mat4 translate(vec3 translation);
mat4 rotate(float angle, vec3 axis);
mat4 view(vec3 position, vec3 rotation);
void RecalculateView();

void main()
{
    Sphere s1 = Sphere(vec3(0.0, 0.5, 0.5), 0.5, Material(vertexColor.xyz));
    Ray ray = Ray(position - s1.position, vec3(0));

    vec3 color = vec3(0);

    RecalculateProjection();
    RecalculateView();
    vec2 coord = (gl_FragCoord.xy / iResolution) * 2.0 - 1.0;
    vec4 target = m_InverseProjection * vec4(coord.x, coord.y, 1, 1);
	  ray.Direction = vec3(m_InverseView * vec4(normalize(vec3(target) / target.w), 0)); // World space

    float a = dot(ray.Direction, ray.Direction);
    float b = 2.0 * dot(ray.Origin, ray.Direction);
    float c = dot(ray.Origin, ray.Origin) - s1.radius * s1.radius;

    float D = b*b - 4.0*a*c;

    if (D >= 0.0) {
        float t0 = (-b + sqrt(D)) / (2.0 * a);
        float t1 = (-b - sqrt(D)) / (2.0 * a);

        vec3 h0 = ray.Origin + ray.Direction * t0;
        vec3 h1 = ray.Origin + ray.Direction * t1;

        vec3 lightDir = normalize(vec3(-1));

        vec3 normal = normalize(h1);

        float d = max(dot(normal, -lightDir) ,0);

        s1.material.Color *= d;
        color = s1.material.Color;
    }

    FragColor = vec4(color, 1.0);
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

