//
// Created by iagoc on 10/10/2020.
//

#include <iostream>
#include <GL/gl.h>
#include "Scene.hpp"
#include "Renderer.hpp"
#include "Transform.hpp"
#include "MatrixStack.hpp"
#include "Shader.hpp"

void Scene::addObject(GameObject *newObject) {
    objectList.push_back(newObject);
}

void Scene::draw(Shader* shader) {
    shader->use();

    for (GameObject* object : objectList) {
        auto* renderer = object->getComponent<Renderer>();
        if (renderer != nullptr) {
            auto* transform = object->getComponent<Transform>();
            if (transform != nullptr) {
                pushMatrix();
                object->getComponent<Transform>()->apply();
                shader->sendUniform("modelViewProjection", getMVPMatrix());
                renderer->render(shader);
                popMatrix();
            } else {
                shader->sendUniform("modelViewProjection", getMVPMatrix());
                renderer->render(shader);
            }
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



