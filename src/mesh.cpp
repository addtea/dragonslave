#include "mesh.hpp"

namespace dragonslave {


Mesh::Mesh() { }


Mesh::~Mesh() { }


void Mesh::create() 
{ 
    bound.is_null = true;
    bound.is_infinite = false;
    bound.center = glm::vec3{0.f, 0.f, 0.f};
    bound.radius = 0.f;
}


void Mesh::destroy() 
{ 
    reset();
}


void Mesh::add_submesh(Geometry* geometry, Material* material, Shader* shader)
{
    submeshes_.push_back({geometry, material, shader});
}


void Mesh::update_bound()
{
    // Check for empty submesh
    if (submeshes_.empty() || submeshes_.front().geometry->positions.empty()) {
        bound.is_null = true;
        return;
    }
    // Using bouncing bubble algorithm
    bound.center = submeshes_.front().geometry->positions.front();
    bound.radius = 0.1f;
    for (int i = 0; i < 2; i++) {
        for (Submesh& submesh : submeshes_) {
            for (const glm::vec3& position: submesh.geometry->positions) {
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
    for (Submesh& submesh : submeshes_) {
        for (const glm::vec3& position: submesh.geometry->positions) {
            glm::vec3 diff = position - bound.center;
            float diff_len = glm::length(diff);
            if (diff_len > bound.radius) {
                bound.radius = (bound.radius + diff_len) / 2.f;
                bound.center += ((diff_len - bound.radius) / diff_len) * diff;
            }
        }
    }
}


void Mesh::reset() 
{
    submeshes_.clear();
}


}
