#version 440 core

uniform int u_bUseTexture;
uniform vec4 u_ambientColor;
uniform vec4 u_diffuseColor;
uniform vec4 u_specularColor;
layout (binding = 0) uniform sampler2D u_ambientTexture;
layout (binding = 1) uniform sampler2D u_diffuseTexture;
layout (binding = 2) uniform sampler2D u_sspecularTexture;

in vec2 v_texcoord;

layout (location = 0) out vec4 fragColor;

void main()
{
	vec4 Ambient; 
	vec4 Diffuse; 

	if(u_bUseTexture == 0)
	{
		Ambient = u_ambientColor;
		Diffuse = u_diffuseColor;
	}
	else
	{
		Ambient = texture(u_ambientTexture, v_texcoord); 
		Diffuse = texture(u_diffuseTexture, v_texcoord); ;
	}
	fragColor = Ambient + Diffuse;
};