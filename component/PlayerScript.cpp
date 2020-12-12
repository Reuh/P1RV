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

#include <iostream>

void PlayerScript::start() {
	// Initial camera setup
    setLookAt(position, position+eye, up);

    // mouse placed in center at game start
    mouseCenterPosition = sf::Mouse::getPosition();
}

void PlayerScript::update(float dt) {
	// Translation movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        position += right * speed*dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        position -= right * speed*dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        position += front * speed*dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        position -= front * speed*dt;

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
            auto objList = object->scene->getObjectList();
            for(auto iter = objList->begin() ; iter != objList->end(); ++iter) {
                Collider* coll = (*iter)->getComponent<Collider>();
                Script* script = (*iter)->getComponent<Script>();
                if (coll != nullptr && script != nullptr && coll->collideRay(position, eye)) {
                   script->onHit();
                }
            }
        }
    }
}