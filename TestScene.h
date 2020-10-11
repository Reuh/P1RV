//
// Created by iagoc on 11/10/2020.
//

#ifndef P1RV_TESTSCENE_H
#define P1RV_TESTSCENE_H


#include "Scene.h"

class TestScene : public Scene {
private:
    GameObject* test;
public:
    void initialize() override;
    void input() override;
    void update() override;
};


#endif //P1RV_TESTSCENE_H