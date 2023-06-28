#version 440 core
out vec4 FragColor;
 
in vec4 vertexColor; 

uniform vec2 iResolution;

void main()
{
    vec3 color = vertexColor.xyz;

    vec3 rayOrigin = vec3(0.0, 0.0, 1.0);
    vec2 ndc = (gl_FragCoord.xy / iResolution) * 2.0 - 1.0;
    vec3 rayDirection = (vec3(ndc, -1.0)); 
    float radius = 0.5;

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