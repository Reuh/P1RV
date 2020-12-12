#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec4 Color;

uniform sampler2D textureDiffuse;
uniform vec3 diffuseColor;

void main()
{
	vec4 baseColor;
	if (TexCoords.x == -1)
    	baseColor = vec4(1.0,1.0,1.0,1.0);
    else
    	baseColor = vec4(diffuseColor, 1.0);

    FragColor = baseColor * Color;
}
