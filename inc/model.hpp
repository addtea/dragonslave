#pragma once
#include <vector>
#include "geometry.hpp"
#include "material.hpp"

namespace dragonslave {


struct Mesh
{
    Geometry* geometry;
    Material* material;

    Mesh(Geometry* geometry, Material* material)
      : geometry (geometry)
      , material (material)
    { }
};

class Model {
public:
    std::vector<Mesh> meshes;

    Model();
    virtual ~Model();
};


}
