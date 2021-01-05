//
// Created by iagoc on 30/12/2020.
//

#include <iostream>
#include <glm/glm.hpp>
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
        // TODO : Place relic in players field of view
        relic->getTransform()->setPosition(player->getTransform()->getPosition() + glm::vec3(.2, 0, .2));
        // TODO : Check if relic inside target zone
    } else {
        auto distance = relicPos - playerPos;
        // std::cout << glm::length(distance) << std::endl;
        if (glm::length(distance) <= 1.1) {
            attached = true;
        }
    }
}


