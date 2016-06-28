#include "model_manager.hpp"

namespace dragonslave {


ModelManager::ModelManager() { }


ModelManager::~ModelManager() { }


void ModelManager::initialize(
        GeometryManager* geometry_manager,
        MaterialManager* material_manager,
        ImageManager* image_manager,
        ShaderManager* shader_manager,
        ModelLoader* model_loader)
{
    geometry_manager_ = geometry_manager;
    material_manager_ = material_manager;
    image_manager_ = image_manager;
    shader_manager_ = shader_manager;
    model_loader_ = model_loader;
}


void ModelManager::terminate()
{
    geometry_manager_ = nullptr;
    material_manager_ = nullptr;
    image_manager_ = nullptr;
    model_loader_ = nullptr;
}


Model* ModelManager::create_model()
{
    models_.emplace_back();
    Model* model = &models_.back();
    model->create();
    return model;
}


Model* ModelManager::load_model(const std::string& path)
{
    Model* model = create_model();
    model_loader_->load_model(
        geometry_manager_,
        material_manager_,
        image_manager_,
        shader_manager_,
        path,
        model);
    return model;
}


void ModelManager::destroy_model(Model* model)
{
    model->destroy();
    std::remove_if(
        models_.begin(),
        models_.end(),
        [=](Model& stored_model){ 
            return &stored_model == model;
        });
}


}
