#shader vertex
#version 440 core

layout(location = 0) in vec3 position;

uniform mat4 u_mvp;
out vec3 v_position;


void main()
{
	v_position = position;
	gl_Position = (u_mvp * vec4(position.xyz, 1.0)).xyww;
};

#shader pixel
#version 440 core

layout(location = 0) out vec4 pixelColor;
layout(location = 1) out int entityId;

in vec3 v_position;
uniform samplerCube skybox;

void main()
{
	pixelColor = texture(skybox, v_position);
	//pixelColor = vec4(1,0,0,1);
	entityId = -1;
};