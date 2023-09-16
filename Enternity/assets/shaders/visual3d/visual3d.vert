#version 440 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texcoord;

layout (std140, binding = 0) uniform Projection
{
    mat4 u_projection;
};

layout (std140, binding = 1) uniform View
{
    mat4 u_view;
};

uniform mat4 u_model;

out vec2 v_texcoord;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1);
	v_texcoord = a_texcoord;
};