#include <algorithm>
#include "material_manager.hpp"

namespace dragonslave {


MaterialManager::MaterialManager() { }


MaterialManager::~MaterialManager() { }


void MaterialManager::initialize() { }


void MaterialManager::terminate() { }


Material* MaterialManager::create_material()
{
    materials_.emplace_back();
    return &materials_.back();
}


void MaterialManager::destroy_material(Material* material)
{
    std::remove_if(
        materials_.begin(),
        materials_.end(),
        [=](Material& stored_material) {
            return &stored_material == material;
        });
}


}
