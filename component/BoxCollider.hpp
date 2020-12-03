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
	BoxCollider(vec3 lb, vec3 rt);

	// Test if ray originating from origing along dir collides with this box.
    bool collideRay(vec3 origin, vec3 dir) override;
};

#endif //P1RV_BOXCOLLIDER_H
