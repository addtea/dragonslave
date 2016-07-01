#include "mesh_manager.hpp"

namespace dragonslave {


MeshManager::MeshManager() { }


MeshManager::~MeshManager() { }


void MeshManager::initialize(
        GeometryManager* geometry_manager,
        MaterialManager* material_manager,
        ImageManager* image_manager,
        ShaderManager* shader_manager,
        MeshLoader* mesh_loader)
{
    geometry_manager_ = geometry_manager;
    material_manager_ = material_manager;
    image_manager_ = image_manager;
    shader_manager_ = shader_manager;
    mesh_loader_ = mesh_loader;
}


void MeshManager::terminate()
{
    geometry_manager_ = nullptr;
    material_manager_ = nullptr;
    image_manager_ = nullptr;
    mesh_loader_ = nullptr;
}


Mesh* MeshManager::create_mesh()
{
    meshs_.emplace_back();
    Mesh* mesh = &meshs_.back();
    mesh->create();
    return mesh;
}


Mesh* MeshManager::load_mesh(const std::string& path)
{
    Mesh* mesh = create_mesh();
    mesh_loader_->load_mesh(
        geometry_manager_,
        material_manager_,
        image_manager_,
        shader_manager_,
        path,
        mesh);
    return mesh;
}


void MeshManager::destroy_mesh(Mesh* mesh)
{
    mesh->destroy();
    std::remove_if(
        meshs_.begin(),
        meshs_.end(),
        [=](Mesh& stored_mesh){ 
            return &stored_mesh == mesh;
        });
}


}
