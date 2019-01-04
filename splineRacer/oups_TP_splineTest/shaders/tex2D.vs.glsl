#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexture;

uniform mat3 uModelMatrix;


out vec2 vFragPosition;
out vec2 vFragTexture;

void main() {
  	vFragTexture = aVertexTexture;
  	vFragPosition = aVertexPosition;
  	vec2 transformed = (uModelMatrix * vec3(aVertexPosition, 1)).xy;
  	gl_Position = vec4(transformed, 0, 1);
};
