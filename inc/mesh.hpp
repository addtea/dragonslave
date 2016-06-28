#pragma once

#include "geometry.hpp"
#include "material.hpp"
#include "shader.hpp"

namespace dragonslave {


struct Mesh 
{
    Geometry* geometry = nullptr;
    Material* material = nullptr;
    Shader* shader = nullptr;
};


}
