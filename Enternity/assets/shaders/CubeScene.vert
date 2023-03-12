#version 440 core
layout(location = 0) in vec3 a_position;
layout(location = 2) in vec2 a_texcoord;

uniform mat4 u_mvp;


out vec2 u_texcoord;

void main()
{
	gl_Position = u_mvp * vec4(a_position, 1);
	u_texcoord = a_texcoord;
};