#shader vertex
#version 330 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
out vec4 settingcolor;
void main() 
{
gl_Position = vec4(position.xyz, 1.0);
settingcolor = vec4(color, 1.0f);
};

#shader pixel
#version 330 core 

out vec4 pixelColor;
in vec4 settingcolor;

uniform vec4 u_color1;
uniform vec4 u_color2;
uniform vec4 u_color3;
void main() 
{
	pixelColor = settingcolor;
};