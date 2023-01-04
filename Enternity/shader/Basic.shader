#shader vertex
#version 330 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

out vec2 v_texcoord;
out vec3 v_normalW;

uniform mat4 u_mvp;
uniform mat4 u_m;

void main() 
{
	gl_Position = u_mvp * vec4(position.xyz, 1.0);
	
	v_texcoord = texcoord;
	v_normalW = (u_m * vec4(normal, 1.0)).xyz;
};

#shader pixel
#version 330 core 

out vec4 pixelColor;
in vec2 v_texcoord;
in vec3 v_normalW;

uniform vec4 u_lightAmbient;
uniform vec4 u_materialAmbient;
uniform vec3 u_lightDir;
uniform vec4 u_lightDiffuse;
uniform vec4 u_materialDiffuse;

uniform sampler2D u_texture;

void main() 
{
	pixelColor = texture(u_texture, v_texcoord);
	

	vec4 ambient = u_lightAmbient * u_materialAmbient * 0.1;
	
	vec4 diffuse;
	vec3 normalW = normalize(v_normalW);
	vec3 lightDir = normalize(-u_lightDir);
	float diff = max(dot(normalW, lightDir), 0.0);
	diffuse = u_lightDiffuse * u_materialDiffuse * diff;

	pixelColor = pixelColor * (ambient + diffuse);
	//pixelColor = pixelColor * ambient;
	//pixelColor = vec4(normalW,1);
};