#include <glm/gtc/matrix_transform.hpp>
#include "scene_group.hpp"
#include "scene_node.hpp"

namespace dragonslave {


SceneNode::SceneNode() 
  : sibling_node {this}
{ }


SceneNode::~SceneNode() { }


void SceneNode::create(Scene* scene)
{
    SceneSpatial::create(scene);
    parent = nullptr;
    world_matrix = glm::mat4{1.f};
    world_updated_ = false;
}


void SceneNode::destroy()
{
    if (parent) parent->remove_child(this);
}


void SceneNode::need_world_update() 
{
    // TODO(eugene): have notification channel for scene
    world_updated_ = false;
}


void SceneNode::update_world()
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
