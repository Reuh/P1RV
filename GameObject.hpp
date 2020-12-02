//
// Created by iagoc on 10/10/2020.
//

#ifndef P1RV_GAMEOBJECT_H
#define P1RV_GAMEOBJECT_H


#include <vector>
#include "Component.hpp"
#include "Transform.hpp"

class GameObject {
private:
    static unsigned idCounter;
    unsigned id;
    std::vector<Component*> componentList;
    Transform transform;
    // TODO Add Renderer Components as separate references (Optimization)
public:
    GameObject() {
        this->id = idCounter++;
    }
    void addComponent(Component* newComponent);
    unsigned getId() const;

    template<typename T> T* getComponent() {
        for (Component* component : componentList) {
            if (dynamic_cast<T *>(component) != NULL)
                return dynamic_cast<T *>(component);
        }
        return nullptr;
    }

    Transform * getComponent() {
        return &(this->transform);
    }

    template<typename T> std::vector<T*> getComponents() {
        std::vector<Component*> components;
        for (Component* component : componentList) {
            if (dynamic_cast<T *>(component) != NULL)
                components.push_back(component);
        }
        return components;
    }
};


#endif //P1RV_GAMEOBJECT_H
