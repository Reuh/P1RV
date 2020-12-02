#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColor;

out vec2 TexCoords;
out vec4 Color;

uniform mat4 modelViewProjection;

void main()
{
    TexCoords = aTexCoords;
    Color = aColor;
    gl_Position = modelViewProjection * vec4(aPos, 1.0);
}