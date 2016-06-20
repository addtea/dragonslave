#pragma once

#include <list>
#include <unordered_map>

#include "model.hpp"
#include "model_loader.hpp"

namespace dragonslave {


class ModelManager 
{
public:
    ModelManager();
    ~ModelManager();

    void set_loader(ModelLoader* loader);

    Model& create_model();
    Model& create_named_model(const std::string& name);
    Model& load_model(const std::string& path);
    Model& load_named_model(const std::string& name, const std::string& path);

    Model* get_model(const std::string& name);

private:    
    ModelLoader* loader_;
    std::unordered_map<
            std::string, 
            std::list<Model>::iterator>
        path_cache_;
    std::unordered_map<
            std::string,
            std::list<Model>::iterator>
        model_lookup_;
    std::list<Model> models_;

    void validate_name_(const std::string& name);
    std::list<Model>::iterator create_model_it_();
};


}
