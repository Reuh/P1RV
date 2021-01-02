//
// Created by iagoc on 30/12/2020.
//

#ifndef P1RV_RELICSCRIPT_HPP
#define P1RV_RELICSCRIPT_HPP

#include <GameObject.hpp>
#include "Script.hpp"

class RelicScript : public Script {
private:
    GameObject* relic;
    GameObject* player;
    bool attached = false;
public:
    RelicScript(GameObject * relic, GameObject * player);
    void update(float dt) override;
};


#endif //P1RV_RELICSCRIPT_HPP
