#ifndef P1RV_MATRIXSTACK_H
#define P1RV_MATRIXSTACK_H

#include <glm/glm.hpp>

void setProjection(glm::mat4 matrix);
glm::mat4 getProjection();
void setView(glm::mat4 matrix);
glm::mat4 getView();

void pushMatrix();
void applyMatrix(glm::mat4 matrix);
void popMatrix();
glm::mat4 getModelMatrix();

glm::mat4 getMVPMatrix();

#endif