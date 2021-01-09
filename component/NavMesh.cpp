//
// Created by iagoc on 03/01/2021.
//

#include "NavMesh.hpp"

NavMesh::NavMesh(const std::string &filename) {
    Assimp::Importer import;
    auto scene = import.ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        // TODO : Throw a warning
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    if (scene->mRootNode->mNumChildren <= 0) {
        // TODO : Throw a warning
        std::cerr << "ERROR::NavMesh::Source file must have one child." << std::endl;
        return;
    }

    generateGraph(scene->mMeshes[scene->mRootNode->mChildren[0]->mMeshes[0]]);
}

int countMatches(node * n1, node * n2) {
    int c = 0;
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            c += (n1->vertices[i] == n2->vertices[j]);
        }
    }
    return c;
}

void NavMesh::generateGraph(aiMesh *source) {
    // Loads all faces
    for(int i = 0; i < source->mNumFaces; i++)
    {
        aiFace face = source->mFaces[i];
        node t;
        int v = 0;
        for (int j = 0; j < face.mNumIndices; j++) {
            t.vertices[v++] = glm::vec3(source->mVertices[face.mIndices[j]].x, source->mVertices[face.mIndices[j]].y, source->mVertices[face.mIndices[j]].z);
        }
        mesh.push_back(t);
    }

    // Create links between faces
    for (int i = 0; i < mesh.size(); i++) {
        for (int j = i + 1; j < mesh.size(); j++) {
            if (countMatches(&mesh[i], &mesh[j]) >= 2) {
                // The two nodes share an edge
                bool found = false;
                for (auto n : mesh[i].nodes) {
                    if (n == j) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    mesh[i].nodes.push_back(j);
                    mesh[j].nodes.push_back(i);
                }
            }
        }
    }
}

float distance(const glm::vec3 & begin, const glm::vec3 & end) {
    return glm::length(begin - end);
}

bool pointInsideTriangle(const node & triangle, const glm::vec3 & point) {
    glm::vec3 v0 = triangle.vertices[1] - triangle.vertices[0];
    glm::vec3 v1 = triangle.vertices[2] - triangle.vertices[0];
    glm::vec3 v2 = point - triangle.vertices[0];

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

struct possiblePoint {
    int begin, end;
    float g, h;
};

bool compare(const possiblePoint &a, const possiblePoint &b) {
    return (a.g + a.h) < (b.g + b.h);
}

glm::vec3 barycenter(node * node) {
    glm::vec3 barycenter = (1.f / 2.f) * (node->vertices[0] + node->vertices[1]);
    barycenter = (0.5) * (barycenter + node->vertices[2]);
    return barycenter;
}

int findInPossiblePoints(const std::vector<possiblePoint>& list, int node) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i].end == node) return i;
    }
    return -1;
}

std::vector<glm::vec3> NavMesh::findPath(glm::vec3 & begin, glm::vec3 & end) {
    // TODO : Optimize using a min-heap
    std::vector<std::pair<int, int>> path;
    // Find triangle of the starting point
    int beginNode = -1;
    for (int i = 0; i < mesh.size(); i++) {
        if (pointInsideTriangle(mesh[i], begin)) {
            beginNode = i;
            break;
        }
    }
    // Find triangle of the ending point
    int endNode = -1;
    for (int i = 0; i < mesh.size(); i++) {
        if (pointInsideTriangle(mesh[i], end)) {
            endNode = i;
            break;
        }
    }
    // Find the path between the two
    if (beginNode != -1 && endNode != -1) {
        path.emplace_back(beginNode, beginNode);
        if (beginNode != endNode) {
            // Run the A* search algorithm

            std::vector<possiblePoint> possiblePoints;
            float totalDistance = 0;
            do {
                // put points inside the list
                for (auto node : mesh[path.back().second].nodes) {
                    int nodePos = findInPossiblePoints(possiblePoints, node);
                    float cost = distance(barycenter(&mesh[path.back().second]), barycenter(&mesh[node]));
                    if (nodePos >= 0) {
                        // Update
                        if (cost < possiblePoints[nodePos].g) {
                            possiblePoints[nodePos].begin = path.back().second;
                            possiblePoints[nodePos].g = totalDistance + cost;
                        }
                    } else {
                        possiblePoints.push_back({path.back().second, node, totalDistance + cost,
                            distance(barycenter(&mesh[node]), barycenter(&mesh[endNode]))});
                    }
                }

                // TODO: find shortest
                auto shortest = std::min_element(possiblePoints.begin(), possiblePoints.end(), compare);
                path.emplace_back(shortest->begin, shortest->end);
                totalDistance = shortest->g + distance(barycenter(&mesh[shortest->begin]), barycenter(&mesh[shortest->end]));
                possiblePoints.erase(shortest);
            } while(path.back().second != endNode);
        }
    } else {
         std::cerr << "ERROR::NavMesh::Points outside of the navmesh." << std::endl;
    }

    // Clear path of dead end branches
    int i = path.size() - 1;
    while (true) {
        if (i >= path.size()) i = path.size() - 1;
        if (i - 1 <= 0) break;
        if (path[i].first == path[i - 1].second) i--;
        else path.erase(path.begin() + (i - 1));
    }

    // TODO : Add a string pulling algorithm here
    // Make a list of points
    std::vector<glm::vec3> result;
    for (auto pair : path) {
        result.emplace_back(barycenter(&mesh[pair.second]));
    }
    return result;
}

int NavMesh::numberOfNodes() {
    return mesh.size();
}
