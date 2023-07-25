#version 440 core

in vec2 v_texcoord;
layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 depthColor;

layout (binding = 0) uniform sampler2D u_texture;

float near = 1; 
float far  = 50.0; 
float LinearizeDepth(float depth) 
{	
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}

void main()
{
	fragColor = texture(u_texture, v_texcoord);
	float depth = LinearizeDepth(gl_FragCoord.z) / far;
    depthColor = vec4(depth, 0, 0, 1.0);
};