#ifndef P1RV_MESHRENDERER_H
#define P1RV_MESHRENDERER_H

#include "Renderer.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Shader.hpp"

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec4 Color;
};

struct Texture {
    sf::Texture tex;
    string path;
};

struct Material {
    bool hasTexture;
    Texture textureDiffuse;
    glm::vec3 diffuseColor;

    glm::vec3 ambientColor;
    glm::vec3 specularColor;
    float shininess;
};

class MeshRenderer : public Renderer {
private:
	//  render data
    unsigned int VAO, VBO, EBO;

public:
	// mesh data
    vector<Vertex>       vertices; // vertex list
    vector<unsigned int> indices; // vertex indice draw order
    Material             material; // mesh material

    MeshRenderer(vector<Vertex> vertices, vector<unsigned int> indices, Material material);

    void render(Shader* shader) override;
};

#endif //P1RV_MESHRENDERER_H
