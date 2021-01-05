//
// Created by iagoc on 11/10/2020.
//

#ifndef P1RV_COMPONENT_H
#define P1RV_COMPONENT_H

class GameObject; // forward declaration (cycle)

// Base class to give some functionnaly to an object
class Component {
public:
	GameObject* object{};
    virtual ~Component() = default;
};


#endif //P1RV_COMPONENT_H
