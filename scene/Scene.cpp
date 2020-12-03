//
// Created by iagoc on 10/10/2020.
//

#include <iostream>
#include <GL/gl.h>
#include <SFML/Window.hpp>
#include "Scene.hpp"
#include "component/Renderer.hpp"
#include "component/Transform.hpp"
#include "MatrixStack.hpp"
#include "Shader.hpp"
#include "component/Script.hpp"

void Scene::addObject(GameObject *newObject) {
    newObject->scene = this;
    objectList.push_back(newObject);

    for (GameObject* object : objectList) {
        auto* script = object->getComponent<Script>();
        if (script != nullptr) {
            script->start();
        }
    }
}

void Scene::draw(Shader* shader) {
    shader->use();

    for (GameObject* object : objectList) {
        auto* renderer = object->getComponent<Renderer>();
        if (renderer != nullptr) {
            pushMatrix();
            object->getTransform()->apply();
            shader->sendUniform("modelViewProjection", getMVPMatrix());
            renderer->render(shader);
            popMatrix();
        }
    }
}

void Scene::update(float dt) {
    for (GameObject* object : objectList) {
        auto* script = object->getComponent<Script>();
        if (script != nullptr) {
            script->update(dt);
        }
    }
}

void Scene::onWindowEvent(sf::Event event) {
    for (GameObject* object : objectList) {
        auto* script = object->getComponent<Script>();
        if (script != nullptr) {
            script->onWindowEvent(event);
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



