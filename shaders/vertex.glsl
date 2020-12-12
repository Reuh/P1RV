#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColor;

out vec2 TexCoords;
out vec4 Color;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 viewProjection;

void main()
{
    TexCoords = aTexCoords;
    Color = aColor;
    Normal = aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = viewProjection * vec4(FragPos, 1.0);
}