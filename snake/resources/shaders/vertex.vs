#version 330 core

// argumenty
in vec4 vertex;
in vec4 normal;
in vec2 texture;

out vec4 n;
out vec4 v;
out vec4 l;
out vec4 d;
out vec4 spot_l;
out vec4 spot_d;
out vec2 texCoord;

// jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float cutOff;
	float outerCutOff;
};

uniform PointLight pointLight;
uniform DirectionalLight directionalLight;
uniform SpotLight spotLight;

void main()	{
	texCoord = texture;
	n = normalize(V*M*normal);
	v = normalize(vec4(0,0,0,1) - V*M*vertex);
	
	// directional
	d = normalize(V*vec4(directionalLight.direction,0));

	// point
	l = normalize(V*vec4(pointLight.position,1)-V*M*vertex);

	// spot
	spot_l = normalize(V*vec4(spotLight.position,1)-V*M*vertex);
	spot_d = normalize(V*vec4(spotLight.direction,0));

	gl_Position = P*V*M*vertex;
}