#version 440 core
out vec4 FragColor;
 
in vec4 vertexColor; 

uniform vec2 iResolution;

void main()
{
    vec3 color = vec3(0.0);

    vec3 rayOrigin = vec3(0.0, 0.0, 1.0);
    vec2 ndc = (gl_FragCoord.xy / iResolution) * 2.0 - 1.0;
    vec3 rayDirection = (vec3(ndc, -1.0)); 
    float radius = 0.5;

    float a = dot(rayDirection, rayDirection);
    float b = 2.0 * dot(rayOrigin, rayDirection);
    float c = dot(rayOrigin, rayOrigin) - radius * radius;

    float D = b*b - 4.0*a*c;

    if (D > 0.2){
        color = vec3(1.0, 0.0, 1.0);        
    }

    FragColor = vec4(color, 1.0);
} 