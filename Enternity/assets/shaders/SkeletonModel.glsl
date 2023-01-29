#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in ivec4 boneIds;
layout(location = 4) in vec4 weights;

out vec4 u_weights;

uniform mat4 u_mvp;

const int MAX_BONES = 200;
uniform mat4 g_Bones[MAX_BONES];

void main()
{
	gl_Position = u_mvp * vec4(position.xyz, 1.0);
    u_weights = weights;
};

#shader pixel
#version 440 core

layout(location = 0) out vec4 pixelColor;
layout(location = 1) out int entityId;

uniform int u_entityId;

in vec4 u_weights;

void main()
{	 
    pixelColor = vec4(u_weights.xyz,1);

	entityId = u_entityId;
};