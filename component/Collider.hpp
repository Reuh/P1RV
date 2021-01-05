#ifndef P1RV_COLLIDER_H
#define P1RV_COLLIDER_H


#include "Component.hpp"
#include <glm/glm.hpp>

class BoxCollider;

class Collider : public Component {
private:
    bool rigid;
public:
    // TODO : Use only one collide function with different signatures
    explicit Collider(bool _rigid) {
        this->rigid = _rigid;
    }
    bool isRigid() const {
        return this->rigid;
    }
    void setRigid(bool _rigid) {
        this->rigid = _rigid;
    }
    virtual bool collideRay(glm::vec3 origin, glm::vec3 dir) = 0;
    virtual bool collideBox(BoxCollider* box) = 0;
};


#endif //P1RV_COLLIDER_H
