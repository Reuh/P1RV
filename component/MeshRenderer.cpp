#include <GL/glew.h>
#include "MeshRenderer.hpp"
#include "Shader.hpp"
#include "BoxCollider.hpp"

#include <iostream>

MeshRenderer::MeshRenderer(vector<Vertex> vertices, vector<unsigned int> indices, Material material) {
    this->vertices = vertices;
    this->indices = indices;
    this->material = material;

    // setup mesh
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex color
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

    glBindVertexArray(0);

    // calculate bounds
    lb = vertices[0].Position;
    rt = vertices[0].Position;
    for (auto v : vertices) {
        auto pos = v.Position;
        lb.x = std::min(lb.x, pos.x);
        lb.y = std::min(lb.y, pos.y);
        lb.z = std::min(lb.z, pos.z);
        rt.x = std::max(rt.x, pos.x);
        rt.y = std::max(rt.y, pos.y);
        rt.z = std::max(rt.z, pos.z);
    }
}

BoxCollider* MeshRenderer::makeCollider(bool rigid) {
    return new BoxCollider(rigid, lb, rt);
}

void MeshRenderer::render(Shader* shader) {
    // bind texture & send material data
    sf::Texture::bind(&material.textureDiffuse.tex);
    shader->sendUniform("material.hasTexture", material.hasTexture);
    shader->sendUniform("material.diffuseColor", material.diffuseColor);
    shader->sendUniform("material.ambientColor", material.ambientColor);
    shader->sendUniform("material.specularColor", material.specularColor);
    shader->sendUniform("material.shininess", material.shininess);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    sf::Texture::bind(NULL);
}
