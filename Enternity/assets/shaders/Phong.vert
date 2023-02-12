#version 440 core
layout(location = 0) in vec3 a_position;

uniform mat4 test;
void main()
{
	gl_Position = test * vec4(a_position, 1);
};