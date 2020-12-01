//
// Created by iagoc on 11/10/2020.
//

#include "TestScene.h"
#include "CubeRenderer.h"
#include "ModelRenderer.h"
#include "BoxCollider.h"

#include <glm/glm.hpp>
#include <iostream>

using namespace glm;

void TestScene::initialize() {
    CubeRenderer* cr = new CubeRenderer();
    test = new GameObject();
    test->addComponent(cr);
    addObject(test);

    auto model = new GameObject();
    model->addComponent(new ModelRenderer("models/Penguin.obj"));
    model->addComponent(new BoxCollider(vec3(-1,-1,-1), vec3(1,1,1)));
    addObject(model);
}

void TestScene::input() {

}

void TestScene::update() {

}
