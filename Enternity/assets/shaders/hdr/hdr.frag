#version 440 core

in vec3 v_position;

layout (location = 0) out vec4 fragColor;

layout (binding = 0) uniform sampler2D u_texture;

const vec2 invAtan = vec2(0.1591, 0.3183);
vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}

void main()
{
	
	fragColor = vec4(texture(u_texture, SampleSphericalMap(normalize(v_position))).rgb, 1.0);
};