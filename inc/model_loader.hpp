#pragma once

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "geometry_manager.hpp"
#include "graphics.hpp"
#include "image_manager.hpp"
#include "material_manager.hpp"
#include "model.hpp"

namespace dragonslave {


class ModelLoader
{
public:
    ModelLoader();
    virtual ~ModelLoader();

    void initiate(Graphics* graphics,
                  GeometryManager* geometry_manager,
                  MaterialManager* material_manager,
                  ImageManager* image_manager);
    void terminate();

    void load_model_from_file(const std::string& path, Model& model);

private:
    Graphics* graphics_ = nullptr;
    GeometryManager* geometry_manager_ = nullptr;
    MaterialManager* material_manager_ = nullptr;
    ImageManager* image_manager_ = nullptr;

    void process_geometry_(aiMesh* ai_mesh, Geometry& geometry);
    void process_material_(
        aiMaterial* ai_material, 
        const std::string& base_dir, 
        Material& material);
    void load_materials_(
        const aiScene* scene, 
        const std::string& base_dir, 
        std::vector<Material*>& materials);
    void load_meshes_(
        const aiScene* scene, 
        const std::vector<Material*>& materials, 
        Model& model);
};


}
