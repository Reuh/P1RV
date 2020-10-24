//
// Created by iagoc on 23/10/2020.
//

#include <GL/gl.h>
#include "Transform.h"

void Transform::apply() {
    glTranslatef(this->position.x, this->position.y, this->position.z);
    glRotatef(this->rotation.x, 1, 0, 0);
    glRotatef(this->rotation.y, 0, 1, 0);
    glRotatef(this->rotation.z, 0, 0, 1);
    glScalef(this->scale.x, this->scale.y, this->scale.z);
}

Transform::Transform() {
    this->position = sf::Vector3f();
    this->rotation = sf::Vector3f();
    this->scale = sf::Vector3f();
}
