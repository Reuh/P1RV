//
// Created by iagoc on 03/01/2021.
//

#ifndef P1RV_NAVMESH_HPP
#define P1RV_NAVMESH_HPP


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

struct node {
    // Should probably change this (v1, v2, v3) into an array to make code cleaner
    glm::vec3 * v1, * v2, * v3;
    std::vector<node*> nodes;
};

struct vertex {
    glm::vec3 pos;
    std::vector<unsigned> nodes;
};

class NavMesh {
private:
    std::vector<vertex> vertices;
    std::vector<node> mesh;
    void generateGraph(aiMesh *mesh);
    static bool pointInsideTriangle(const node & triangle, const glm::vec3 & point);
    static inline float distance(const glm::vec3 & begin, const glm::vec3 & end);
    vertex & findVertex(const glm::vec3 & coord);
public:
    explicit NavMesh(const std::string & filename);
    std::vector<std::pair<glm::vec3, glm::vec3>> findPath(glm::vec3 & begin, glm::vec3 & end);
    int numberOfVertices();
    int numberOfFaces();
};


#endif //P1RV_NAVMESH_HPP
