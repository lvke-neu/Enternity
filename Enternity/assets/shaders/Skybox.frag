#version 440 core

out vec4 fragColor;
in vec3 u_texcoord;

layout (binding = 0) uniform samplerCube u_sampleTexture;

void main()
{
	fragColor = texture(u_sampleTexture, u_texcoord);
};