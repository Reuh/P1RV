//
// Created by iagoc on 11/10/2020.
//

#ifndef P1RV_TESTSCENE_H
#define P1RV_TESTSCENE_H


#include "Scene.hpp"

class TestScene : public Scene {
private:
    GameObject* test;
public:
    void initialize() override;
};


#endif //P1RV_TESTSCENE_H
