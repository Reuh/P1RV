#ifndef P1RV_BOXCOLLIDER_H
#define P1RV_BOXCOLLIDER_H

#include "Collider.hpp"
#include <glm/glm.hpp>
#include <algorithm>
#include "Transform.hpp"

using namespace glm;

class BoxCollider : public Collider {
protected:
	vec3 lb; // left-bottom corner (minimal coordinates)
	vec3 rt; // right-top corner (maximal coordinates)
public:
	BoxCollider(vec3 lb, vec3 rt) {
		this->lb = lb;
		this->rt = rt;
	}

    bool collideRay(vec3 origin, vec3 dir) {
    	// Apply Transform to box (FIXME: should probably ignore rotation)
    	Transform* tr = object->getTransform();
    	vec3 lb2 = tr->getMatrix() * vec4(lb, 1.f);
    	vec3 rt2 = tr->getMatrix() * vec4(rt, 1.f);

    	// Test
    	vec3 dirfrac;
		dirfrac.x = 1.0f / dir.x;
		dirfrac.y = 1.0f / dir.y;
		dirfrac.z = 1.0f / dir.z;

		float t1 = (lb2.x - origin.x)*dirfrac.x;
		float t2 = (rt2.x - origin.x)*dirfrac.x;
		float t3 = (lb2.y - origin.y)*dirfrac.y;
		float t4 = (rt2.y - origin.y)*dirfrac.y;
		float t5 = (lb2.z - origin.z)*dirfrac.z;
		float t6 = (rt2.z - origin.z)*dirfrac.z;

		float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
		float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

		if (tmax < 0) {
		    return false; // box behind ray
		}

		if (tmin > tmax) {
		    return false; // no intersection
		}

		return true;
    }
};

#endif //P1RV_BOXCOLLIDER_H
