#version 440 core

in vec2 u_texcoord;

layout (binding = 0) uniform sampler2D u_sampleTexture;

out vec4 fragColor;
void main()
{
	//fragColor = u_color * texture(u_sampleTexture, u_texcoord);
	fragColor = texture(u_sampleTexture, u_texcoord);
//	if(fragColor.a < 0.1)
//		discard;
}