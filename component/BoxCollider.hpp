#ifndef P1RV_BOXCOLLIDER_H
#define P1RV_BOXCOLLIDER_H

#include "Collider.hpp"
#include <glm/glm.hpp>

using namespace glm;

class BoxCollider : public Collider {
protected:
	vec3 lb; // left-bottom corner (minimal coordinates)
	vec3 rt; // right-top corner (maximal coordinates)
public:
	BoxCollider(bool _rigid, vec3 lb, vec3 rt);

	vec3 getLb();
	vec3 getRt();

	vec3 getTransformedLb();
	vec3 getTransformedRt();

	// Test if ray originating from origing along dir collides with this box.
	// Apply parent transformation.
    virtual bool collideRay(vec3 origin, vec3 dir) override;

    // Test if collides with another box
    // Apply parent transformation.
    virtual bool collideBox(BoxCollider* box) override;
};

#endif //P1RV_BOXCOLLIDER_H
