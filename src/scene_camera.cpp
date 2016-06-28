#include <glm/gtc/matrix_transform.hpp>
#include "scene_camera.hpp"

namespace dragonslave {
    

SceneCamera::SceneCamera() { }


SceneCamera::~SceneCamera() { }


void SceneCamera::create(Scene* scene)
{
    SceneSpatial::create(scene);
    view_matrix = glm::mat4{1.f};
    projection_matrix = glm::mat4{1.f};
    forward_ = {0.f, 0.f, -1.f};
    up_ = {0.f, 1.f, 0.f};
    right_ = {1.f, 0.f, 0.f};
}


void SceneCamera::destroy() { }


void SceneCamera::update_view()
{
    glm::mat4 world_matrix;
    world_matrix[0] = glm::vec4{right_, 0.f};
    world_matrix[1] = glm::vec4{up_, 0.f};
    world_matrix[2] = glm::vec4{-forward_, 0.f};
    world_matrix[3] = glm::vec4{position, 1.f};
    view_matrix = glm::inverse(world_matrix);
}


void SceneCamera::update_directions()
{
    glm::mat4 basis = glm::mat4_cast(orientation);
    forward_ = -glm::vec3(basis[2]);
    up_ = glm::vec3(basis[1]);
    right_ = glm::vec3(basis[0]);
}


void SceneCamera::update_frustrum()
{
    frustrum.apply_projection_matrix(projection_matrix);
}


void SceneCamera::look_at(const glm::vec3& target, const glm::vec3& up)
{
    forward_ = glm::normalize(target - position);
    right_ = glm::normalize(glm::cross(forward_, up));
    up_ = glm::normalize(glm::cross(right_, forward_));
    glm::mat3 local_basis {right_, up_, -forward_};
    orientation = glm::quat_cast(local_basis);
}


}
