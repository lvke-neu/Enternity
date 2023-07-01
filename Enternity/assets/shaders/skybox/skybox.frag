#version 440 core

out vec4 pixelColor;

in vec3 v_position;

layout(location = 0) uniform samplerCube skybox;

void main()
{
	pixelColor = texture(skybox, v_position);
};