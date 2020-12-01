#ifndef P1RV_BOXCOLLIDER_H
#define P1RV_BOXCOLLIDER_H

#include "Component.h"
#include <glm/glm.hpp>
#include <algorithm>

using namespace glm;

class BoxCollider : public Component {
protected:
	vec3 lb; // left-bottom corner (minimal coordinates)
	vec3 rt; // right-top corner (maximal coordinates)
public:
	BoxCollider(vec3 lb, vec3 rt) {
		this->lb = lb;
		this->rt = rt;
	}

    bool collideRay(vec3 origin, vec3 dir) {
    	vec3 dirfrac;
		dirfrac.x = 1.0f / dir.x;
		dirfrac.y = 1.0f / dir.y;
		dirfrac.z = 1.0f / dir.z;

		float t1 = (lb.x - origin.x)*dirfrac.x;
		float t2 = (rt.x - origin.x)*dirfrac.x;
		float t3 = (lb.y - origin.y)*dirfrac.y;
		float t4 = (rt.y - origin.y)*dirfrac.y;
		float t5 = (lb.z - origin.z)*dirfrac.z;
		float t6 = (rt.z - origin.z)*dirfrac.z;

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
