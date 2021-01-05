//
// Created by iagoc on 11/10/2020.
//

#include "TestScene.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include "component/ModelRenderer.hpp"
#include "component/BoxCollider.hpp"
#include "component/Transform.hpp"
#include "component/PlayerScript.hpp"
#include "component/RelicScript.hpp"
#include "component/TestEnemyScript.hpp"
#include <component/NavMesh.hpp>
#include <component/NavMeshNavigator.hpp>

using namespace glm;

void TestScene::initialize() {
    auto enemy = new GameObject();
    Transform* transform = enemy->getTransform();
    transform->scale(vec3(0.4,0.4,0.4));
    transform->translate(vec3(0,0,20)); // TODO: better initial placement
    auto enemyModel = new ModelRenderer("models/enemy/MechaGolem.obj");
    enemy->addComponent(enemyModel);
    enemy->addComponent(enemyModel->makeCollider(true));
    enemy->addComponent(new TestEnemyScript());
    addObject(enemy);

    auto level = new GameObject();
    auto levelCollisions = new ModelRenderer("models/level/levelcollisions.obj");
    levelCollisions->object = level; // need to be set manually since this component is never actually added to the object
    level->addComponent(new ModelRenderer("models/level/level.obj"));
    level->addComponent(levelCollisions->makeCollider(true));
    addObject(level);

    auto player = new GameObject();
    player->addComponent(new PlayerScript());
    player->addComponent(new BoxCollider(true, vec3(-.2,0.01,-.2), vec3(.2,.7,.2)));
    player->getTransform()->setPosition(glm::vec3(0,1,30));
    addObject(player);

    auto skybox = new GameObject();
    skybox->getTransform()->scale(glm::vec3(45,45,45));
    auto skyboxModel = new ModelRenderer("models/skybox.obj");
    skyboxModel->setLightning(false);
    skybox->addComponent(skyboxModel);
    addObject(skybox);

    auto relic = new GameObject();
    relic->addComponent(new ModelRenderer("models/Relic.obj"));
    relic->getTransform()->setPosition(glm::vec3(2, 0, 25));
    relic->getTransform()->scale(glm::vec3(0.4, 0.4, 0.4));
    relic->addComponent(new RelicScript(relic, player));
    addObject(relic);
}
