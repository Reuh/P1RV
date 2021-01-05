#ifndef P1RV_TESTENEMYSCRIPT_H
#define P1RV_TESTENEMYSCRIPT_H

#include "Script.hpp"

class TestEnemyScript : public Script {
public:
	void start() override;

	void update(float dt) override;

	void onHit() override;
};

#endif