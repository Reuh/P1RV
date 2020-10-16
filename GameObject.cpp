//
// Created by iagoc on 10/10/2020.
//

#include "GameObject.h"

void GameObject::addComponent(Component* newComponent) {
    componentList.push_back(newComponent);
}
