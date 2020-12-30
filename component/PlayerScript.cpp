#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <SFML/Window.hpp>

#include "MatrixStack.hpp"
#include "PlayerScript.hpp"
#include "Collider.hpp"
#include "Script.hpp"
#include "GameObject.hpp"
#include "scene/Scene.hpp"
#include "Game.hpp"
#include "EventHandler.hpp"
#include "BoxCollider.hpp"

#include <iostream>

#ifdef _WIN32
#include <winuser.h>
#endif

void PlayerScript::start() {
	// Initial camera setup
    glm::vec3 position = object->getTransform()->getPosition();
    setLookAt(position, position+eye, up);

    // mouse placed in center at game start
    mouseCenterPosition = sf::Mouse::getPosition();

    // Register actions, maybe add default bindings so that it doesn't need initialization
    EventHandler::addAction("left", [this](auto && PH1) { leftKey(std::forward<decltype(PH1)>(PH1)); });
    EventHandler::addAction("right", [this](auto && PH1) { rightKey(std::forward<decltype(PH1)>(PH1)); });
    EventHandler::addAction("up", [this](auto && PH1) { upKey(std::forward<decltype(PH1)>(PH1)); });
    EventHandler::addAction("down", [this](auto && PH1) { downKey(std::forward<decltype(PH1)>(PH1)); });

    // Register bindings
    long long x = 0;
    #ifdef _WIN32
        // Check keyboard type
        x = (long long) GetKeyboardLayout(0) & 0x0000FFFF;
    #endif
    if (x == 1046) { // QWERTY
        EventHandler::setBinding(sf::Keyboard::W, "up");
        EventHandler::setBinding(sf::Keyboard::S, "down");
        EventHandler::setBinding(sf::Keyboard::A, "left");
        EventHandler::setBinding(sf::Keyboard::D, "right");
    } else { // AZERTY or linux
        EventHandler::setBinding(sf::Keyboard::Z, "up");
        EventHandler::setBinding(sf::Keyboard::S, "down");
        EventHandler::setBinding(sf::Keyboard::Q, "left");
        EventHandler::setBinding(sf::Keyboard::D, "right");
    }
}

void PlayerScript::update(float dt) {
	// Translation movement
    glm::vec3 position = object->getTransform()->getPosition();
    glm::vec3 oldPosition = position;
    if (sRight)
        position += right * speed*dt;
    if (sLeft)
        position -= right * speed*dt;
    if (sUp)
        position += front * speed*dt;
    if (sDown)
        position -= front * speed*dt;
    object->getTransform()->setPosition(position);

    // Cancel translation if collided (TODO: proper collision resolution)
    auto boxcollider = object->getComponent<BoxCollider>();
    if (boxcollider != nullptr) {
        auto objList = object->scene->getObjectList();
        for(auto & iter : *objList) {
            if (iter != object) {
                auto coll = iter->getComponent<Collider>();
                if (coll != nullptr && coll->collideBox(boxcollider)) {
                   object->getTransform()->setPosition(oldPosition);
                   position = oldPosition;
                }
            }
        }
    }

    // Rotation movement
    sf::Vector2i newMousePosition = sf::Mouse::getPosition();
    sf::Vector2i diff = newMousePosition - mouseCenterPosition;
    Game *instance = Game::getInstance();
    if (instance->getWindow()->hasFocus())
        sf::Mouse::setPosition(mouseCenterPosition); // re-center mouse
    
    angleY += -diff.x * rotateSpeed * dt;
    angleX += -diff.y * rotateSpeed * dt;
    angleX = std::min(std::max(angleX, -3.14f/2), 3.14f/2); // prevent infinite rotation on x axis

    // Update position vectors
    front = glm::rotate(glm::vec3(1,0,0), angleY, up);
    right = glm::cross(front, up);
    eye = glm::rotate(front, angleX, right);

    // Update camera
    setLookAt(position, position+eye, up);
}

void PlayerScript::onWindowEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		// Fire
        if (event.mouseButton.button == sf::Mouse::Left) {
            glm::vec3 position = object->getTransform()->getPosition();
            auto objList = object->scene->getObjectList();
            for(auto & iter : *objList) {
                if (iter != object) {
                    auto coll = iter->getComponent<Collider>();
                    auto script = iter->getComponent<Script>();
                    if (coll != nullptr && script != nullptr && coll->collideRay(position, eye)) {
                       script->onHit();
                    }
                }
            }
        }
    }
}

void PlayerScript::leftKey(sf::Event::EventType eventType) {
    if (eventType == sf::Event::KeyPressed) sLeft = true;
    else if (eventType == sf::Event::KeyReleased) sLeft = false;
}

void PlayerScript::rightKey(sf::Event::EventType eventType) {
    if (eventType == sf::Event::KeyPressed) sRight = true;
    else if (eventType == sf::Event::KeyReleased) sRight = false;
}

void PlayerScript::upKey(sf::Event::EventType eventType) {
    if (eventType == sf::Event::KeyPressed) sUp = true;
    else if (eventType == sf::Event::KeyReleased) sUp = false;
}

void PlayerScript::downKey(sf::Event::EventType eventType) {
    if (eventType == sf::Event::KeyPressed) sDown = true;
    else if (eventType == sf::Event::KeyReleased) sDown = false;
}
