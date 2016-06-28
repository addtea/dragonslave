#pragma once

#include "linked_list.hpp"
#include "scene_spatial.hpp"

namespace dragonslave {


class SceneGroup : public SceneSpatial
{
public:
    SceneGroup();
    virtual ~SceneGroup();

    virtual void create(Scene* scene) override;
    virtual void destroy() override;

    void add_child(SceneSpatial* child);
    void remove_child(SceneSpatial* child);

    virtual void accept(SceneVisitor* visitor) override;
    virtual void update_world() override;
    virtual void traverse_children(SceneVisitor* visitor);

private:
    LinkedList<SceneSpatial> children_;
};


}
