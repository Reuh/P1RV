#ifndef P1RV_TESTENEMYIA_H
#define P1RV_TESTENEMYIA_H

#include "Script.hpp"

class TestEnemyIA : public Script {
public:
	void update(float dt) override;

	void onHit() override;
};

#endif