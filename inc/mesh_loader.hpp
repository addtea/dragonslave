#pragma once

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "graphics_context.hpp"
#include "geometry_manager.hpp"
#include "image_manager.hpp"
#include "material_manager.hpp"
#include "shader_manager.hpp"
#include "mesh.hpp"

namespace dragonslave {


class MeshLoader
{
public:
    MeshLoader();
    virtual ~MeshLoader();

    void load_mesh(
        GeometryManager* geometry_manager,
        MaterialManager* material_manager,
        ImageManager* image_manager,
        ShaderManager* shader_manager,
        const std::string& path,
        Mesh* mesh);

private:
    void process_material_(
        ImageManager* image_manager,
        aiMaterial* ai_material, 
        const std::string& base_dir, 
        Material* material);
    void process_geometry_(
        aiMesh* ai_mesh,
        Geometry* geometry);
    void load_materials_(
        MaterialManager* material_manager,
        ImageManager* image_manager,
        const aiScene* scene, 
        const std::string& base_dir, 
        std::vector<Material*>& materials);
    void load_mesh_(
        GeometryManager* geometry_manager,
        ShaderManager* shader_manager,
        const aiScene* scene, 
        const std::vector<Material*>& materials, 
        Mesh* mesh);
};


}
