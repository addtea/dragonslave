#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "mesh.hpp"
#include "shader.hpp"
#include "sphere_bound.hpp"

namespace dragonslave {


class Model {
public:
    SphereBound bound;

    Model();
    virtual ~Model();
    
    std::vector<Mesh>& get_meshes() { return meshes_; }

    void create();
    void destroy();

    void add_mesh(Geometry* geometry, Material* material, Shader* shader);
    void update_bound();
    void reset();

private:
    std::vector<Mesh> meshes_;
};


}
