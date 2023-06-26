#version 440 core
layout (location = 0) in vec3 Position; // position variable at attribute position 0
layout (location = 1) in vec3 Color; // color variable at attribute position 1

out vec4 vertexColor; // specify a color output to the fragment shader

void main()
{
    gl_Position = vec4(Position, 1.0);
    vertexColor = vec4(Color, 1.0);
}