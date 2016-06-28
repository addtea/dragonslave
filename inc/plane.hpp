#pragma once

#include <glm/glm.hpp>
#include "sphere_bound.hpp"

namespace dragonslave {


class Plane
{
public:

    float a;
    float b;
    float c;
    float d;

    Plane();
    virtual ~Plane();

    bool contains(const SphereBound& bound) const;
};


}
