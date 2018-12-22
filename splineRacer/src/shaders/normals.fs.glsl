#version 330 core

in vec3 vFragPosition;
in vec3 vFragNormal;
in vec2 vFragTexCoords;

out vec3 fFragColor;

void main() {
	fFragColor = normalize(vFragNormal.xyz);
	// fFragColor = vec3(1, 0, 0);
};
