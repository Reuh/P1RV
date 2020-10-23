//
// Created by iagoc on 11/10/2020.
//

#include "TestScene.h"
#include "CubeRenderer.h"
#include "ModelRenderer.h"

#include <iostream>

void TestScene::initialize() {
    CubeRenderer* cr = new CubeRenderer();
    test = new GameObject();
    test->addComponent(cr);
    addObject(test);

    auto model = new GameObject();
    std::cout << "init scene" << std::endl;
    model->addComponent(new ModelRenderer("models/Penguin.obj"));
    addObject(model);
}

void TestScene::input() {

}

void TestScene::update() {

}
