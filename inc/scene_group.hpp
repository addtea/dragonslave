#pragma once

#include "linked_list.hpp"
#include "scene_node.hpp"

namespace dragonslave {


class SceneGroup : public SceneNode
{
public:
    SceneGroup();
    virtual ~SceneGroup();

    virtual void create(Scene* scene) override;
    virtual void destroy() override;

    void add_child(SceneNode* child);
    void remove_child(SceneNode* child);

    virtual void accept(SceneVisitor* visitor) override;
    virtual void update_world() override;
    virtual void traverse_children(SceneVisitor* visitor);

private:
    LinkedList<SceneNode> children_;
};


}
