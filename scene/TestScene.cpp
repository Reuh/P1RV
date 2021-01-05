//
// Created by iagoc on 11/10/2020.
//

#include "TestScene.hpp"
#include "component/ModelRenderer.hpp"
#include "component/BoxCollider.hpp"
#include "component/Transform.hpp"
#include "component/PlayerScript.hpp"
#include "component/RelicScript.hpp"
#include "component/TestEnemyScript.hpp"

#include <glm/glm.hpp>
#include <iostream>
#include <component/NavMesh.hpp>
#include <component/NavMeshNavigator.hpp>

using namespace glm;

void TestScene::initialize() {
    auto navmesh = new NavMesh("models/navmesh.obj");
    glm::vec3 begin = vec3(-0.5, 0, -0.5);
    glm::vec3 end = vec3(-0.5, 0, -4);
    auto result = navmesh->findPath(begin, end);

    cout << result.size() << " points." << endl;

    auto * point = new GameObject();
    point->addComponent(new ModelRenderer("models/cube/cube.gltf"));
    point->getTransform()->scale(vec3(0.125, 0.125, 0.125));
    point->getTransform()->setPosition(result[0].second);
    point->addComponent(new NavMeshNavigator(navmesh));
    point->addComponent(new TestEnemyScript());
    addObject(point);

    auto map = new GameObject();
    map->getTransform()->setPosition(vec3(0, -1, 0));
    map->addComponent(new ModelRenderer("models/navmesh.obj"));
    addObject(map);

    /*
    auto model = new GameObject();
    Transform* transform = model->getTransform();
    transform->scale(vec3(0.5,0.5,0.5));
    model->addComponent(new ModelRenderer("models/cube/cube.gltf"));
    model->addComponent(new BoxCollider(true, vec3(-1,-1,-1), vec3(1,1,1))); // TODO: automatically calculate from model data
    model->addComponent(new TestEnemyScript());
    addObject(model);
     */

    /*
    auto maze = new GameObject();
    maze->getTransform()->scale(vec3(1, 1, 1));
    // TODO : Add a way to change model color from ModelRenderer properties
    // maze->addComponent(new ModelRenderer("models/labyrinth.obj"));
    maze->addComponent(new ModelRenderer("models/level/level.obj"));
    addObject(maze);
    */

    auto player = new GameObject();
    player->addComponent(new PlayerScript());
    player->addComponent(new BoxCollider(true, vec3(-.2,0,-.2), vec3(.2,.7,.2)));
    player->getTransform()->setPosition(glm::vec3(-0.5, 0, -0.5));
    // player->getTransform()->setPosition(glm::vec3(0,1,30));
    addObject(player);

    auto skybox = new GameObject();
    skybox->getTransform()->scale(glm::vec3(50,50,50));
    auto skyboxModel = new ModelRenderer("models/skybox.obj");
    skyboxModel->setLightning(false);
    skybox->addComponent(skyboxModel);
    addObject(skybox);

    /*
    auto relic = new GameObject();
    relic->addComponent(new ModelRenderer("models/Relic.obj"));
    relic->getTransform()->setPosition(glm::vec3(2, -0.5, 0));
    relic->getTransform()->scale(glm::vec3(0.25, 0.25, 0.25));
    relic->addComponent(new RelicScript(relic, player));
    addObject(relic);
    */
}
