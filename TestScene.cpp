//
// Created by iagoc on 11/10/2020.
//

#include "TestScene.h"
#include "CubeRenderer.h"
#include "ModelRenderer.h"
#include "BoxCollider.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <iostream>

using namespace glm;

void TestScene::initialize() {
    auto* cr = new CubeRenderer();
    test = new GameObject();
    test->addComponent(cr);
    addObject(test);

    auto model = new GameObject();
    model->addComponent(new ModelRenderer("models/cube/cube.gltf"));
    model->addComponent(new BoxCollider(vec3(-1,-1,-1), vec3(1,1,1)));
    Transform* transform = new Transform();
    transform->scale(vec3(0.5,0.5,0.5));
    model->addComponent(transform);
    addObject(model);
}

void TestScene::input() {

}

void TestScene::update() {

}
