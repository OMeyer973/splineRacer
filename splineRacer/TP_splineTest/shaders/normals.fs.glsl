#version 330 core

in  vec4 vFragPosition;
in  vec4 vFragNormal;
in  vec2 vFragTexCoords;

uniform sampler2D uTexture;
out vec3 fFragColor;

void main() {
	fFragColor = normalize((vFragNormal.xyz));
};
