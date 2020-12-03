//
// Created by iagoc on 11/10/2020.
//

#include "TestScene.hpp"
#include "CubeRenderer.hpp"
#include "ModelRenderer.hpp"
#include "BoxCollider.hpp"
#include "Transform.hpp"
#include "Player.hpp"
#include "TestEnemyIA.hpp"

#include <glm/glm.hpp>
#include <iostream>

using namespace glm;

void TestScene::initialize() {
    auto model = new GameObject();
    Transform* transform = model->getTransform();
    transform->scale(vec3(0.5,0.5,0.5));
    model->addComponent(new ModelRenderer("models/cube/cube.gltf"));
    model->addComponent(new BoxCollider(vec3(-1,-1,-1), vec3(1,1,1))); // TODO: automatically calculate from model data
    model->addComponent(new TestEnemyIA());
    addObject(model);

    auto player = new GameObject();
    player->addComponent(new Player());
    addObject(player);
}
