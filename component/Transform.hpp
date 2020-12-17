//
// Created by iagoc on 23/10/2020.
//

#ifndef P1RV_TRANSFORM_H
#define P1RV_TRANSFORM_H

#include <SFML/System.hpp>
#include "Component.hpp"
#include <glm/glm.hpp>

class Transform : public Component {
private:
    // TODO Use quaternions
    glm::vec3 vPosition;
    glm::vec3 vScale;
    glm::vec3 vRotation;
public:
    Transform();

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);

    void translate(glm::vec3 vec);
    void scale(glm::vec3 vec);

    glm::mat4 getMatrix();
    void apply();
    // Maybe? static void restoreMatrix();
};


#endif //P1RV_TRANSFORM_H
