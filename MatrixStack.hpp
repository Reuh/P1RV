#ifndef P1RV_MATRIXSTACK_H
#define P1RV_MATRIXSTACK_H

#include <glm/glm.hpp>

// Projection matrix
void setPerspective(float fov, float aspect, float near, float far);
glm::mat4 getProjection();

// View matrix
void setLookAt(const glm::vec3 eye, const glm::vec3 center, const glm::vec3 up);
glm::vec3 getEye();
glm::mat4 getView();

glm::mat4 getViewProjectionMatrix();

// Model matrix
void pushMatrix();
void applyMatrix(glm::mat4 matrix);
void popMatrix();
glm::mat4 getModelMatrix();

#endif