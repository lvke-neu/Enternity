#shader vertex
#version 330 core 

layout(location = 0) in vec3 position;

void main() 
{
gl_Position = vec4(position.xyz, 1.0);
};

#shader pixel
#version 330 core 
#extension GL_ARB_explicit_uniform_location : enable

out vec4 pixelColor;

layout(location = 0) uniform vec4 u_color1;  
layout(location = 1) uniform vec4 u_color2;
layout(location = 2) uniform vec4 u_color3;
void main() 
{
	pixelColor = u_color1;
};