#pragma once

#include <list>
#include <memory>
#include "shader.hpp"

namespace dragonslave {


class ShaderManager
{
public:
    ShaderManager();
    virtual ~ShaderManager();

    void initialize(GraphicsContext* gc);
    void terminate();

    template <typename TShader>
    TShader* create_shader();
    void destroy_shader(Shader* shader);
    
    Shader* get_default_shader() const
    { return default_shader_; }
    void set_default_shader(Shader* shader)
    { default_shader_ = shader; }

private:
    GraphicsContext* gc_ = nullptr;
    Shader* default_shader_ = nullptr;
    std::list<std::unique_ptr<Shader> > shaders_;
};


template <typename TShader>
TShader* ShaderManager::create_shader()
{
    shaders_.push_back(std::make_unique<TShader>());
    TShader* shader = reinterpret_cast<TShader*>(shaders_.back().get());
    shader->create(gc_);
    return shader;
}


}
