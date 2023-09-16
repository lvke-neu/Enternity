#version 440 core

layout(location = 0) in vec3 position;

layout (std140, binding = 0) uniform Projection
{
    mat4 u_projection;
};

layout (std140, binding = 1) uniform View
{
    mat4 u_view;
};


out vec3 v_position;

void main()
{
	v_position = position;
	mat4 viewIgnoreTranslation = u_view;
	gl_Position = (u_projection * mat4(mat3(u_view)) * vec4(position.xyz, 1.0)).xyww;
};