#version 330 core

in vec2 vFragTexture;

out vec3 fFragColor;

uniform vec3 uColor;

uniform sampler2D uTexture;

void main() {
  //fFragColor = vec3(1,0,0);
  //fFragColor = uColor;
  fFragColor = texture(uTexture, vFragTexture).xyz;
};
