#version 440 core

layout (location = 0) out vec4 fragColor;

in vec2 v_texcoord;
in vec4 v_fragPosLightSpace;

layout (binding = 0) uniform sampler2D u_albedoTexture;
layout (binding = 6) uniform sampler2D u_shadowMapTexture;


float shadowCalculation(vec4 fragPosLightSpace)
{
  	// perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(u_shadowMapTexture, projCoords.xy).r; 
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Calculate bias (based on depth map resolution and slope)

    float bias = 0.005;
    // Check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(u_shadowMapTexture, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(u_shadowMapTexture, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{		
    
    float shadow = 1.0 - shadowCalculation(v_fragPosLightSpace);  


    fragColor = texture(u_albedoTexture, v_texcoord) + shadow * 0.1;
}
