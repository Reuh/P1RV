//
// Created by iagoc on 23/10/2020.
//

#include <SFML/OpenGL.hpp>
#include "Transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "MatrixStack.hpp"

glm::mat4 Transform::getMatrix() {
	glm::mat4 matrix = glm::translate(glm::mat4(1.0f), vPosition);
	matrix = glm::rotate(matrix, vRotation.x, glm::vec3(1,0,0));
	matrix = glm::rotate(matrix, vRotation.y, glm::vec3(0,1,0));
	matrix = glm::rotate(matrix, vRotation.z, glm::vec3(0,0,1));
    matrix = glm::scale(matrix, vScale);
    return matrix;
}

void Transform::apply() {
	applyMatrix(getMatrix());
}

Transform::Transform() {
    this->vPosition = glm::vec3(0,0,0);
    this->vRotation = glm::vec3(0,0,0);
    this->vScale = glm::vec3(1,1,1);
    this->front = glm::vec3(1,0,0);
}

glm::vec3 Transform::getPosition() {
	return vPosition;
}
void Transform::setPosition(glm::vec3 pos) {
	vPosition = pos;
}

void Transform::translate(glm::vec3 vec) {
	vPosition += vec;
}

void Transform::scale(glm::vec3 vec) {
	vScale *= vec;
}

void Transform::setFront(glm::vec3 vec) {
    this->front = vec;
}

glm::vec3 Transform::getFront() {
    return this->front;
}