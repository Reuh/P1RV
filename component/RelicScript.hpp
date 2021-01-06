//
// Created by iagoc on 30/12/2020.
//

#ifndef P1RV_RELICSCRIPT_HPP
#define P1RV_RELICSCRIPT_HPP

#include <GameObject.hpp>
#include "Script.hpp"

// Game logic for the flag.
class RelicScript : public Script {
private:
    GameObject* relic;
    GameObject* player;

    glm::vec3 destination;
    glm::vec3 originalPosition;

    bool attached = false;
public:
    RelicScript(GameObject * relic, GameObject * player, glm::vec3 destination);
    void update(float dt) override;
    bool isAttached();
    void reset();
};


#endif //P1RV_RELICSCRIPT_HPP
