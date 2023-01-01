#shader vertex
#version 330 core 

layout(location = 0) in vec3 position;

layout(location = 1) in vec2 texcoord;


out vec2 settingtexcoord;
uniform mat4 u_mvp;
void main() 
{
	gl_Position = u_mvp * vec4(position.xyz, 1.0);
	
	settingtexcoord = texcoord;
};

#shader pixel
#version 330 core 

out vec4 pixelColor;

in vec2 settingtexcoord;
uniform vec4 u_color1;
uniform vec4 u_color2;
uniform vec4 u_color3;

uniform sampler2D u_texture;

void main() 
{
	//pixelColor = texture(u_texture, settingtexcoord);
	pixelColor = vec4(0.2f, 0.3f, 0.4f, 1.0f);
};