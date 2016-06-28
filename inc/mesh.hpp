#pragma once

#include "geometry.hpp"
#include "material.hpp"
#include "shader.hpp"

namespace dragonslave {


struct Mesh 
{
    Geometry* geometry;
    Material* material;
    Shader* shader;
};


}
