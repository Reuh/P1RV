#ifndef P1RV_MATRIXSTACK_H
#define P1RV_MATRIXSTACK_H

#include "MatrixStack.hpp"
#include <glm/glm.hpp>
#include <vector>

// Transformations matrixes
glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
std::vector<glm::mat4> modelStack = { glm::mat4(1.f) };

void setProjection(glm::mat4 matrix) {
	projection = matrix;
}
glm::mat4 getProjection() {
	return projection;
}
void setView(glm::mat4 matrix) {
	view = matrix;
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

glm::mat4 getMVPMatrix() {
	return getProjection() * getView() * getModelMatrix();
}

#endif