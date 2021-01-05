//
// Created by iagoc on 11/10/2020.
//

#ifndef P1RV_RENDERER_H
#define P1RV_RENDERER_H


#include "Component.hpp"
#include "Shader.hpp"

// Base class for renderer components.
class Renderer : public Component {
private:
	bool lightning = true;
public:
	// Enable/disable lightning for this renderer.
	void setLightning(bool l) { lightning = l; };
	bool getLightning() { return lightning; };

    // TODO Make it static and build an interface to pass the parameters from a reference to the object
    virtual void render(Shader* shader) = 0;
};


#endif //P1RV_RENDERER_H
