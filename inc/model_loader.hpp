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
#include "model.hpp"

namespace dragonslave {


class ModelLoader
{
public:
    ModelLoader();
    virtual ~ModelLoader();

    void load_model(
        GeometryManager* geometry_manager,
        MaterialManager* material_manager,
        ImageManager* image_manager,
        ShaderManager* shader_manager,
        const std::string& path,
        Model* model);

private:
    void process_geometry_(
        aiMesh* ai_mesh,
        Geometry* geometry);
    void process_material_(
        ImageManager* image_manager,
        aiMaterial* ai_material, 
        const std::string& base_dir, 
        Material* material);
    void load_materials_(
        MaterialManager* material_manager,
        ImageManager* image_manager,
        const aiScene* scene, 
        const std::string& base_dir, 
        std::vector<Material*>& materials);
    void load_meshes_(
        GeometryManager* geometry_manager,
        ShaderManager* shader_manager,
        const aiScene* scene, 
        const std::vector<Material*>& materials, 
        Model* model);
};


}
