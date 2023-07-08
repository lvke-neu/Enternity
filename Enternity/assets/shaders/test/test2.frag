#version 440 core

in vec3 v_position;
in vec3 v_normal;
in vec2 v_texcoord;

layout (location = 0) out vec4 fragColor;


layout (binding = 0) uniform sampler2D u_texture;
layout (binding = 1) uniform samplerCube u_skybox;

uniform vec3 u_cameraPos;
uniform uint u_environmentMapType;

void main()
{
	if(u_environmentMapType == 0)
	{
		fragColor = texture(u_texture, v_texcoord);
	}
	else if(u_environmentMapType == 1)
	{
		vec3 I = normalize(v_position - u_cameraPos);
		vec3 R = reflect(I, normalize(v_normal));
		fragColor = vec4(texture(u_skybox, R).rgb, 1.0);
	}
	else
	{
		float ratio = 1.00 / 1.52;
		vec3 I = normalize(v_position - u_cameraPos);
		vec3 R = refract(I, normalize(v_normal), ratio);
		fragColor = vec4(texture(u_skybox, R).rgb, 1.0);
	}


};