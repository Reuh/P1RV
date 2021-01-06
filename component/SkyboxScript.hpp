#ifndef P1RV_SKYBOXSCRIPT_HPP
#define P1RV_SKYBOXSCRIPT_HPP

#include <GameObject.hpp>
#include "Script.hpp"

// Game logic for the skybox (follow player).
class SkyboxScript : public Script {
private:
    GameObject* player;
public:
    SkyboxScript(GameObject* player);
    void update(float dt) override;
};

#endif //P1RV_SKYBOXSCRIPT_HPP
