//
// Created by iagoc on 10/10/2020.
//

#include "GameObject.h"

unsigned GameObject::idCounter = 0;

void GameObject::addComponent(Component* newComponent) {
	newComponent->object = this;
    componentList.push_back(newComponent);
}

unsigned GameObject::getId() const {
    return this->id;
}
