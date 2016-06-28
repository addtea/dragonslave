#pragma once

#include "scene_spatial.hpp"
#include "scene_visitor.hpp"
#include "linked_list.hpp"

namespace dragonslave {


class SceneGroup;


class SceneNode : public SceneSpatial
{
public:
    bool is_visible = true;
    SceneGroup* parent;
    glm::mat4 world_matrix;
    LinkedListNode<SceneNode> sibling_node;

    SceneNode();
    virtual ~SceneNode();

    virtual void create(Scene* scene) override;
    virtual void destroy() override;

    bool is_world_updated() const { return world_updated_; }
    void need_world_update();
    virtual void update_world();
    virtual void accept(SceneVisitor* visitor) = 0;

private:
    bool world_updated_ = false;
};


}
