#pragma once
#include <vector>
#include "mesh.hpp"
#include "material.hpp"

namespace dragonslave {

struct Model {
    std::vector<Mesh> meshes;
    std::vector<Material> materials;

    void add_mesh(Mesh mesh) { meshes.push_back(mesh); }
    void add_material(Material material) { materials.push_back(material); }

    void remove_mesh(Mesh mesh) {
        std::vector<Mesh>::iterator it = std::find(
                meshes.begin(), meshes.end(), mesh);
        if (it != meshes.end()) meshes.erase(it);
    }

    void remove_material(Material material) {
        std::vector<material>::iterator it = std::find(
                materials.begin(), materials.end(), material);
        if (it != materials.end()) materials.erase(it);
    }
};


}
