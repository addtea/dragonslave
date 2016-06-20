#pragma once
#include <vector>
#include "geode.hpp"
#include "material.hpp"

namespace dragonslave {


struct Mesh
{
    Geode* geode;
    Material* material;

    Mesh(Geode* geode, Material* material)
      : geode (geode)
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
