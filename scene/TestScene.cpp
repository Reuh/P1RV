//
// Created by iagoc on 11/10/2020.
//

#include "TestScene.hpp"
#include "component/CubeRenderer.hpp"
#include "component/ModelRenderer.hpp"
#include "component/BoxCollider.hpp"
#include "component/Transform.hpp"
#include "component/PlayerScript.hpp"
#include "component/TestEnemyScript.hpp"

#include <glm/glm.hpp>
#include <iostream>

using namespace glm;

void TestScene::initialize() {
    auto model = new GameObject();
    Transform* transform = model->getTransform();
    transform->scale(vec3(0.5,0.5,0.5));
    model->addComponent(new ModelRenderer("models/cube/cube.gltf"));
    model->addComponent(new BoxCollider(vec3(-1,-1,-1), vec3(1,1,1))); // TODO: automatically calculate from model data
    model->addComponent(new TestEnemyScript());
    addObject(model);

    auto player = new GameObject();
    player->addComponent(new PlayerScript());
    addObject(player);
}
