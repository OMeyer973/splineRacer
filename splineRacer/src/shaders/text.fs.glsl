#version 330 core

// In
in vec2 vTexCoords;

// Out
out vec4 fFragColor;

uniform sampler2D uTexture;
uniform vec3 uTextColor;

void main()
{
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uTexture, vTexCoords).r);
  fFragColor = vec4(uTextColor, 1.0) * sampled;
}
