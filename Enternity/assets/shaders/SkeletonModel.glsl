#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in ivec4 boneIds;
layout(location = 4) in vec4 weights;
layout(location = 5) in ivec4 boneIds2;
layout(location = 6) in vec4 weights2;

uniform mat4 u_mvp;
out vec2 v_texcoord;

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
    // if(BoneTransform == mat4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0))
    // {
    //     gl_Position = u_mvp * vec4(position.xyz, 1.0);
    // }
    // else
    // {
    //     vec4 PosL = BoneTransform * vec4(position.xyz, 1.0);
    //     gl_Position = u_mvp * PosL;
    // }

    mat4 BoneTransform =    g_Bones[boneIds.x] * weights.x;
        BoneTransform     += g_Bones[boneIds.y] * weights.y;
        BoneTransform     += g_Bones[boneIds.z] * weights.z;
        BoneTransform     += g_Bones[boneIds.w] * weights.w;

        BoneTransform     += g_Bones[boneIds2.x] * weights2.x;
        BoneTransform     += g_Bones[boneIds2.y] * weights2.y;
        BoneTransform     += g_Bones[boneIds2.z] * weights2.z;
        BoneTransform     += g_Bones[boneIds2.w] * weights2.w;

    vec4 PosL = BoneTransform * vec4(position.xyz, 1.0);
    gl_Position = u_mvp * PosL;

    v_texcoord = texcoord;

};

#shader pixel
#version 440 core


in vec2 v_texcoord;

layout(location = 0) out vec4 pixelColor;
layout(location = 1) out int entityId;


layout (binding = 0) uniform sampler2D u_diffuseTexture;


uniform int u_entityId;

void main()
{	 
    pixelColor = texture(u_diffuseTexture, v_texcoord);

	entityId = u_entityId;
    //entityId = int(g_Bones[0][0].x);
};