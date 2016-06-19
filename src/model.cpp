#include "model.hpp"

namespace dragonslave {


Model::Model() { }


Model::~Model() { }


void Model::add_mesh(Geode* geode, Material* material)
{
    meshes_.emplace_back(geode, material);
}


}
