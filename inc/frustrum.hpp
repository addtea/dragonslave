#pragma once

#include <glm/glm.hpp>
#include "plane.hpp"

namespace dragonslave {


class Frustrum
{
public:
    Plane left;
    Plane right;
    Plane bottom;
    Plane top;
    Plane near;
    Plane far;

    Frustrum();
    virtual ~Frustrum();

    bool contains(const SphereBound& bound) const;
    void apply_projection_matrix(const glm::mat4& projection);
};


}
