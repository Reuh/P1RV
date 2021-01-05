#ifndef P1RV_GROUPCOLLIDER_H
#define P1RV_GROUPCOLLIDER_H

#include "Collider.hpp"
#include <glm/glm.hpp>
#include <vector>

using namespace glm;

// Collection of colliders.
class GroupCollider : public Collider {
protected:
	std::vector<Collider*> colliders;
public:
	GroupCollider(bool _rigid);

	void addCollider(Collider* col);

	// Test if ray originating from origing along dir collides with the group collider.
	// Apply parent transformation.
	virtual bool collideRay(vec3 origin, vec3 dir) override;
    virtual float collideRayDistance(vec3 origin, vec3 dir) override;

    // Test if collides with another box
    // Apply parent transformation.
    virtual bool collideBox(BoxCollider* box) override;
};

#endif //P1RV_GROUPCOLLIDER_H
