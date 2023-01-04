#shader vertex
#version 330 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

out vec2 v_texcoord;
out vec3 v_normalW;
out vec3 v_position;

uniform mat4 u_mvp;
uniform mat4 u_mInvTrans;
uniform mat4 u_m;

void main() 
{
	gl_Position = u_mvp * vec4(position.xyz, 1.0);
	
	v_texcoord = texcoord;
	v_normalW = mat3(u_mInvTrans) * normal;
	v_position = (u_m * vec4(position, 1.0f)).xyz;
};

#shader pixel
#version 330 core 

out vec4 pixelColor;
in vec2 v_texcoord;
in vec3 v_normalW;
in vec3 v_position;

uniform vec4 u_lightAmbient;
uniform vec4 u_materialAmbient;
uniform vec3 u_lightDir;
uniform vec4 u_lightDiffuse;
uniform vec4 u_materialDiffuse;
uniform vec4 u_lightSpecular;
uniform vec4 u_materialSpecular;
uniform vec3 u_eyePos;

uniform sampler2D u_texture;

void main() 
{
	pixelColor = texture(u_texture, v_texcoord);
	pixelColor = vec4(1, 1, 1, 1.0f);

	vec4 ambient = u_lightAmbient * u_materialAmbient * 0.1;
	
	vec4 diffuse;
	vec3 normalW = normalize(v_normalW);
	vec3 lightDir = normalize(-u_lightDir);
	float diff = max(dot(normalW, lightDir), 0.0);
	diffuse = u_lightDiffuse * u_materialDiffuse * diff * 0.5;

	vec4 specular;
	vec3 viewDir = normalize(u_eyePos - v_position);
	vec3 reflectDir = reflect(normalize(u_lightDir), normalW);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
	specular = u_lightSpecular * u_materialSpecular * spec * 0.5;

	pixelColor = pixelColor * (ambient + diffuse + specular);
	//pixelColor = pixelColor * ambient;
	//pixelColor = vec4(normalW,1);
};