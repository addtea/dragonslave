#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "scene_visitor.hpp"
#include "linked_list.hpp"

namespace dragonslave {


class SceneGroup;
class Scene;


class SceneSpatial
{
public:
    Scene* scene;
    SceneGroup* parent;
    glm::vec3 position;
    glm::quat orientation;
    glm::mat4 world_matrix;
    LinkedListNode<SceneSpatial> sibling_node;
    
    SceneSpatial();
    virtual ~SceneSpatial();

    bool is_world_updated() const { return world_updated_; }

    virtual void accept(SceneVisitor* visitor) = 0;
    virtual void create(Scene* scene);
    virtual void destroy();
    void request_world_update();
    virtual void update_world();

private:
    bool world_updated_ = false;
};


}
