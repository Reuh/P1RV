//
// Created by iagoc on 11/10/2020.
//

#ifndef P1RV_RENDERER_H
#define P1RV_RENDERER_H


#include "Component.h"
#include "Shader.hpp"

class Renderer : public Component {
public:
    // TODO Make it static and build an interface to pass the parameters from a reference to the object
    virtual void render(Shader* shader) = 0;
};


#endif //P1RV_RENDERER_H
