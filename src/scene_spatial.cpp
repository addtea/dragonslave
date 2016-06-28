#include <glm/gtc/matrix_transform.hpp>
#include "scene.hpp"
#include "scene_spatial.hpp"

namespace dragonslave {


SceneSpatial::SceneSpatial() 
  : sibling_node (this)
{ }


SceneSpatial::~SceneSpatial() { }


void SceneSpatial::create(Scene* scene) 
{
    this->scene = scene;
    parent = nullptr;
    world_updated_ = false;
    position = glm::vec3{0.f, 0.f, 0.f};
    orientation = glm::quat{1.f, 0.f, 0.f, 0.f};
    world_matrix = glm::mat4{1.f};
}


void SceneSpatial::destroy()
{
    if (parent) parent->remove_child(this);
}


void SceneSpatial::request_world_update()
{
    // TODO(eugene): have notification channel for scene
    world_updated_ = false;
}


void SceneSpatial::update_world()
{
    glm::mat4 local_matrix = 
        glm::translate(glm::mat4{1.f}, position) *
        glm::mat4_cast(orientation);
    if (!parent) {
        world_matrix = local_matrix;
    } else {
        world_matrix = parent->world_matrix * local_matrix;
    }
    world_updated_ = true;
}


}
