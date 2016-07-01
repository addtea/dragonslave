#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "mesh.hpp"
#include "shader.hpp"
#include "sphere_bound.hpp"

namespace dragonslave {


struct Submesh
{
    Geometry* geometry = nullptr;
    Material* material = nullptr;
    Shader* shader = nullptr;
};


class Mesh {
public:
    SphereBound bound;

    Mesh();
    virtual ~Mesh();
    
    std::vector<Submesh>& get_submeshes() { return submeshes_; }

    void create();
    void destroy();

    void add_submesh(Geometry* geometry, Material* material, Shader* shader);
    void update_bound();
    void reset();

private:
    std::vector<Submesh> submeshes_;
};


}
