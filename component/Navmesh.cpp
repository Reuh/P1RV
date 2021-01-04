//
// Created by iagoc on 03/01/2021.
//

#include "Navmesh.hpp"

Navmesh::Navmesh(const std::string &filename) {
    Assimp::Importer import;
    auto scene = import.ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    if (scene->mRootNode->mNumChildren <= 0) {
        std::cerr << "ERROR::Navmesh::Source file must have one child." << std::endl;
        return;
    }

    generateGraph(scene->mMeshes[scene->mRootNode->mChildren[0]->mMeshes[0]]);
    delete scene;
}

void Navmesh::generateGraph(aiMesh *source) {

    // Loads all vertices
    for(unsigned int i = 0; i < source->mNumVertices; i++) {
        vertex t;
        t.pos = glm::vec3(source->mVertices[i].x, source->mVertices[i].y, source->mVertices[i].z);
        vertices.push_back(t);
    }

    // Loads all faces
    for(unsigned int i = 0; i < source->mNumFaces; i++)
    {
        aiFace face = source->mFaces[i];
        node t;
        t.v1 = &(vertices[face.mIndices[0]].pos);
        t.v2 = &(vertices[face.mIndices[1]].pos);
        t.v3 = &(vertices[face.mIndices[2]].pos);
        mesh.push_back(t);

        vertices[face.mIndices[0]].nodes.push_back(mesh.size() - 1);
        vertices[face.mIndices[1]].nodes.push_back(mesh.size() - 1);
        vertices[face.mIndices[2]].nodes.push_back(mesh.size() - 1);
    }

    for (unsigned int i = 0; i < mesh.size(); i++) {
        for (unsigned int j = i + 1; j < mesh.size(); j++) {
            unsigned matches = (mesh[i].v1 == mesh[j].v1) +
                    (mesh[i].v1 == mesh[j].v2) +
                    (mesh[i].v1 == mesh[j].v3) +
                    (mesh[i].v2 == mesh[j].v1) +
                    (mesh[i].v2 == mesh[j].v2) +
                    (mesh[i].v2 == mesh[j].v3) +
                    (mesh[i].v3 == mesh[j].v1) +
                    (mesh[i].v3 == mesh[j].v2) +
                    (mesh[i].v3 == mesh[j].v3);
            if (matches >= 2) {
                // Se o nó não foi encontrado no outro, adicionar
                bool found = false;
                for (node* n : mesh[i].nodes) {
                    if (n == &mesh[j]) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    mesh[i].nodes.push_back(&mesh[j]);
                    mesh[j].nodes.push_back(&mesh[i]);
                }
            }
        }
    }
}

bool Navmesh::pointInsideTriangle(const node & triangle, const glm::vec3 & point) {
    glm::vec3 v0 = * triangle.v2 - * triangle.v1;
    glm::vec3 v1 = * triangle.v3 - * triangle.v1;
    glm::vec3 v2 = point - * triangle.v1;

    float d00 = glm::dot(v0, v0);
    float d01 = glm::dot(v0, v1);
    float d02 = glm::dot(v0, v2);
    float d11 = glm::dot(v1, v1);
    float d12 = glm::dot(v1, v2);

    float inv = 1 / (d00 * d11 - d01 + d01);
    float u = (d11 * d02 - d01 * d12) * inv;
    float v = (d00 * d12 - d01 * d02) * inv;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}

struct openPoint {
    glm::vec3 * begin, * end;
    float g, h;
};

bool compare(const openPoint &a, const openPoint &b) {
    return (a.g + a.h) < (b.g + b.h);
}

inline bool vertexOfTriangle(glm::vec3 & _vertex, node & triangle) {
    return _vertex == *triangle.v1 || _vertex == *triangle.v2 || _vertex == *triangle.v3;
}

// Should probably use pointers here
vertex & Navmesh::findVertex(const glm::vec3 & coord) {
    for (auto & v : vertices) {
        if (v.pos == coord) {
            return v;
        }
    }
}

openPoint * findInOpenPoints(std::vector<openPoint> & openPoints, glm::vec3 & coord) {
    for (openPoint & p : openPoints) {
        if (*p.end == coord) return &p;
    }
    return nullptr;
}

std::vector<std::pair<glm::vec3, glm::vec3>> Navmesh::findPath(glm::vec3 & begin, glm::vec3 & end) {
    std::vector<std::pair<glm::vec3, glm::vec3>> result;
    // Find triangle of the starting point
    node* beginTriangle = nullptr;
    for (auto & n : mesh) {
        if (pointInsideTriangle(n, begin)) {
            beginTriangle = &n;
            break;
        }
    }
    // Find triangle of the ending point
    node* endTriangle = nullptr;
    for (auto & n : mesh) {
        if (pointInsideTriangle(n, end)) {
            endTriangle = &n;
            break;
        }
    }
    // Find the path between the two
    if (beginTriangle != nullptr && endTriangle != nullptr) {
        result.emplace_back(begin, begin);
        if (beginTriangle != endTriangle) {
            // Run the A* search algorithm

            std::vector<openPoint> openPoints;
            float totalDistance = 0;
            openPoints.push_back({&begin, beginTriangle->v1, distance(begin, *beginTriangle->v1), distance(end, *beginTriangle->v1)});
            openPoints.push_back({&begin, beginTriangle->v2, distance(begin, *beginTriangle->v2), distance(end, *beginTriangle->v2)});
            openPoints.push_back({&begin, beginTriangle->v3, distance(begin, *beginTriangle->v3), distance(end, *beginTriangle->v3)});

            auto shortest = std::min_element(openPoints.begin(), openPoints.end(), compare);
            result.emplace_back(result.back().second, *shortest->end);
            totalDistance += distance(*shortest->begin, *shortest->end);
            openPoints.erase(shortest);

            // TODO : Optimize using a binaryHeap
            while (!vertexOfTriangle(result.back().second, *endTriangle)) {
                auto v = findVertex(result.back().second);
                // Para cada face conectada ao vértice
                for (auto n : v.nodes) {
                    openPoint * p;
                    // Se os vértices estiverem em openPoints
                    if (*mesh[n].v1 != result.back().second) {
                        p = findInOpenPoints(openPoints, *mesh[n].v1);
                        if (p != nullptr) {
                            float cost = distance(result.back().second, *mesh[n].v1);
                            if (cost < p->g) {
                                p->begin = &result.back().second;
                                p->g = totalDistance + cost;
                            }
                        } else {
                            // Add vertex
                            openPoints.push_back({&result.back().second, mesh[n].v1, totalDistance + distance(result.back().second, *mesh[n].v1), distance(*mesh[n].v1, end)});
                        }
                    }
                    // Refazer para mesh[n].v2
                    if (*mesh[n].v2 != result.back().second) {
                        p = findInOpenPoints(openPoints, *mesh[n].v2);
                        if (p != nullptr) {
                            float cost = distance(result.back().second, *mesh[n].v2);
                            if (cost < p->g) {
                                p->begin = &result.back().second;
                                p->g = totalDistance + cost;
                            }
                        } else {
                            // Add vertex
                            openPoints.push_back({&result.back().second, mesh[n].v2, totalDistance + distance(result.back().second, *mesh[n].v2), distance(*mesh[n].v2, end)});
                        }
                    }
                    // Refazer para mesh[n].v3
                    if (*mesh[n].v3 != result.back().second) {
                        p = findInOpenPoints(openPoints, *mesh[n].v3);
                        if (p != nullptr) {
                            float cost = distance(result.back().second, *mesh[n].v3);
                            if (cost < p->g) {
                                p->begin = &result.back().second;
                                p->g = totalDistance + cost;
                            }
                        } else {
                            // Add vertex
                            openPoints.push_back({&result.back().second, mesh[n].v3, totalDistance + distance(result.back().second, *mesh[n].v3), distance(*mesh[n].v3, end)});
                        }
                    }
                }

                shortest = std::min_element(openPoints.begin(), openPoints.end(), compare);
                result.emplace_back(*shortest->begin, *shortest->end);
                totalDistance += distance(*shortest->begin, *shortest->end);
                openPoints.erase(shortest);
            }
        }
        result.emplace_back(end, end);
    } else {
         std::cerr << "ERROR::Navmesh::Points outside of the navmesh." << std::endl;
    }

    int i = 0;
    while (true) {
        if (i + 1 > result.size()) break;
        if (result[i].second == result[i + 1].first) i++;
        else result.erase(result.begin() + i + 1);
    }

    // TODO : Probably clean up the path from some unnecessary points
    // Run by all the points and check if you can skip the next point without falling off the navmesh

    return result;
}

int Navmesh::numberOfVertices() {
    return vertices.size();
}

int Navmesh::numberOfFaces() {
    return mesh.size();
}

float Navmesh::distance(const glm::vec3 & begin, const glm::vec3 & end) {
    return glm::length(begin - end);
}
