#version 440 core

in vec2 v_texcoord;

layout (location = 0) out vec4 fragColor;

layout (binding = 0) uniform sampler2D u_ambientTexture;
layout (binding = 1) uniform sampler2D u_diffuseTexture;
layout (binding = 2) uniform sampler2D u_specularTexture;

uniform vec4 u_ambientColor;
uniform vec4 u_diffuseColor;
uniform vec4 u_specularColor;

void main()
{
	vec4 ambient = texture(u_ambientTexture, v_texcoord) * u_ambientColor;
	vec4 diffuse = texture(u_diffuseTexture, v_texcoord) * u_diffuseColor;
	vec4 specular = texture(u_specularTexture, v_texcoord) * u_specularColor;
	fragColor = ambient + diffuse + specular;
};