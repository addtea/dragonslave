#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "linked_list.hpp"

namespace dragonslave {


class Scene;


class SceneSpatial
{
public:
    Scene* scene;
    glm::vec3 position;
    glm::quat orientation;
    
    SceneSpatial();
    virtual ~SceneSpatial();

    virtual void create(Scene* scene);
    virtual void destroy();

    void move(const glm::vec3& offset);
    void rotate(float angle, const glm::vec3& axis);
};


}
