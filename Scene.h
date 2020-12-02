//
// Created by iagoc on 10/10/2020.
//

#ifndef P1RV_SCENE_H
#define P1RV_SCENE_H


#include <vector>
#include "GameObject.h"
#include "Shader.hpp"

// At the end this class can just load a Scene information from a file specified in the constructor
class Scene {
private:
    std::vector<GameObject*> objectList;
public:
    void addObject(GameObject* newObject);
    // GameObject* find(); // TODO after adding identifier
    // GameObject* findByTag
    void removeObject(GameObject* targetObject);
    std::vector<GameObject*>* getObjectList();
    virtual void initialize() = 0;
    virtual void input() = 0;
    virtual void update() = 0;
    // TODO To decouple the scope of rendering from this class, it would be better a function to return the list of objects to be rendered
    // It's also nice to use a fixed pointer that can be accessed only once
    void draw(Shader* shader);
};


#endif //P1RV_SCENE_H
