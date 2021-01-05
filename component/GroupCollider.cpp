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

bool GroupCollider::collideBox(BoxCollider* box) {
	for (Collider* col : colliders) {
		if (col->collideBox(box))
			return true;
	}
	return false;
}
