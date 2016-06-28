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
}


void SceneCamera::destroy() { }


void SceneCamera::update_view()
{
    glm::mat4 world_matrix = 
        glm::translate(glm::mat4{1.f}, position) *
        glm::mat4_cast(orientation);
    view_matrix = glm::inverse(world_matrix);
}


void SceneCamera::update_frustrum()
{
    frustrum.apply_projection_matrix(projection_matrix);
}


void SceneCamera::look_at(const glm::vec3& target, const glm::vec3& up)
{
    glm::vec3 local_forward = glm::normalize(target - position);
    glm::vec3 local_right = glm::normalize(glm::cross(local_forward, up));
    glm::vec3 local_up = glm::normalize(glm::cross(local_right, local_forward));
    glm::mat3 local_basis {local_right, local_up, -local_forward};
    orientation = glm::quat_cast(local_basis);
}


}
