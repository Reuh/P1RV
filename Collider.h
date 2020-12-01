#ifndef P1RV_COLLIDER_H
#define P1RV_COLLIDER_H


#include "Component.h"
#include <glm/glm.hpp>

class Collider : public Component {
public:
    virtual bool collideRay(glm::vec3 origin, glm::vec3 dir) = 0;
};


#endif //P1RV_COLLIDER_H
