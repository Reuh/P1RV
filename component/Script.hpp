#ifndef P1RV_SCRIPT_H
#define P1RV_SCRIPT_H

#include <SFML/Window.hpp>
#include "Component.hpp"

// Base class to implement some scripted game logic for an object.
class Script : public Component {
public:
	// Called when added to the scene
	virtual void start() {};

	// Called each frame. dt is delta time in seconds.
	virtual void update(float dt) {};

	// Called each window event.
	virtual void onWindowEvent(sf::Event event) {};

	// Called when receive a hit.
	virtual void onHit() {};
};

#endif