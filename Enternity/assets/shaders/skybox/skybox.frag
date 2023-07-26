#version 440 core

layout (location = 0) out vec4 fragColor;

in vec3 v_position;
layout(location = 0) uniform samplerCube skybox;

void main()
{
    vec3 envColor = texture(skybox, v_position).rgb;
    
    // HDR tonemap and gamma correct
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2));

    fragColor = vec4(envColor, 1.0);
};