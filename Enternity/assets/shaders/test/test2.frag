#version 440 core

in vec3 v_position;
in vec3 v_normal;
in vec2 v_texcoord;

out vec4 fragColor;

layout (binding = 0) uniform sampler2D u_texture;
layout (binding = 1) uniform samplerCube u_skybox;

uniform vec3 u_cameraPos;
uniform uint u_enableEnvironmentMap;

void main()
{
	if(u_enableEnvironmentMap == 0)
	{
		fragColor = texture(u_texture, v_texcoord);
	}
	else
	{
		vec3 I = normalize(v_position - u_cameraPos);
		vec3 R = reflect(I, normalize(v_normal));
		fragColor = vec4(texture(u_skybox, R).rgb, 1.0);
	}
};