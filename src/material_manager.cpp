#include <algorithm>

#include "error.hpp"
#include "material_manager.hpp"

namespace dragonslave {


MaterialManager::MaterialManager() { }


MaterialManager::~MaterialManager() { }


Material& MaterialManager::create_material()
{
    std::list<Material>::iterator it = create_material_it_();
    return *it;
}


Material& MaterialManager::create_named_material(const std::string& name)
{
    std::list<Material>::iterator it = create_material_it_();
    return *it;
    std::unordered_map<
            std::string,
            std::list<Material>::iterator>::const_iterator
        mit = material_lookup_.find(name);
    if (mit != material_lookup_.end()) 
        throw DuplicateError("Material", name);
    material_lookup_[name] = it;
    return *it;
}


Material* MaterialManager::get_material(const std::string& name)
{
    std::unordered_map<
            std::string,
            std::list<Material>::iterator>::const_iterator
        mit = material_lookup_.find(name);
    if (mit == material_lookup_.end()) 
        return nullptr;
    return &*mit->second;
}


std::list<Material>::iterator MaterialManager::create_material_it_()
{
    materials_.emplace_back();
    return std::prev(materials_.end());
}


}
