//
// Created by iagoc on 23/10/2020.
//

#ifndef P1RV_TRANSFORM_H
#define P1RV_TRANSFORM_H


#include <SFML/System.hpp>
#include "Component.h"

class Transform : public Component {
private:
    // TODO Use quaternions
    sf::Vector3f position;
    sf::Vector3f scale;
    sf::Vector3f rotation;
public:
    Transform();
    void apply();
    // Maybe? static void restoreMatrix();
};


#endif //P1RV_TRANSFORM_H
