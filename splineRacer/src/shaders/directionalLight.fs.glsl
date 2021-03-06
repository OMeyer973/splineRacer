#version 330 core

in vec4 vFragPosition;
in vec4 vFragNormal;
in vec2 vFragTexCoords;

uniform vec3 uLightIntensity;
uniform vec3 uLightDir_vs;
uniform vec3 uKd;
uniform vec3 uKs;
uniform vec3 uKa;
uniform float uShininess;

uniform sampler2D uTexture;

out vec3 fFragColor;

vec3 blinnPhong() {
	return uLightIntensity * (uKd * dot(normalize(uLightDir_vs), vFragNormal.xyz)
		+ uKs * pow((dot((normalize(-vFragPosition.xyz) + normalize(uLightDir_vs)) / 2, vFragNormal.xyz)), uShininess));
}

void main() {
	float ambientStrength = 0.15f;
	vec3 tex = vec3(texture(uTexture,vFragTexCoords));
	vec3 light = clamp(blinnPhong(), ambientStrength, 1);

	fFragColor = tex * light;
};
