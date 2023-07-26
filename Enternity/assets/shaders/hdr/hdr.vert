#version 440 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texcoord;


uniform mat4 u_v;
uniform mat4 u_p;

out vec3 v_position;
out vec2 v_texcoord;


void main()
{
	gl_Position = u_p * u_v * vec4(a_position, 1);
	v_position = a_position;
	v_texcoord = a_texcoord;
};