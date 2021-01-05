#include "TestEnemyScript.hpp"
#include "Script.hpp"
#include <SFML/Audio.hpp>
#include <glm/glm.hpp>
#include "GameObject.hpp"
#include "NavMeshNavigator.hpp"
#include <iostream>
#include "Collider.hpp"
#include "scene/Scene.hpp"

// some global sound buffers and sounds for sfx
sf::SoundBuffer hitBuffer;
sf::Sound hitSound;

TestEnemyScript::TestEnemyScript(GameObject * player) {
    this->player = player;
}

void TestEnemyScript::start() {
    // Load sounds
    if (!hitBuffer.loadFromFile("sounds/littlerobotsoundfactory-robot1.wav"))
        std::cout << "ERROR: can't load sound sounds/littlerobotsoundfactory-robot1.wav" << std::endl;
    hitSound.setBuffer(hitBuffer);
}

void TestEnemyScript::update(float dt) {
    glm::vec3 begin = glm::vec3(-0.5, 0, -0.5);
    glm::vec3 end = glm::vec3(-0.5, 0, -4);
	auto enemy = this->object;
	glm::vec3 pos = enemy->getComponent<NavMeshNavigator>()->nextStep(dt);
    std::cout << pos.x << " : " << pos.y << " : " << pos.z << std::endl;
	enemy->getTransform()->setPosition(pos);
	if (enemy->getTransform()->getPosition() == begin) {
        enemy->getComponent<NavMeshNavigator>()->setDestination(end);
	} else if (enemy->getTransform()->getPosition() == end) {
        enemy->getComponent<NavMeshNavigator>()->setDestination(begin);
	}

	// Check if there are no rigid object between us and the player (ie we see them)
    bool playerVisible = true;
    // search objects intersecting with the ray going from this object to the player
    glm::vec3 position = object->getTransform()->getPosition();
    glm::vec3 playerDirection = player->getTransform()->getPosition() - position;
    float playerDistance = glm::length(playerDistance);
    glm::vec3 ray = glm::normalize(playerDirection);
    auto objList = object->scene->getObjectList();
    for(auto & iter : *objList) {
        if (iter != object) {
            auto coll = iter->getComponent<Collider>();
            if (coll != nullptr && coll->isRigid()) {
                float dist = coll->collideRayDistance(position, ray);
                if (dist >= 0) {
                	if (dist < playerDistance) { // the rigid object is between us and the player
                		playerVisible = false;
                		break;
                	}
                }
            }
        }
    }
    // Act on first hit object, if any
    if (playerVisible) {
    	// do stuff
    }
}

void TestEnemyScript::onHit() {
	std::cout << "Touché!" << std::endl;

	// Play SFX
	glm::vec3 pos = object->getTransform()->getPosition();
	hitSound.setPosition(pos.x, pos.y, pos.z);
	hitSound.play();
}
