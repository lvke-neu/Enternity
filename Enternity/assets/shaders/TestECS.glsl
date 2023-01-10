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

out vec4 pixelColor;

in vec2 v_texcoord;
uniform sampler2D u_texture;

void main()
{
	//pixelColor = vec4(v_texcoord, 0, 1);
	pixelColor = texture(u_texture, v_texcoord);
};