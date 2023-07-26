#version 440 core
layout(location = 0) in vec3 a_position;

uniform mat4 u_v;
uniform mat4 u_p;

out vec3 v_position;

void main()
{
	gl_Position = u_p * u_v * vec4(a_position, 1);
	v_position = a_position;
};