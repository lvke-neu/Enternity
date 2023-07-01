#version 440 core

layout(location = 0) in vec3 position;

uniform mat4 u_mvp;
out vec3 v_position;


void main()
{
	v_position = position;
	gl_Position = (u_mvp * vec4(position.xyz, 1.0)).xyww;
};