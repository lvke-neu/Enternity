#version 440 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texcoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;


out vec2 u_texcoord;
out vec3 u_normal;
out vec3 u_fragPos;

void main()
{
	gl_Position = u_proj * u_view * u_model * vec4(a_position, 1);
	u_texcoord = a_texcoord;
	u_normal = mat3(transpose(inverse(u_model))) *  a_normal;
	u_fragPos = vec3(u_model * vec4(a_position, 1));
};