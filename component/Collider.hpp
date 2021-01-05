#ifndef P1RV_COLLIDER_H
#define P1RV_COLLIDER_H


#include "Component.hpp"
#include <glm/glm.hpp>

class BoxCollider;

// Base class for colliders.
class Collider : public Component {
private:
    bool rigid;
public:
    // TODO : Use only one collide function with different signatures
    explicit Collider(bool _rigid) {
        this->rigid = _rigid;
    }

    // A rigid collider will induce physical collisions, ie block the player and bullets
    bool isRigid() const {
        return this->rigid;
    }
    void setRigid(bool _rigid) {
        this->rigid = _rigid;
    }

    // Test if ray originating from origing along dir collides with this collider.
    // Apply parent transformation.
    virtual bool collideRay(glm::vec3 origin, glm::vec3 dir) {
        return collideRayDistance(origin, dir) >= 0;
    };
    // Same but return the distance at which the ray intersected starting from origin. -1 if it didn't intersect.
    virtual float collideRayDistance(glm::vec3 origin, glm::vec3 dir) = 0;

    // Test if collides with another box
    // Apply parent transformation.
    virtual bool collideBox(BoxCollider* box) = 0;
};


#endif //P1RV_COLLIDER_H
