#version 330 core

in vec2 vFragTexCoords;
uniform sampler2D uTexture;

out vec3 fFragColor;

void main() {
	fFragColor = (texture(uTexture, vFragTexCoords)).xyz;
};
