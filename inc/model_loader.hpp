#pragma once

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "geode_manager.hpp"
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
                  GeodeManager* geode_manager,
                  MaterialManager* material_manager,
                  ImageManager* image_manager);
    void terminate();

    void load_model_from_file(const std::string& path, Model& model);

private:
    Graphics* graphics_ = nullptr;
    GeodeManager* geode_manager_ = nullptr;
    MaterialManager* material_manager_ = nullptr;
    ImageManager* image_manager_ = nullptr;

    void process_geode_(aiMesh* ai_mesh, Geode& geode);
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
