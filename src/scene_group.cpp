#include "scene_group.hpp"

namespace dragonslave {


SceneGroup::SceneGroup() { }


SceneGroup::~SceneGroup() { }


void SceneGroup::create(Scene* scene)
{
    SceneNode::create(scene);
}


void SceneGroup::destroy()
{
    children_.clear();
    SceneNode::destroy();
}


void SceneGroup::add_child(SceneNode* child)
{
    children_.add(&child->sibling_node);
}


void SceneGroup::remove_child(SceneNode* child)
{
    children_.remove(&child->sibling_node);
}


void SceneGroup::update_world()
{
    SceneNode::update_world();
    LinkedListNode<SceneNode>* it = children_.get_head();
    while (it) {
        it->data->need_world_update();
        it = it->next;
    }
}


void SceneGroup::accept(SceneVisitor* visitor)
{
    visitor->visit(this);
}


void SceneGroup::traverse_children(SceneVisitor* visitor)
{
    LinkedListNode<SceneNode>* it = children_.get_head();
    while (it) {
        it->data->accept(visitor);
        it = it->next;
    }
}


}
