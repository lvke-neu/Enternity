#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;


uniform mat4 u_mvp;
uniform mat4 u_m;
uniform mat4 u_inverseTransposeM;
uniform mat4 u_lightSpaceMatrix;

out vec2 v_texcoord;
out vec3 v_worldPos;
out vec3 v_worldNormal;
out vec4 FragPosLightSpace;

void main()
{
	gl_Position = u_mvp * vec4(position.xyz, 1.0);
	v_texcoord = texcoord;
	v_worldPos = (u_m * vec4(position.xyz, 1.0)).xyz;
	v_worldNormal = mat3(u_inverseTransposeM) * normal;
	FragPosLightSpace = u_lightSpaceMatrix * vec4(v_worldPos, 1.0);
};

#shader pixel
#version 440 core

layout(location = 0) out vec4 pixelColor;
layout(location = 1) out int entityId;


in vec2 v_texcoord;

uniform bool u_useTexture;
layout (binding = 0) uniform sampler2D u_diffuseTexture;
layout (binding = 1) uniform sampler2D u_specularTexture;
layout (binding = 2) uniform sampler2D u_shadowMap;


uniform int u_entityId;

uniform vec3 u_lightPos;
uniform vec3 u_cameraPos;

uniform vec4 u_lightAmbient;
uniform vec4 u_entityAmbient;
uniform vec4 u_lightDiffuse;
uniform vec4 u_entityDiffuse;
uniform vec4 u_lightSpecular;
uniform vec4 u_entitySpecular;
uniform int u_shininess;

in vec3 v_worldPos;
in vec3 v_worldNormal;
in vec4 FragPosLightSpace;

float ShadowCalculation(vec4 fragPosLightSpace)
{
	    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    // 取得最近点的深度(使用[0,1]范围下的fragPosLight当坐标)
    float closestDepth = texture(u_shadowMap, projCoords.xy).r; 
    // 取得当前片段在光源视角下的深度
    float currentDepth = projCoords.z;
    // 检查当前片段是否在阴影中
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

void main()
{

	//ambient
	vec4 Ambient = u_lightAmbient * texture(u_diffuseTexture, v_texcoord) * u_entityAmbient;

	//diffuse
	vec4 Diffuse = u_lightDiffuse * texture(u_diffuseTexture, v_texcoord) * u_entityDiffuse;
	vec3 worldNomal = normalize(v_worldNormal);
	//point light
	vec3 negLightDirection = normalize(u_lightPos - v_worldPos);
	//direction light
	//vec3 negLightDirection = normalize(u_lightPos);
	Diffuse = Diffuse * max(dot(worldNomal, negLightDirection), 0);

	//specular
	vec4 Specular = u_lightSpecular * texture(u_specularTexture, v_texcoord) * u_entitySpecular;
	vec3 reflectLightDir = normalize(reflect(-negLightDirection, worldNomal));
	vec3 viewDir = normalize(u_cameraPos - v_worldPos);
	Specular = Specular * pow(max(dot(reflectLightDir, viewDir), 0), u_shininess);

    float shadow = ShadowCalculation(FragPosLightSpace);       
    pixelColor = Ambient + (1.0 - shadow) * (Diffuse + Specular); 

	entityId = u_entityId;
};