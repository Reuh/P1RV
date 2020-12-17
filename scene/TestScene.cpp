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

    auto maze = new GameObject();
    maze->getTransform()->scale(vec3(1, 1, 1));
    // TODO : Add a way to change model color from ModelRenderer properties
    maze->addComponent(new ModelRenderer("models/labyrinth.obj"));
    addObject(maze);

    auto player = new GameObject();
    player->addComponent(new PlayerScript());
    player->addComponent(new BoxCollider(vec3(-.2,0,-.2), vec3(.2,.7,.2)));
    player->getTransform()->setPosition(glm::vec3(-2,0,0));
    addObject(player);
}
