//
// Created by iagoc on 05/01/2021.
//

#include <glm/glm.hpp>
#include <glm/gtx/scalar_multiplication.hpp>
#include "GameObject.hpp"
#include "NavMeshNavigator.hpp"

NavMeshNavigator::NavMeshNavigator(NavMesh * navMesh) {
    this->navMesh = navMesh;
}

glm::vec3  NavMeshNavigator::nextStep(float dt) {
    if (path.size() > 1 && lastPoint < path.size() - 1) {
        glm::vec3 direction = path[lastPoint + 1].second - path[lastPoint].second;
        totalDistance += walkingSpeed * dt;
        double deltaDistance = totalDistance - lastDistance;

        while (deltaDistance > glm::length(direction)) {
            lastPoint++;
            if (lastPoint >= path.size() - 1) {
                lastPoint = path.size() - 1;
                break;
            }
            direction = path[lastPoint].second - path[lastPoint - 1].second;
            lastDistance += glm::length(direction);
            deltaDistance = totalDistance - lastDistance;
        }
        if (lastPoint == path.size() - 1) {
            return path.back().second;
        } else {
            return path[lastPoint].second + glm::normalize(direction) * (deltaDistance + walkingSpeed * dt / glm::length(direction));
        }
    } else {
        return object->getTransform()->getPosition();
    }
}

void NavMeshNavigator::setDestination(glm::vec3 & vec) {
    this->destination = vec;
    auto begin = this->object->getTransform()->getPosition();
    //this->path = navMesh->findPath(begin, this->destination);
    totalDistance = 0;
    lastDistance = 0;
    lastPoint = 0;
}

void NavMeshNavigator::setWalkingSpeed(float speed) {
    this->walkingSpeed = speed;
}

void NavMeshNavigator::setTurningSpeed(float speed) {
    this->turningSpeed = speed;
}

glm::vec3 NavMeshNavigator::getDestination() {
    return this->destination;
}
