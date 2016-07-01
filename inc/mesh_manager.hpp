#pragma once

#include <list>
#include "geometry_manager.hpp"
#include "material_manager.hpp"
#include "mesh.hpp"
#include "mesh_loader.hpp"
#include "shader_manager.hpp"

namespace dragonslave {


class MeshManager
{
public:
    MeshManager();
    virtual ~MeshManager();

    void initialize(
        GeometryManager* geometry_manager,
        MaterialManager* material_manager,
        ImageManager* image_manager,
        ShaderManager* shader_manager,
        MeshLoader* mesh_loader);
    void terminate();

    Mesh* create_mesh();
    Mesh* load_mesh(const std::string& path);
    void destroy_mesh(Mesh* mesh);

private:
    GeometryManager* geometry_manager_ = nullptr;
    MaterialManager* material_manager_ = nullptr;
    ImageManager* image_manager_ = nullptr;
    ShaderManager* shader_manager_ = nullptr;
    MeshLoader* mesh_loader_ = nullptr;
    std::list<Mesh> meshs_;
};


}
