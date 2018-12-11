#version 330 core

in  vec4 vFragPosition;
in  vec4 vFragNormal;
in  vec2 vFragTexCoords;

out vec3 fFragColor;

void main() {
	fFragColor = normalize(vFragNormal.xyz);
};
