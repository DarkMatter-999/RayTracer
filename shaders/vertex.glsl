#version 440 core
layout (location = 0) in vec3 Position; // position variable at attribute position 0
layout (location = 1) in vec3 Color; // color variable at attribute position 1

out vec4 vertexColor; // specify a color output to the fragment shader

uniform float scale;
uniform vec3 color;

void main()
{
    gl_Position = vec4(Position * scale, 1.0);
    vertexColor = vec4(color, 1.0);
}