#version 440 core

in vec2 v_texcoord;
out vec4 fragColor;

layout (binding = 0) uniform sampler2D u_texture;
uniform uint u_postProcessType;



void main()
{
	if(u_postProcessType == 0)
	{
		fragColor = texture(u_texture, v_texcoord);
        return;
	}

	if(u_postProcessType == 1)
	{
		fragColor = vec4(vec3(1.0 - texture(u_texture, v_texcoord)), 1.0);
        return;
	}

	if(u_postProcessType == 2)
	{
		fragColor = texture(u_texture, v_texcoord);
		float average = 0.2126 * fragColor.r + 0.7152 * fragColor.g + 0.0722 * fragColor.b;
		fragColor = vec4(average, average, average, 1.0);
        return;
	}

    float kernel[9];
    if(u_postProcessType == 3)
    {
        kernel = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
        );
    }
   else if(u_postProcessType == 4)
    {
        kernel = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16   
        );
    }
    else if(u_postProcessType == 5)
    {
        kernel = float[](
            1, 1, 1,
            1, -8, 1,
            1, 1,1  
        );
    }

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
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(u_texture, v_texcoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    fragColor = vec4(col, 1.0);
};