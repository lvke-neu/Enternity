#version 440 core

struct Material
{
	layout (binding = 0) sampler2D ambient;
	layout (binding = 1) sampler2D diffuse;
	layout (binding = 2) sampler2D specular;
	float shininess;
};

in vec2 u_texcoord;
in vec3 u_normal;
in vec3 u_fragPos;

layout (binding = 0) uniform sampler2D u_sampleTexture;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;
uniform Material u_material;

out vec4 fragColor;
void main()
{
	//ambient
	float ambient = 0.2;
	vec4 ambientColor = ambient * texture(u_material.ambient, u_texcoord);


	//diffuse
	vec3 fragNormal = normalize(u_normal);
	vec3 lightDir   = normalize(u_lightPos - u_fragPos);
	float diffuse = max(dot(fragNormal, lightDir), 0);
	vec4 diffuseColor = diffuse * texture(u_material.diffuse, u_texcoord);

	//specular
	vec3 viewDir = normalize(u_viewPos - u_fragPos);
	vec3 reflectDir = reflect(-lightDir, fragNormal);
	float specular = pow(max(dot(viewDir, reflectDir), 0),	u_material.shininess);
	vec4 specularColor = specular * texture(u_material.specular, u_texcoord);

	fragColor = ambientColor + diffuseColor + specularColor;
};