#version 440 core
in vec2 u_texcoord;

layout (binding = 0) uniform sampler2D u_sampleTexture;
out vec4 fragColor;

void main()
{
	//fragColor = vec4(vec3(1 - texture(u_sampleTexture, u_texcoord)), 1.0);

//	fragColor = texture(u_sampleTexture, u_texcoord);
//    float average = (fragColor.r + fragColor.g + fragColor.b) / 3.0;
//    fragColor = vec4(average, average, average, 1.0);


const float offset = 1.0 / 300.0; 
	 vec2 offsets[9] = vec2[](
        vec2(-offset,  offset),
        vec2( 0.0f,    offset),
        vec2( offset,  offset),
        vec2(-offset,  0.0f),  
        vec2( 0.0f,    0.0f),  
        vec2( offset,  0.0f),  
        vec2(-offset, -offset),
        vec2( 0.0f,   -offset),
        vec2( offset, -offset) 
    );

    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

//float kernel[9] = float[](
//    1.0 / 16, 2.0 / 16, 1.0 / 16,
//    2.0 / 16, 4.0 / 16, 2.0 / 16,
//    1.0 / 16, 2.0 / 16, 1.0 / 16  
//);

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(u_sampleTexture, u_texcoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    fragColor = vec4(col, 1.0);
}