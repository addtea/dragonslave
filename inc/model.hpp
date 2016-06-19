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
    Model();
    virtual ~Model();

    const std::vector<Mesh>& get_meshes() const
    { return meshes_; }

    void add_mesh(Geode* geode, Material* material);
    
private:
    std::vector<Mesh> meshes_;
};


}
