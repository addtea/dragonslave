#pragma once

#include <list>
#include <unordered_map>

#include "material.hpp"

namespace dragonslave {


class MaterialManager
{
public:
    MaterialManager();
    ~MaterialManager();

    Material& create_material();
    Material& create_named_material(const std::string& name);

    Material* get_material(const std::string& name);

private:    
    std::unordered_map<
            std::string,
            std::list<Material>::iterator>
        material_lookup_;
    std::list<Material> materials_;

    std::list<Material>::iterator create_material_it_();
};


}
