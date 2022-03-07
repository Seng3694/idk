#version 330 core

layout(location = 0) in vec2 in_Position;
layout(location = 1) in vec2 in_TexCoords;


out vec2 TexCoords;

uniform mat4 u_ModelView;

void main() 
{
    TexCoords = in_TexCoords;
    gl_Position = u_ModelView * vec4(in_Position, 0.0, 1.0);
}
