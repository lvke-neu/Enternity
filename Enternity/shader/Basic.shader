#shader vertex
#version 330 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texcoord;

out vec4 settingcolor;
out vec2 settingtexcoord;

void main() 
{
	gl_Position = vec4(position.xyz, 1.0);
	settingcolor = vec4(color, 1.0f);
	settingtexcoord = texcoord;
};

#shader pixel
#version 330 core 

out vec4 pixelColor;
in vec4 settingcolor;
in vec2 settingtexcoord;
uniform vec4 u_color1;
uniform vec4 u_color2;
uniform vec4 u_color3;

uniform sampler2D u_texture;

void main() 
{
	//pixelColor = vec4(settingtexcoord, 0.0f, 1.0f);
	pixelColor = texture(u_texture, settingtexcoord);
};