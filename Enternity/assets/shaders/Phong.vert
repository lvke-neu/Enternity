#version 440 core
layout(location = 0) in vec3 a_position;

uniform mat4 vp;
void main()
{
	gl_Position = vp * vec4(a_position, 1);
};