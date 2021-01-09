//
// Created by iagoc on 05/01/2021.
//

#ifndef P1RV_NAVMESHNAVIGATOR_HPP
#define P1RV_NAVMESHNAVIGATOR_HPP


#include "NavMesh.hpp"
#include "Component.hpp"

class NavMeshNavigator : public Component {
private:
    NavMesh * navMesh;
    glm::vec3 destination{};
    std::vector<glm::vec3> path;
    float walkingSpeed = 3;
    float turningSpeed = 5;
    unsigned lastPoint = 0;
    double totalDistance = 0;
    double lastDistance = 0;
public:
    explicit NavMeshNavigator(NavMesh * navMesh);
    glm::vec3 nextStep(float dt);
    void setDestination(glm::vec3 & vec);
    glm::vec3 getDestination();
    void setWalkingSpeed(float speed);
    void setTurningSpeed(float speed);
};


#endif //P1RV_NAVMESHNAVIGATOR_HPP
