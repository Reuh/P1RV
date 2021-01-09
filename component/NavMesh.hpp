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
#include <glm/gtx/scalar_multiplication.hpp>

struct node {
    // TODO : Change to support different vertex sizes
    glm::vec3 vertices[3];
    // TODO : Add barycenter here
    std::vector<int> nodes;
};

class NavMesh {
private:
    std::vector<node> mesh;
    void generateGraph(aiMesh *mesh);
public:
    explicit NavMesh(const std::string & filename);
    std::vector<glm::vec3> findPath(glm::vec3 & begin, glm::vec3 & end);
    int numberOfNodes();
};


#endif //P1RV_NAVMESH_HPP
