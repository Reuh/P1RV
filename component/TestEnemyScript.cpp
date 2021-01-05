#include "TestEnemyScript.hpp"
#include "Script.hpp"
#include <SFML/Audio.hpp>
#include <glm/glm.hpp>
#include "GameObject.hpp"

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
	// update IA and stuff
}

void TestEnemyScript::onHit() {
	std::cout << "Touché!" << std::endl;

	// Play SFX
	glm::vec3 pos = object->getTransform()->getPosition();
	hitSound.setPosition(pos.x, pos.y, pos.z);
	hitSound.play();
}
