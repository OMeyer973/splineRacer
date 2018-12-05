#version 330 core
#define M_PI 3.1415926535897932384626433832795

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec4 vFragPosition;
out vec4 vFragNormal;
out vec2 vFragTexCoords;


void main() {
  vFragPosition = uMVMatrix * vec4(aVertexPosition,1);
  vFragNormal = uNormalMatrix * vec4(aVertexNormal,0);
  vFragTexCoords = aVertexTexCoords;

  gl_Position = uMVPMatrix * vec4(aVertexPosition,1);

};