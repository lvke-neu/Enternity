#shader vertex
#version 440 core 

layout(location = 0) in vec3 position;

uniform mat4 u_mvp;

void main() 
{
	gl_Position = u_mvp * vec4(position.xyz, 1.0);
	
};

#shader pixel
#version 440 core 

out vec4 pixelColor;

void main() 
{
	pixelColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
};