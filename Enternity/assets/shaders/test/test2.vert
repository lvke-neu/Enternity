#version 440 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texcoord;

uniform mat4 u_m;
uniform mat4 u_v;
uniform mat4 u_p;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_texcoord;

void main()
{
	gl_Position = u_p * u_v * u_m * vec4(a_position, 1);
	v_normal = mat3(transpose(inverse(u_m))) * a_normal;
    v_position = vec3(u_m * vec4(a_position, 1.0));
	v_texcoord = a_texcoord;
};