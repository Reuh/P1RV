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
