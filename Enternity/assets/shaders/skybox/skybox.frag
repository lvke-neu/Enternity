#version 440 core

layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 depthColor;

float near = 1; 
float far  = 50.0; 
float LinearizeDepth(float depth) 
{	
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}

in vec3 v_position;

layout(location = 0) uniform samplerCube skybox;

void main()
{
	fragColor = texture(skybox, v_position);
	float depth = LinearizeDepth(gl_FragCoord.z) / far;
    depthColor = vec4(depth, 0, 0, 1.0);
};