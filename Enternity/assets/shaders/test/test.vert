#version 440 core
layout(location = 0) in vec3 a_position;

uniform mat4 u_m;
uniform mat4 u_v;
uniform mat4 u_p;

void main()
{
	gl_Position = u_p * u_v * u_m * vec4(a_position, 1);
};