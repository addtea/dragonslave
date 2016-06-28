#include "model.hpp"

namespace dragonslave {


Model::Model() { }


Model::~Model() { }


void Model::create()
{
    reset();
}


void Model::destroy() { }


void Model::add_mesh(Geometry* geometry, Material* material, Shader* shader)
{
    meshes_.push_back({geometry, material, shader});
}


void Model::update_bound()
{
    // Check for empty mesh
    if (meshes_.empty() || meshes_.front().geometry->positions.empty()) {
        bound.is_null = true;
        return;
    }
    // Using bouncing bubble algorithm
    bound.center = meshes_.front().geometry->positions.front();
    bound.radius = 0.1f;
    for (int i = 0; i < 2; i++) {
        for (Mesh& mesh : meshes_) {
            for (const glm::vec3& position: mesh.geometry->positions) {
                glm::vec3 diff = position - bound.center;
                float diff_len = glm::length(diff);
                if (diff_len > bound.radius) {
                    float alpha = diff_len / bound.radius;
                    float alpha_sq = alpha * alpha;
                    bound.radius = 0.5f * (alpha + 1 / alpha) * bound.radius;
                    bound.center = 0.5f * (
                        (1 + 1 / alpha_sq) * bound.center + 
                        (1 - 1 / alpha_sq) * position);
                }
            }
        }
    }
    for (Mesh& mesh : meshes_) {
        for (const glm::vec3& position: mesh.geometry->positions) {
            glm::vec3 diff = position - bound.center;
            float diff_len = glm::length(diff);
            if (diff_len > bound.radius) {
                bound.radius = (bound.radius + diff_len) / 2.f;
                bound.center += ((diff_len - bound.radius) / diff_len) * diff;
            }
        }
    }
}


void Model::reset() 
{
    meshes_.clear();
}


}
