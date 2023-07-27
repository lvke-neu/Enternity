#version 440 core

in vec2 v_texcoord;

layout (location = 0) out vec4 fragColor;
layout (binding = 0) uniform sampler2D u_texture;

void main()
{
	//fragColor = texture(u_texture, v_texcoord);
	fragColor = vec4(1,1,1,1);
};