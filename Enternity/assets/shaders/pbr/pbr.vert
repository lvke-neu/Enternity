#version 440 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texcoord;

uniform mat4 u_m;
uniform mat4 u_v;
uniform mat4 u_p;
uniform mat4 u_lightVP;

out vec3 v_worldPos;
out vec3 v_normal;
out vec2 v_texcoord;
out vec4 v_fragPosLightSpace;

void main()
{
	gl_Position = u_p * u_v * u_m * vec4(a_position, 1);
	v_worldPos = vec3(u_m * vec4(a_position, 1.0));
	v_normal = transpose(inverse(mat3(u_m))) * a_normal;
	v_texcoord = a_texcoord;
	v_fragPosLightSpace = u_lightVP * vec4(v_worldPos.xyz, 1);
};