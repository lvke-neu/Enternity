#version 440 core

out vec4 fragColor;

float near = 1; 
float far  = 50.0; 

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}

void main()
{             
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    fragColor = vec4(depth, 0, 0, 1.0);
}