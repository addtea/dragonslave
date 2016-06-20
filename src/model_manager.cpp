#include <algorithm>

#include "model_manager.hpp"

namespace dragonslave {


ModelManager::ModelManager() { }


ModelManager::~ModelManager() { }


void ModelManager::set_loader(ModelLoader* loader)
{
    loader_ = loader;
}


Model& ModelManager::create_model()
{
    std::list<Model>::iterator it = create_model_it_();
    return *it;
}


Model& ModelManager::create_named_model(const std::string& name)
{
    validate_name_(name);
    std::list<Model>::iterator it = create_model_it_();
    model_lookup_[name] = it;
    return *it;
}


Model& ModelManager::load_model(const std::string& path)
{
    std::unordered_map<
            std::string,
            std::list<Model>::iterator>::const_iterator
        mit = path_cache_.find(path);
    if (mit != path_cache_.end())
        return *mit->second;
    std::list<Model>::iterator it = create_model_it_();
    path_cache_[path] = it;
    loader_->load_model_from_file(path, *it);
    return *it;
}


Model& ModelManager::load_named_model(const std::string& name, const std::string& path)
{
    validate_name_(name);
    std::unordered_map<
            std::string,
            std::list<Model>::iterator>::const_iterator
        mit = path_cache_.find(path);
    if (mit != path_cache_.end()) {
        model_lookup_[name] = mit->second; 
        return *mit->second;
    }
    std::list<Model>::iterator it = create_model_it_();
    path_cache_[path] = it;
    model_lookup_[name] = it;
    loader_->load_model_from_file(path, *it);
    return *it;
}


Model* ModelManager::get_model(const std::string& name)
{
    std::unordered_map<
            std::string,
            std::list<Model>::iterator>::const_iterator
        mit = model_lookup_.find(name);
    if (mit == model_lookup_.end()) 
        return nullptr;
    return &*mit->second;
}


void ModelManager::validate_name_(const std::string& name)
{
    std::unordered_map<
            std::string,
            std::list<Model>::iterator>::const_iterator
        mit = model_lookup_.find(name);
    if (mit != model_lookup_.end()) 
        throw DuplicateError("Model", name);
}


std::list<Model>::iterator ModelManager::create_model_it_()
{
    models_.emplace_back();
    return std::prev(models_.end());
}


}
