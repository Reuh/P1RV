#ifndef P1RV_PLAYERCONTROLLER_H
#define P1RV_PLAYERCONTROLLER_H

#include "Script.hpp"

#include <glm/glm.hpp>

class Player : public Script {
private:
	// Player position. TODO: merge with Transform
	const glm::vec3 up = glm::vec3(0,1,0); // up axis, fixed
	glm::vec3 position = glm::vec3(-2,0,0); // player position
	glm::vec3 front = glm::vec3(1,0,0); // player front axis (parrallel to the horizontal) = rotate((1,0,0), angleX, up)
	glm::vec3 right = glm::vec3(0,0,1); // player right axis (parrallel to the horizontal) = cross(front, up)
	glm::vec3 eye = glm::vec3(1,0,0); // player eye direction = rotate(front, angleX, right)
	const float speed = 1; // movement speed per second
	float angleX = 0; // eye rotation
	float angleY = 0;
	const float rotateSpeed = 0.1; // rotation speed per second

	// Mouse center coordinates
	sf::Vector2i mouseCenterPosition;
public:
	void start() override;
	void update(float dt) override;
	void onWindowEvent(sf::Event event) override;
};

#endif