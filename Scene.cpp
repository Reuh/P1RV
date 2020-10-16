//
// Created by iagoc on 10/10/2020.
//

#include <iostream>
#include "Scene.h"
#include "Renderer.h"

void Scene::addObject(GameObject *newObject) {
    objectList.push_back(newObject);
}

void Scene::draw() {
    for (GameObject* object : objectList) {
        auto* renderer = object->getComponent<Renderer>();
        if (renderer != nullptr)
            renderer->render();
    }
}
// TODO : Test for objects with a Renderer and without one

void Scene::removeObject(GameObject *targetObject) {
    for (int i = 0; i < objectList.size(); i++) {
        if (objectList[i] == targetObject)
            objectList.erase(objectList.begin() + i);
    }
}

std::vector<GameObject *> *Scene::getObjectList() {
    return &objectList;
}



