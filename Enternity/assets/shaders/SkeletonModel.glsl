#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in ivec4 boneIds;
layout(location = 4) in vec4 weights;

uniform mat4 u_mvp;

const int MAX_BONES = 200;
uniform mat4 g_Bones[MAX_BONES];

void main()
{
    // mat4 BoneTransform;
    // BoneTransform[0] = vec4(1,0,0,0);
    // BoneTransform[1] = vec4(0,1,0,0);
    // BoneTransform[2] = vec4(0,0,1,0);
    // BoneTransform[3] = vec4(0,0,0,1);
    
    // mat4 BoneTransform = mat4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    // if(boneIds.x != -1 && weights.x != -1)
    //     BoneTransform     += g_Bones[boneIds.x] * weights.x;
    // if(boneIds.y != -1 && weights.y != -1)
    //     BoneTransform     += g_Bones[boneIds.y] * weights.y;
    // if(boneIds.z != -1 && weights.z != -1)
    //     BoneTransform     += g_Bones[boneIds.z] * weights.z;
    // if(boneIds.w != -1 && weights.w != -1)
    //     BoneTransform     += g_Bones[boneIds.w] * weights.w;
    // // if(BoneTransform == mat4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0))
    // // {
    // //     gl_Position = u_mvp * vec4(position.xyz, 1.0);
    // // }
    // // else
    // // {
    // //     vec4 PosL = BoneTransform * vec4(position.xyz, 1.0);
    // //     gl_Position = u_mvp * PosL;
    // // }

    mat4 BoneTransform =    g_Bones[boneIds.x] * weights.x;

        BoneTransform     += g_Bones[boneIds.y] * weights.y;

        BoneTransform     += g_Bones[boneIds.z] * weights.z;

        BoneTransform     += g_Bones[boneIds.w] * weights.w;


     vec4 PosL = BoneTransform * vec4(position.xyz, 1.0);
        gl_Position = u_mvp * PosL;
};

#shader pixel
#version 440 core

layout(location = 0) out vec4 pixelColor;
layout(location = 1) out int entityId;

uniform int u_entityId;

void main()
{	 
    pixelColor = vec4(1,0,0,1);

	entityId = u_entityId;
    //entityId = int(g_Bones[0][0].x);
};