#version 440 core

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec2 a_texcoord;
layout(location = 3) in ivec4 boneIds; 
layout(location = 4) in vec4 weights;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

uniform mat4 u_m;
uniform mat4 u_v;
uniform mat4 u_p;
uniform mat4 u_lightVP;


out vec2 v_texcoord;
out vec4 v_fragPosLightSpace;

void main()
{
    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >=MAX_BONES) 
        {
            totalPosition = vec4(a_position,1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(a_position,1.0f);
        totalPosition += localPosition * weights[i];
   }

	gl_Position = u_p * u_v * u_m * totalPosition;
	v_texcoord = a_texcoord;
	v_fragPosLightSpace = u_lightVP * vec4(vec3(u_m * totalPosition), 1);
};