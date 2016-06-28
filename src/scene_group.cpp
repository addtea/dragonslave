#include "scene_group.hpp"

namespace dragonslave {


SceneGroup::SceneGroup() { }


SceneGroup::~SceneGroup() { }


void SceneGroup::create(Scene* scene)
{
    SceneSpatial::create(scene);
}


void SceneGroup::destroy()
{
    children_.clear();
    SceneSpatial::destroy();
}


void SceneGroup::add_child(SceneSpatial* child)
{
    children_.add(&child->sibling_node);
}


void SceneGroup::remove_child(SceneSpatial* child)
{
    children_.remove(&child->sibling_node);
}


void SceneGroup::update_world()
{
    SceneSpatial::update_world();
    LinkedListNode<SceneSpatial>* it = children_.get_head();
    while (it) {
        it->data->request_world_update();
        it = it->next;
    }
}


void SceneGroup::accept(SceneVisitor* visitor)
{
    visitor->visit(this);
}


void SceneGroup::traverse_children(SceneVisitor* visitor)
{
    LinkedListNode<SceneSpatial>* it = children_.get_head();
    while (it) {
        it->data->accept(visitor);
        it = it->next;
    }
}


}
