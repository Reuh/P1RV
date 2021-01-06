#include "SkyboxScript.hpp"

SkyboxScript::SkyboxScript(GameObject * player) {
    this->player = player;
}

void SkyboxScript::update(float dt) {
    object->getTransform()->setPosition(player->getTransform()->getPosition());
}
