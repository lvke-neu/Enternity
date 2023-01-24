#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;


uniform mat4 u_mvp;
uniform mat4 u_m;
uniform mat4 u_inverseTransposeM;

out vec2 v_texcoord;
out vec3 v_worldPos;
out vec3 v_worldNormal;

void main()
{
	gl_Position = u_mvp * vec4(position.xyz, 1.0);
	v_texcoord = texcoord;
	v_worldPos = (u_m * vec4(position.xyz, 1.0)).xyz;
	v_worldNormal = mat3(u_inverseTransposeM) * normal;
};

#shader pixel
#version 440 core

layout(location = 0) out vec4 pixelColor;
layout(location = 1) out int entityId;


in vec2 v_texcoord;

uniform int b_useColor;
uniform vec4 u_baseColor;
layout (binding = 0) uniform sampler2D u_texture;
uniform int u_entityId;

uniform vec3 u_lightPos;

uniform vec4 u_lightAmbient;
uniform vec4 u_entityAmbient;
uniform vec4 u_lightDiffuse;
uniform vec4 u_entityDiffuse;

in vec3 v_worldPos;
in vec3 v_worldNormal;

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

	//ambient
	vec4 Ambient = u_lightAmbient * u_entityAmbient;

	//diffuse
	vec4 Diffuse = u_lightDiffuse * u_entityDiffuse;
	vec3 worldNomal = normalize(v_worldNormal);
	
	//point light
	//vec3 negLightDirection = normalize(u_lightPos - v_worldPos);

	//direction light
	vec3 negLightDirection = normalize(u_lightPos);

	Diffuse = Diffuse * max(0, dot(worldNomal, negLightDirection));

	pixelColor = pixelColor * (Ambient + Diffuse);

	entityId = u_entityId;
};