#ifndef P1RV_MATRIXSTACK_H
#define P1RV_MATRIXSTACK_H

#include "MatrixStack.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

// Transformations matrixes
glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
std::vector<glm::mat4> modelStack = { glm::mat4(1.f) };

void setPerspective(float fov, float aspect, float near, float far) {
	projection = glm::perspective(fov, aspect, near, far);
}
glm::mat4 getProjection() {
	return projection;
}

glm::vec3 eye(0,0,0);
void setLookAt(const glm::vec3 eye_, const glm::vec3 center, const glm::vec3 up) {
	eye = eye_;
	view = glm::lookAt(eye_, center, up);
}
glm::vec3 getEye() {
	return eye;
}
glm::mat4 getView() {
	return view;
}

void pushMatrix() {
	modelStack.push_back(modelStack[modelStack.size()-1]);
}
void applyMatrix(glm::mat4 matrix) {
	modelStack[modelStack.size()-1] = matrix * modelStack[modelStack.size()-1];
}
void popMatrix() {
	modelStack.pop_back();
}
glm::mat4 getModelMatrix() {
	return modelStack[modelStack.size()-1];
}

glm::mat4 getViewProjectionMatrix() {
	return getProjection() * getView();
}

#endif