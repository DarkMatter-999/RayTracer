#version 440 core
out vec4 FragColor;
 
in vec4 vertexColor; 

uniform vec2 iResolution;
uniform vec3 position;
uniform vec2 dimension;
uniform vec2 delta;

mat4 m_Projection = mat4(1.0);
mat4 m_View = mat4(1.0);
mat4 m_InverseProjection = mat4(1.0);
mat4 m_InverseView = mat4(1.0);

float m_VerticalFOV = 70.0;
float m_NearClip = 0.1;
float m_FarClip = 1000.0;
vec3 m_Position = position;
vec3 m_ForwardDirection = vec3(0.0, 0.0, -2.0);

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

void RecalculateForward() {
    float x = cos(delta.x) * cos(delta.y);
    float y = sin(delta.x) * cos(delta.y);
    float z = sin(delta.y);
    m_ForwardDirection = vec3(x, 0, z);
}

void RecalculateProjection()
{
	m_Projection = perspective(m_VerticalFOV,dimension.x / dimension.y, m_NearClip, m_FarClip);
	m_InverseProjection = inverse(m_Projection);
}

void RecalculateView()
{
	m_View = lookAt(m_Position, m_Position + m_ForwardDirection * 0.00001, vec3(0, 1, 0));
	m_InverseView = inverse(m_View);
}

void main()
{
    vec3 rayOrigin = position;
    vec3 color = vertexColor.xyz;
    float radius = 0.5;

    RecalculateProjection();
    // RecalculateForward();
    RecalculateView();
    vec2 ndc = (gl_FragCoord.xy / iResolution) * 2.0 - 1.0;
    vec2 coord = ndc; // -1 -> 1
    vec4 target = m_InverseProjection * vec4(coord.x, coord.y, 1, 1);
	vec3 rayDirection = vec3(m_InverseView * vec4(normalize(vec3(target) / target.w), 0)); // World space

    float a = dot(rayDirection, rayDirection);
    float b = 2.0 * dot(rayOrigin, rayDirection);
    float c = dot(rayOrigin, rayOrigin) - radius * radius;

    float D = b*b - 4.0*a*c;

    if (D >= 0.0) {
        color = vec3(1.0, 0.0, 1.0);

        float t0 = (-b + sqrt(D)) / (2.0 * a);
        float t1 = (-b - sqrt(D)) / (2.0 * a);

        vec3 h0 = rayOrigin + rayDirection * t0;
        vec3 h1 = rayOrigin + rayDirection * t1;

        vec3 lightDir = normalize(vec3(-1));

        vec3 normal = normalize(h1);

        float d = max(dot(normal, -lightDir) ,0);

        color *= d;

    }

    FragColor = vec4(color, 1.0);
} 