#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texcoord;


uniform mat4 u_mvp;
out vec2 v_texcoord;


void main()
{
	gl_Position = u_mvp * vec4(position.xyz, 1.0);
	v_texcoord = texcoord;
};

#shader pixel
#version 440 core

out vec4 pixelColor;
in vec2 v_texcoord;

uniform int b_useColor;
uniform vec4 u_baseColor;
uniform sampler2D u_texture;

void main()
{
	//pixelColor = vec4(v_texcoord, 0, 1);
	if(b_useColor == 1)
	{
		pixelColor = u_baseColor;
	}
	else if(b_useColor == 0)
	{
		pixelColor = texture(u_texture, v_texcoord);
	}
	pixelColor = vec4(0.3,0.4,0.7,1);
};