#version 440 core

in vec2 v_texcoord;
out vec4 fragColor;

layout (binding = 0) uniform sampler2D u_texture;

void main()
{
	fragColor = texture(u_texture, v_texcoord);;
};