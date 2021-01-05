#include "TestEnemyScript.hpp"
#include "Script.hpp"
#include <SFML/Audio.hpp>
#include <glm/glm.hpp>
#include "GameObject.hpp"
#include "NavMeshNavigator.hpp"
#include <iostream>

// some global sound buffers and sounds for sfx
sf::SoundBuffer hitBuffer;
sf::Sound hitSound;

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
}

void TestEnemyScript::onHit() {
	std::cout << "Touché!" << std::endl;

	// Play SFX
	glm::vec3 pos = object->getTransform()->getPosition();
	hitSound.setPosition(pos.x, pos.y, pos.z);
	hitSound.play();
}
