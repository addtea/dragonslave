#pragma once

#include <glm/glm.hpp>

namespace dragonslave {


struct SphereBound
{
    bool is_null = false;
    bool is_infinite = true;

    glm::vec3 center;
    float radius = 0.f;
};


}
