#include "plane.hpp"

namespace dragonslave {


Plane::Plane() { }


Plane::~Plane() { }


bool Plane::contains(const SphereBound& bound) const
{
    if (bound.is_null) 
        return false;
    if (bound.is_infinite) 
        return true;
    glm::vec3 normal = glm::normalize(glm::vec3{a, b, c});
    float dot = a * a + b * b + c * c;
    glm::vec3 position = -d / dot * glm::vec3{a, b, c};
    glm::vec3 to_center = bound.center - position;
    float offset = glm::dot(to_center, normal);
    return -offset < bound.radius;
}


}
