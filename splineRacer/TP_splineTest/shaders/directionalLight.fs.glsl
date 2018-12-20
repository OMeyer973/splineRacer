#version 330 core

in vec3 vFragPosition;
in vec3 vFragNormal;

uniform vec3 uLightIntensity;
uniform vec3 uLightDir_vs;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

out vec3 fFragColor;

vec3 blinnPhong() {
	return uLightIntensity * (uKd * dot(normalize(uLightDir_vs), vFragNormal) 
		+ uKs * pow((dot((normalize(-vFragPosition) + normalize(uLightDir_vs)) / 2, vFragNormal)), uShininess));
}

void main() {
	fFragColor = blinnPhong();
};