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


void SceneCamera::accept(SceneVisitor* visitor)
{
    visitor->visit(this);
}


void SceneCamera::update_view()
{
    view_matrix = glm::inverse(world_matrix);
}


void SceneCamera::update_frustrum()
{
    frustrum.apply_projection_matrix(projection_matrix);
}


void SceneCamera::look_at(const glm::vec3& target, const glm::vec3& up)
{
    update_view();
    glm::vec3 local_forward = glm::vec3(glm::normalize(view_matrix * glm::vec4(target, 1)));
    glm::vec3 local_up = glm::vec3(view_matrix * glm::vec4(up, 1));
    glm::vec3 local_right = glm::normalize(glm::cross(local_forward, local_up));
    local_up = glm::normalize(glm::cross(local_right, local_forward));
    glm::mat3 local_basis {local_right, local_up, -local_forward};
    orientation = glm::quat_cast(local_basis);
    request_world_update();
}


}
