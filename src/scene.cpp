#include "scene.hpp"

namespace dragonslave {
    

Scene::Scene() 
{ 
    entity_indices_.create(ENTITY_POOL_SIZE);
    camera_indices_.create(CAMERA_POOL_SIZE);
    group_indices_.create(GROUP_POOL_SIZE);
    light_indices_.create(LIGHT_POOL_SIZE);

    root_ = create_group();
}


Scene::~Scene() { }


SceneCamera* Scene::create_camera()
{
    int id = camera_indices_.request_index();
    SceneCamera* camera = &camera_pool_[id];
    camera->create(this);
    return camera;
}


SceneEntity* Scene::create_entity()
{
    int id = entity_indices_.request_index();
    SceneEntity* entity = &entity_pool_[id];
    entity->create(this);
    return entity;
}


SceneGroup* Scene::create_group()
{
    int id = group_indices_.request_index();
    SceneGroup* group = &group_pool_[id];
    group->create(this);
    return group;
}


SceneLight* Scene::create_light()
{
    int id = light_indices_.request_index();
    SceneLight* light = &light_pool_[id];
    light->create(this);
    return light;
}


void Scene::destroy_camera(SceneCamera* camera)
{
    int id = camera - camera_pool_.data();
    if (id < camera_pool_.size()) {
        camera_indices_.free_index(id);
        camera->destroy();
    }
}


void Scene::destroy_entity(SceneEntity* entity)
{
    int id = entity - entity_pool_.data();
    if (id < entity_pool_.size()) {
        entity_indices_.free_index(id);
        entity->destroy();
    }
}


void Scene::destroy_group(SceneGroup* group)
{
    int id = group - group_pool_.data();
    if (id < group_pool_.size()) {
        group_indices_.free_index(id);
        group->destroy();
    }
}


void Scene::destroy_light(SceneLight* light)
{
    int id = light - light_pool_.data();
    if (id < light_pool_.size()) {
        light_indices_.free_index(id);
        light->destroy();
    }
}


void Scene::update()
{
    SceneUpdateVisitor visitor;
    traverse(&visitor);
}


void Scene::clear()
{
    entity_indices_.clear();
    group_indices_.clear();
    light_indices_.clear();

    for (SceneCamera& camera : camera_pool_) camera.destroy();
    for (SceneEntity& entity : entity_pool_) entity.destroy();
    for (SceneGroup& group : group_pool_) group.destroy();
    for (SceneLight& light : light_pool_) light.destroy();

    root_ = create_group();
}


void Scene::traverse(SceneVisitor* visitor)
{
    root_->accept(visitor);
}


SceneUpdateVisitor::SceneUpdateVisitor() { }


SceneUpdateVisitor::~SceneUpdateVisitor() { }


void SceneUpdateVisitor::visit(SceneEntity* entity)
{
    if (!entity->is_world_updated())
        entity->update_world();
}


void SceneUpdateVisitor::visit(SceneGroup* group)
{
    if (!group->is_world_updated())
        group->update_world();
    group->traverse_children(this);
}


void SceneUpdateVisitor::visit(SceneLight* light)
{
    if (!light->is_world_updated())
        light->update_world();
}


SceneCullVisitor::SceneCullVisitor(SceneCamera* camera)
  : camera_ (camera)
{ }


SceneCullVisitor::~SceneCullVisitor() { }


void SceneCullVisitor::visit(SceneEntity* entity)
{
    visible_entities_.push_back(entity);
}


void SceneCullVisitor::visit(SceneGroup* group)
{
    group->traverse_children(this);
}


}
