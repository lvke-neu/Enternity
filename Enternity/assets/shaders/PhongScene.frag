#version 440 core

in vec2 u_texcoord;
in vec3 u_normal;
in vec3 u_fragPos;

layout (binding = 0) uniform sampler2D u_sampleTexture;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

out vec4 fragColor;
void main()
{
	//fragColor = texture(u_sampleTexture, u_texcoord);
	fragColor = vec4(0.4, 0.3, 0.27, 1.0);
	
	//ambient
	float ambient = 0.5;

	//diffuse
	vec3 fragNormal = normalize(u_normal);
	vec3 lightDir   = normalize(u_lightPos - u_fragPos);
	float diffuse = max(dot(fragNormal, lightDir), 0);

	//specular
	vec3 viewDir = normalize(u_viewPos - u_fragPos);
	vec3 reflectDir = reflect(-lightDir, fragNormal);
	float specular = pow(max(dot(viewDir, reflectDir), 0),32);

	fragColor *= (ambient + diffuse + specular);
};