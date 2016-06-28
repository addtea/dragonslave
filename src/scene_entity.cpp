#include <glm/gtc/matrix_transform.hpp>
#include "scene_entity.hpp"
#include "scene_group.hpp"

namespace dragonslave {


SceneEntity::SceneEntity() { }


SceneEntity::~SceneEntity() { }


void SceneEntity::create(Scene* scene)
{
    SceneSpatial::create(scene);
    scale = glm::vec3{1.f, 1.f, 1.f};
    world_matrix = glm::mat4{1.f};
    model = nullptr;
}


void SceneEntity::update_world()
{
    SceneSpatial::update_world();
    model_matrix = world_matrix * glm::scale(glm::mat4{1.f}, scale);
}


void SceneEntity::accept(SceneVisitor* visitor)
{
    visitor->visit(this);
}


}
