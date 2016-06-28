#pragma once

#include <list>
#include "string_manager.hpp"
#include "material.hpp"

namespace dragonslave {


class MaterialManager
{
public:
    MaterialManager();
    virtual ~MaterialManager();

    void initialize();
    void terminate();

    Material* create_material();
    void destroy_material(Material* material);

private:
    std::list<Material> materials_;
};


}
