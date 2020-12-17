#version 330 core
out vec3 FragColor;

in vec2 TexCoords;
in vec4 Color; // vertex color
in vec3 Normal; // normal in world space
in vec3 FragPos; // position in world space

struct Material {
	bool hasTexture;
	sampler2D textureDiffuse;
	vec3 diffuseColor;

	vec3 ambientColor;
	vec3 specularColor;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform DirectionalLight light;
uniform vec3 eyePos; // camera position in world space
uniform bool hasLightning;

void main()
{
	vec3 diffuseColor;
	if (!material.hasTexture)
		diffuseColor = material.diffuseColor;
	else
		diffuseColor = vec3(texture(material.textureDiffuse, TexCoords));

	// Calculate lightning //
	if (hasLightning) {
		vec3 normal = normalize(Normal);
		vec3 viewDir = normalize(eyePos - FragPos);

		// Directional lightning
		vec3 lightDir = normalize(-light.direction);
	    // diffuse shading
	    float diff = max(dot(normal, lightDir), 0.0);
	    // specular shading
	    vec3 reflectDir = reflect(-lightDir, normal);
	    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	    // combine results
	    vec3 ambient  = light.ambient  * diffuseColor;
	    vec3 diffuse  = light.diffuse  * diff * diffuseColor;
	    vec3 specular = light.specular * spec * material.specularColor;
	    FragColor = ambient + diffuse + specular;

	    // TODO: point lights
	} else {
		FragColor = diffuseColor;
	}
}
