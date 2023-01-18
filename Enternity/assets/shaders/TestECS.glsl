#shader vertex
#version 330 core

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
#version 330 core

layout(location = 0) out vec4 pixelColor;
layout(location = 1) out int entityId;


in vec2 v_texcoord;

uniform int b_useColor;
uniform vec4 u_baseColor;
uniform sampler2D u_texture;

void main()
{
	if(b_useColor == 1)
	{
		pixelColor = u_baseColor;
	}
	else if(b_useColor == 0)
	{
		pixelColor = texture(u_texture, v_texcoord);
	}

	//pixelColor = vec4(vec3(gl_FragCoord.z),1.0);
	entityId = 50;
};