#version 440 core

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
	vec4 Ambient = u_ambientColor * texture(u_ambientTexture, v_texcoord); 
	vec4 Diffuse = u_diffuseColor * texture(u_diffuseTexture, v_texcoord); 

	fragColor = Ambient + Diffuse;
};