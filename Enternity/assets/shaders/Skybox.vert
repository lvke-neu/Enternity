#version 440 core
layout(location = 0) in vec3 a_position;


uniform mat4 u_view;
uniform mat4 u_proj;
out vec3 u_texcoord;

void main()
{
	gl_Position = (u_proj * u_view * vec4(a_position, 1)).xyww;
	u_texcoord = a_position;
};