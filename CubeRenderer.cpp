//
// Created by iagoc on 11/10/2020.
//

#include <GL/gl.h>
#include "CubeRenderer.h"

void CubeRenderer::render() {
    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-.5f, -.5f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(.5f, -.5f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(.5f, .5f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-.5f, .5f);

    glEnd();
}