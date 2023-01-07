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

uniform int u_useColor;
uniform vec3 u_Color;

uniform sampler2D u_texture;
uniform sampler2D u_texture2;

void main() 
{
	if(u_useColor == 1)
		pixelColor = texture(u_texture, v_texcoord);
	else
		pixelColor = texture(u_texture2, v_texcoord);

	vec4 ambient = u_lightAmbient * u_materialAmbient ;
	
	vec4 diffuse;
	vec3 normalW = normalize(v_normalW);
	vec3 lightDir = normalize(-u_lightDir);
	float diff = max(dot(normalW, lightDir), 0.0);
	diffuse = u_lightDiffuse * u_materialDiffuse * diff ;

	vec4 specular;
	vec3 viewDir = normalize(u_eyePos - v_position);
	vec3 reflectDir = reflect(normalize(u_lightDir), normalW);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 128);
	specular = u_lightSpecular * u_materialSpecular * spec ;

	pixelColor = pixelColor * (ambient + diffuse + specular);
	//pixelColor = pixelColor * ambient;
	//pixelColor = vec4(normalW,1);
};