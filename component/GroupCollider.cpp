#include "GroupCollider.hpp"
#include "Collider.hpp"
#include <glm/glm.hpp>

using namespace glm;

#include <iostream>

GroupCollider::GroupCollider(bool _rigid) : Collider(_rigid) {
}

void GroupCollider::addCollider(Collider* col) {
	col->object = object;
	colliders.push_back(col);
}

bool GroupCollider::collideRay(vec3 origin, vec3 dir) {
	for (Collider* col : colliders) {
		if (col->collideRay(origin, dir))
			return true;
	}
	return false;
}
float GroupCollider::collideRayDistance(vec3 origin, vec3 dir) {
	float tmin = -1;
	// Try to find closest intersection among all colliders in this group.
	for (Collider* col : colliders) {
		float dist = col->collideRayDistance(origin, dir);
		if (dist >= 0) {
			if (tmin >= 0)
				tmin = std::min(tmin, dist);
			else
				tmin = dist;
		}
	}
	return tmin;
}

bool GroupCollider::collideBox(BoxCollider* box) {
	for (Collider* col : colliders) {
		if (col->collideBox(box))
			return true;
	}
	return false;
}
