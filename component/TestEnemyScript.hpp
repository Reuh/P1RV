#ifndef P1RV_TESTENEMYSCRIPT_H
#define P1RV_TESTENEMYSCRIPT_H

#include "Script.hpp"

// Game logic for the enemy.
class TestEnemyScript : public Script {
private:
	GameObject* player;
public:
	TestEnemyScript(GameObject* player);

	void start() override;

	void update(float dt) override;

	void onHit() override;
};

#endif