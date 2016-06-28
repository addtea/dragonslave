#pragma once

#include "geometry.hpp"

namespace dragonslave {


class GeometryGenerator
{
public:
    GeometryGenerator();
    virtual ~GeometryGenerator();

    void generate_plane(float scale, Geometry* geometry);
    void generate_cube(float scale, Geometry* geometry);
    void generate_sphere(float radius, int subdivides, Geometry* geometry);
    void generate_cylinder(float height, float radius, int subdivides, Geometry* geometry);
};

    
}
