#pragma once

#include <list>
#include "geometry_manager.hpp"
#include "material_manager.hpp"
#include "model.hpp"
#include "model_loader.hpp"
#include "shader_manager.hpp"

namespace dragonslave {


class ModelManager
{
public:
    ModelManager();
    virtual ~ModelManager();

    void initialize(
        GeometryManager* geometry_manager,
        MaterialManager* material_manager,
        ImageManager* image_manager,
        ShaderManager* shader_manager,
        ModelLoader* model_loader);
    void terminate();

    Model* create_model();
    Model* load_model(const std::string& path);
    void destroy_model(Model* model);

private:
    GeometryManager* geometry_manager_ = nullptr;
    MaterialManager* material_manager_ = nullptr;
    ImageManager* image_manager_ = nullptr;
    ShaderManager* shader_manager_ = nullptr;
    ModelLoader* model_loader_ = nullptr;
    std::list<Model> models_;
};


}
