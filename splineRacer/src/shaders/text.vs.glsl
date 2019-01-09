#version 330 core

// In
layout (location = 0) in vec4 aVertex;

// Out
out vec2 vTexCoords;

uniform mat4 uProjection;

void main()
{
    gl_Position = uProjection * vec4(aVertex.xy, 0.0, 1.0);
    vTexCoords = aVertex.zw;
} 
