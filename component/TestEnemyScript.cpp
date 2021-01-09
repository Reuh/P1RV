#include <iostream>
#include <random>
#include <SFML/Audio.hpp>
#include <glm/glm.hpp>
#include "TestEnemyScript.hpp"
#include "Script.hpp"
#include "GameObject.hpp"
#include "NavMeshNavigator.hpp"
#include "Collider.hpp"
#include "scene/Scene.hpp"
#include "RelicScript.hpp"

// some global sound buffers and sounds for sfx
sf::SoundBuffer hitBuffer;
sf::Sound hitSound;

TestEnemyScript::TestEnemyScript(GameObject * player, GameObject* relic) {
    this->player = player;
    this->relic = relic;
}

void TestEnemyScript::start() {
    // Load sounds
    if (!hitBuffer.loadFromFile("sounds/littlerobotsoundfactory-robot1.wav"))
        std::cout << "ERROR: can't load sound sounds/littlerobotsoundfactory-robot1.wav" << std::endl;
    hitSound.setBuffer(hitBuffer);
}

void TestEnemyScript::update(float dt) {
	// Check if there are no rigid object between us and the player (ie we see them)
    bool playerVisible = true;
    // search objects intersecting with the ray going from this object to the player
    glm::vec3 position = object->getTransform()->getPosition();
    glm::vec3 playerDirection = player->getTransform()->getPosition() - position; // TODO: use the enemy eye direction
    glm::vec3 ray = glm::normalize(playerDirection);
    float playerDistance = player->getComponent<Collider>()->collideRayDistance(position, ray);
    if (playerDistance >= 0) {
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
	} else {
		playerVisible = false;
	}
    // Act if player in sight
    auto navigator = object->getComponent<NavMeshNavigator>();
    playerVisible = false;
    if (playerVisible) {
        if (glm::length(playerDirection) < 5) {
            std::uniform_int_distribution<int> random(0, 999);
            std::random_device rd;
            std::mt19937 randomNumbers(rd());
            if (random(randomNumbers) < 50) {
                // Kill Player
                auto playerScript = player->getComponent<Script>();
                if (playerScript != nullptr)
                    playerScript->onHit();
            }
        } else {
            if (glm::length(lastPos - player->getTransform()->getPosition()) > 2) {
                // Chase
                lastPos = player->getTransform()->getPosition();
                navigator->setDestination(lastPos);
            }
        }
    } else {
        glm::vec3 dest = navigator->getDestination();
        if (relic->getComponent<RelicScript>()->isAttached()) {
            // Go to base
            dest = glm::vec3(0,0,-36.5);
        } else {
            dest = relic->getTransform()->getPosition();
        }
        if (navigator->getDestination() != dest) {
            navigator->setDestination(dest);
        }
    }

    // Update position using NavMeshNavigator
	glm::vec3 pos = object->getComponent<NavMeshNavigator>()->nextStep(dt);
    object->getTransform()->setPosition(pos);
}

void TestEnemyScript::onHit() {
    // Release relic
    relic->getComponent<RelicScript>()->reset();

    // Teleport back to base
    auto basePos = glm::vec3(0,0,-36.5);
    object->getTransform()->setPosition(basePos);
    object->getComponent<NavMeshNavigator>()->setDestination(basePos);

	// Play SFX
	glm::vec3 pos = object->getTransform()->getPosition();
	hitSound.setPosition(pos.x, pos.y, pos.z);
	hitSound.play();
}
