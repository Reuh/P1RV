#include "TestEnemyScript.hpp"
#include "Script.hpp"

#include <iostream>

void TestEnemyScript::update(float dt) {
	// update IA and stuff
}

void TestEnemyScript::onHit() {
	std::cout << "Touché!" << std::endl;
}
