#version 440 core
layout(location = 0) in vec3 a_position;
layout(location = 2) in vec2 a_texcoord;

out vec2 v_texcoord;

void main()
{
	gl_Position = vec4(a_position, 1);
	v_texcoord = a_texcoord;
};