//
// Created by iagoc on 10/10/2020.
//

#include <iostream>
#include <SFML/OpenGL.hpp>
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
    shader->sendUniform("viewProjection", getViewProjectionMatrix());
    shader->sendUniform("eyePos", getEye());

    shader->sendUniform("light.direction", glm::vec3(2,-3,1));
    shader->sendUniform("light.ambient", glm::vec3(0.4,0.4,0.4));
    shader->sendUniform("light.diffuse", glm::vec3(1,1,1));
    shader->sendUniform("light.specular", glm::vec3(1,1,1));

    for (GameObject* object : objectList) {
        auto* renderer = object->getComponent<Renderer>();
        if (renderer != nullptr) {
            pushMatrix();
            object->getTransform()->apply();
            shader->sendUniform("model", getModelMatrix());
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



