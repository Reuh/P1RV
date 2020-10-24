//
// Created by iagoc on 11/10/2020.
//

#include "TestScene.h"
#include "CubeRenderer.h"

void TestScene::initialize() {
    auto* cr = new CubeRenderer();
    test = new GameObject();
    test->addComponent(cr);
    addObject(test);
}

void TestScene::input() {

}

void TestScene::update() {

}
