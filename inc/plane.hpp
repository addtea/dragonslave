#pragma once

#include <glm/glm.hpp>
#include "sphere_bound.hpp"

namespace dragonslave {


class Plane
{
public:
    float a = 0;
    float b = 0;
    float c = 0;
    float d = 0;

    Plane();
    virtual ~Plane();

    bool contains(const SphereBound& bound) const;
};


}
