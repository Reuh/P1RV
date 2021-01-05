#include "BoxCollider.hpp"
#include <glm/glm.hpp>
#include <algorithm>
#include "Transform.hpp"
#include "GameObject.hpp"

using namespace glm;

BoxCollider::BoxCollider(bool _rigid, vec3 lb, vec3 rt) : Collider(_rigid) {
	this->lb = lb;
	this->rt = rt;
}

vec3 BoxCollider::getLb() {
	return lb;
}

vec3 BoxCollider::getRt() {
	return rt;
}

vec3 BoxCollider::getTransformedLb() {
	// Apply Transform to box (TODO: should probably handle rotation separately)
	Transform* tr = object->getTransform();
	vec3 lb2 = tr->getMatrix() * vec4(lb, 1.f);
	return lb2;
}

vec3 BoxCollider::getTransformedRt() {
	// Apply Transform to box (TODO: should probably handle rotation separately)
	Transform* tr = object->getTransform();
	vec3 rt2 = tr->getMatrix() * vec4(rt, 1.f);
	return rt2;
}

float BoxCollider::collideRayDistance(vec3 origin, vec3 dir) {
	vec3 lb = getTransformedLb();
	vec3 rt = getTransformedRt();

	// Slab test
	vec3 invdir = 1.0f / dir;

	float t1 = (lb.x - origin.x)*invdir.x;
	float t2 = (rt.x - origin.x)*invdir.x;

	float t3 = (lb.y - origin.y)*invdir.y;
	float t4 = (rt.y - origin.y)*invdir.y;

	float t5 = (lb.z - origin.z)*invdir.z;
	float t6 = (rt.z - origin.z)*invdir.z;

	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	if (tmax > std::max(tmin, 0.f)) {
		return tmin;
	} else {
		return -1;
	}
}

bool BoxCollider::collideBox(BoxCollider* box) {
	vec3 lb = getTransformedLb();
	vec3 rt = getTransformedRt();

	vec3 lb2 = box->getTransformedLb();
	vec3 rt2 = box->getTransformedRt();

	return (lb.x <= rt2.x && rt.x >= lb2.x) &&
		(lb.y <= rt2.y && rt.y >= lb2.y) &&
		(lb.z <= rt2.z && rt.z >= lb2.z);
}
