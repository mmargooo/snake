#version 330 core

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

out vec4 color;

in vec4 n;
in vec4 v;
in vec4 l;
in vec4 d;
in vec4 spot_l;
in vec4 spot_d;
in vec2 texCoord;

uniform sampler2D textureMap;
uniform float shininess;

vec3 calcPointLight(PointLight pointLight, vec4 ml, vec4 mn, vec4 mv);
vec3 calcDirectionalLight(DirectionalLight directionalLight, vec4 md, vec4 mn, vec4 mv);
vec3 calcSpotLight(SpotLight spotLight, vec4 mspot_l, vec4 mspot_d, vec4 mn, vec4 mv);

void main() {
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);

	vec4 ml = normalize(l);
	vec4 md = normalize(d);
	vec4 mspot_l = normalize(spot_l);
	vec4 mspot_d = normalize(spot_d);

	// calc directional
	color = vec4(calcDirectionalLight(directionalLight, md, mn, mv),1);
	
	// calc pointlight 
	color += vec4(calcPointLight(pointLight, ml, mn, mv), 1);

	// calc spotlight
	color += vec4(calcSpotLight(spotLight, mspot_l, mspot_d, mn, mv), 1);
}

vec3 calcSpotLight(SpotLight spotLight, vec4 mspot_l, vec4 mspot_d, vec4 mn, vec4 mv) {
	// diffuse
	float nl = max(dot(mn, -mspot_d), 0);
	// specular
	vec4 r = reflect(mspot_d, mn);
	float rv = pow(max(dot(r, mv), 0), shininess);
	// spotlight intensity
	float theta = dot(mspot_l, normalize(-mspot_d));
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp((theta - spotLight.outerCutOff)/epsilon, 0, 1);

	// result
	vec3 ambient = spotLight.ambient * texture(textureMap, texCoord) * intensity;
	vec3 diffuse = spotLight.diffuse * vec4(nl,nl,nl,1) * texture(textureMap, texCoord) * intensity;
	vec3 specular = spotLight.specular * rv * texture(textureMap, texCoord) * intensity;

	return (ambient + diffuse + specular);
}

vec3 calcDirectionalLight(DirectionalLight directionalLight, vec4 md, vec4 mn, vec4 mv) {
	// diffuse
	float nl = max(dot(mn, -md), 0);
	// specular
	vec4 r = reflect(md, mn);
	float rv = pow(max(dot(r, mv), 0), shininess);

	// result
	vec3 ambient = directionalLight.ambient * texture(textureMap, texCoord);
	vec3 diffuse = directionalLight.diffuse * vec4(nl,nl,nl,1) * texture(textureMap, texCoord);
	vec3 specular = directionalLight.specular * rv * texture(textureMap, texCoord);

	return vec3(ambient+diffuse+specular);
}

vec3 calcPointLight(PointLight pointLight, vec4 ml, vec4 mn, vec4 mv) {
	// diffuse	
	float nl = max(dot(mn, ml), 0);
	// specular
	vec4 r = reflect(-ml, mn);
	float rv = pow(max(dot(r, mv), 0), shininess);
	// result
	vec3 ambient = pointLight.ambient * texture(textureMap, texCoord);
	vec3 diffuse = pointLight.diffuse * vec4(nl,nl,nl,1) * texture(textureMap, texCoord);
	vec3 specular = pointLight.specular * rv * texture(textureMap, texCoord);

	return vec3(ambient+diffuse+specular);
}