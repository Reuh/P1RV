//
// Created by iagoc on 11/10/2020.
//

#ifndef P1RV_CUBERENDERER_H
#define P1RV_CUBERENDERER_H


#include "Renderer.h"
#include "Shader.hpp"

class CubeRenderer : public Renderer {
private:
public:
    void render(Shader* shader) override;

};

#endif //P1RV_CUBERENDERER_H
