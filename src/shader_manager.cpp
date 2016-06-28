#include "shader_manager.hpp" 

namespace dragonslave {


ShaderManager::ShaderManager() { }


ShaderManager::~ShaderManager() { }


void ShaderManager::initialize(GraphicsContext* gc)
{
    gc_ = gc;
}


void ShaderManager::terminate()
{
    for (auto& shader : shaders_) {
        shader->destroy();
    }
    shaders_.clear();
    gc_ = nullptr;
    default_shader_ = nullptr;
}


void ShaderManager::destroy_shader(Shader* shader)
{
    shader->destroy();
    std::remove_if(
        shaders_.begin(),
        shaders_.end(),
        [=](auto& stored_shader){ 
            return stored_shader.get() == shader;
        });
}


}
