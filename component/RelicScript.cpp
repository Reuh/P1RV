//
// Created by iagoc on 30/12/2020.
//

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/scalar_multiplication.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "RelicScript.hpp"


RelicScript::RelicScript(GameObject * relic, GameObject * player) {
    this->relic = relic;
    this->player = player;
}

void RelicScript::update(float dt) {
    auto relicPos = relic->getTransform()->getPosition();
    //std::cout << "R " << relicPos.x << " : " << relicPos.y << " : " << relicPos.z << std::endl;
    auto playerPos = player->getTransform()->getPosition();
    //std::cout << "P " << playerPos.x << " : " << playerPos.y << " : " << playerPos.z << std::endl;
    if (this->attached) {
        auto t = glm::rotateY(player->getTransform()->getFront(), glm::radians(30.f));
        relic->getTransform()->setPosition(player->getTransform()->getPosition() + 0.25 * t + glm::vec3(0, -.1, 0));
        // TODO : Rotate relic to follow the camera orientation

        // TODO : Check if relic inside target zone
    } else {
        auto distance = relicPos - playerPos;
        // std::cout << glm::length(distance) << std::endl;
        if (glm::length(distance) <= 1.1) {
            attached = true;
            relic->getTransform()->scale(glm::vec3(0.2, 0.2, 0.2));
        }
    }
}


