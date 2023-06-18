#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;



uniform mat4 u_mvp;


void main()
{
	gl_Position = u_mvp * vec4(position.xyz, 1.0);

};

#shader pixel
#version 440 core

void main()
{

};