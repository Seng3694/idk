#version 330 core

in vec2 TexCoords; 
out vec4 color;

uniform sampler2D u_Image;
uniform vec4 u_Color;

void main() 
{ 
	color = u_Color * texture(u_Image, TexCoords); 
}
