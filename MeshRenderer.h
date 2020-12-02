#ifndef P1RV_MESHRENDERER_H
#define P1RV_MESHRENDERER_H

#include "Renderer.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

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

class MeshRenderer : public Renderer {
private:
	//  render data
    unsigned int VAO, VBO, EBO;

public:
	// mesh data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    Texture              texture;

    MeshRenderer(vector<Vertex> vertices, vector<unsigned int> indices, Texture texture);

    void render() override;
};

#endif //P1RV_MESHRENDERER_H
