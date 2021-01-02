//
// Created by iagoc on 10/10/2020.
//

#include <iostream>
#include <GL/gl.h>
#include "Scene.h"
#include "Renderer.h"
#include "Transform.h"

void Scene::addObject(GameObject *newObject) {
    objectList.push_back(newObject);
}

void Scene::draw() {
    for (GameObject* object : objectList) {
        auto* renderer = object->getComponent<Renderer>();
        if (renderer != nullptr) {
            glPushMatrix();
            object->getComponent<Transform>()->apply();
            renderer->render();
            glPopMatrix();
        }
    }
}

void Scene::removeObject(GameObject *targetObject) {
    for (int i = 0; i < objectList.size(); i++) {
        if (objectList[i] == targetObject)
            objectList.erase(objectList.begin() + i);
    }
}

std::vector<GameObject *> *Scene::getObjectList() {
    return &objectList;
}



