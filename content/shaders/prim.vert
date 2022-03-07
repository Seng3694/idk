#version 330 core

layout(location = 0) in vec2 in_Position;

uniform mat4 u_ModelView;

void main() 
{
    gl_Position = u_ModelView * vec4(in_Position, 0.0, 1.0);
}
