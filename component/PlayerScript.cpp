#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "MatrixStack.hpp"
#include "PlayerScript.hpp"
#include "Collider.hpp"
#include "Script.hpp"
#include "GameObject.hpp"
#include "scene/Scene.hpp"
#include "Game.hpp"
#include "EventHandler.hpp"
#include "BoxCollider.hpp"

#ifdef _WIN32
#include <winuser.h>
#endif

// some global sound buffers and sounds for sfx
sf::SoundBuffer shotBuffer;
sf::Sound shotSound;

void PlayerScript::start() {
	// Initial camera setup
    glm::vec3 position = object->getTransform()->getPosition();
    setLookAt(position, position+eye, up);

    // mouse placed in center at game start
    // mouseCenterPosition = sf::Mouse::getPosition();
    auto wPos = Game::getInstance()->getWindow()->getPosition();
    auto wSize = Game::getInstance()->getWindow()->getSize();
    mouseCenterPosition = sf::Vector2i(wPos.x + wSize.x / 2, wPos.y + wSize.y / 2);

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

    // Load sounds
    if (!shotBuffer.loadFromFile("sounds/cjdeets-shot.wav"))
        std::cout << "ERROR: can't load sound sounds/cjdeets-shot.wav" << std::endl;
    shotSound.setBuffer(shotBuffer);
    shotSound.setRelativeToListener(true);
    shotSound.setVolume(50.0f);
}

void PlayerScript::update(float dt) {
	// Translation movement
    glm::vec3 position = object->getTransform()->getPosition();
    glm::vec3 oldPosition = position;
    // TODO : Fix speed attribution so it's constant in all directions
    if (sRight)
        position += right * speed*dt;
    if (sLeft)
        position -= right * speed*dt;
    if (sUp)
        position += front * speed*dt;
    if (sDown)
        position -= front * speed*dt;
    object->getTransform()->setPosition(position);

    // Cancel translation if collided
    // TODO: physics based collision
    auto boxcollider = object->getComponent<BoxCollider>();
    if (boxcollider != nullptr) {
        auto objList = object->scene->getObjectList();
        for(auto & iter : *objList) {
            if (iter != object) {
                // TODO: Expand to multiple colliders
                auto coll = iter->getComponent<Collider>();
                if (coll != nullptr && coll->isRigid() && coll->collideBox(boxcollider)) {
                   object->getTransform()->setPosition(oldPosition);
                   position = oldPosition;
                   break;
                }
            }
        }
    }

    // Rotation movement
    sf::Vector2i newMousePosition = sf::Mouse::getPosition();
    sf::Vector2i diff = newMousePosition - mouseCenterPosition;
    Game *instance = Game::getInstance();
    if (instance->getWindow()->hasFocus()) {
        sf::Mouse::setPosition(mouseCenterPosition); // re-center mouse

        angleY += -diff.x * rotateSpeed * dt;
        angleX += -diff.y * rotateSpeed * dt;
        angleX = std::min(std::max(angleX, -3.14f/2), 3.14f/2); // prevent infinite rotation on x axis

        // Update position vectors
        front = glm::rotate(glm::vec3(1,0,0), angleY, up);
        right = glm::cross(front, up);
        eye = glm::rotate(front, angleX, right);

        this->object->getTransform()->setFront(front);

        // Update camera
        setLookAt(position, position+eye, up);
    }

    // update audio listener position
    sf::Listener::setPosition(position.x, position.y, position.z);
    sf::Listener::setDirection(eye.x, eye.y, eye.z);
    sf::Listener::setUpVector(up.x, up.y, up.z);
}

void PlayerScript::onWindowEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		// Fire
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Play shot SFX
            shotSound.play();

            // We search for the object with a script (hitScript) hit by the ray starting from the player at the shortest distance (minDist).
            float minDist = -1; // -1 if no object intersect with ray
            Script* hitScript = nullptr; // nullptr if no object with a script intersect
            // search objects intersecting with ray
            glm::vec3 position = object->getTransform()->getPosition();
            auto objList = object->scene->getObjectList();
            for(auto & iter : *objList) {
                if (iter != object) {
                    auto coll = iter->getComponent<Collider>();
                    if (coll != nullptr) {
                        float dist = coll->collideRayDistance(position, eye);
                        if (dist >= 0) {
                            if ((minDist == -1) || (dist < minDist)) {
                                auto script = iter->getComponent<Script>();
                                if (script != nullptr) {
                                    minDist = dist;
                                    hitScript = script;
                                // Handle occlusion by rigid objects without script
                                } else if (coll->isRigid()) {
                                    minDist = dist;
                                    hitScript = nullptr;
                                }
                            }
                        }
                    }
                }
            }
            // Act on first hit object, if any
            if (hitScript != nullptr)
                hitScript->onHit();
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
