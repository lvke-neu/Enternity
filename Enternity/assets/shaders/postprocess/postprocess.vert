#version 440 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texcoord;

uniform mat4 u_mvp;
out vec2 v_texcoord;

void main()
{
	gl_Position = vec4(a_position, 1);
	v_texcoord = a_texcoord;
};