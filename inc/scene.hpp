#pragma once

#include <array>
#include "scene_entity.hpp"
#include "scene_camera.hpp"
#include "scene_group.hpp"
#include "scene_light.hpp"
#include "scene_visitor.hpp"
#include "index_pool.hpp"

namespace dragonslave {


class Scene
{
public:
    Scene();
    virtual ~Scene();

    SceneGroup* get_root() { return root_; }

    SceneCamera* create_camera();
    SceneEntity* create_entity();
    SceneGroup* create_group();
    SceneLight* create_light();

    void destroy_camera(SceneCamera* camera);
    void destroy_entity(SceneEntity* entity);
    void destroy_group(SceneGroup* group);
    void destroy_light(SceneLight* light);

    void clear();
    void traverse(SceneVisitor* visitor);
    void update();

private:
    constexpr static int CAMERA_POOL_SIZE = 100;
    constexpr static int ENTITY_POOL_SIZE = 10000;
    constexpr static int GROUP_POOL_SIZE  = 1000;
    constexpr static int LIGHT_POOL_SIZE  = 1000;

    IndexPool entity_indices_;
    std::array<SceneEntity, ENTITY_POOL_SIZE> entity_pool_;
    IndexPool camera_indices_;
    std::array<SceneCamera, CAMERA_POOL_SIZE> camera_pool_;
    IndexPool group_indices_;
    std::array<SceneGroup, GROUP_POOL_SIZE> group_pool_;
    IndexPool light_indices_;
    std::array<SceneLight, LIGHT_POOL_SIZE> light_pool_;

    SceneGroup* root_;
};


class SceneUpdateVisitor : public SceneVisitor
{
public:
    SceneUpdateVisitor();
    virtual ~SceneUpdateVisitor();

    virtual void visit(SceneCamera* camera) override;
    virtual void visit(SceneEntity* entity) override;
    virtual void visit(SceneGroup* group) override;
    virtual void visit(SceneLight* light) override;
};


class SceneCullVisitor : public SceneVisitor
{
public:
    SceneCullVisitor(SceneCamera* camera);
    virtual ~SceneCullVisitor();

    const std::vector<SceneEntity*>& get_visible_entities()
    { return visible_entities_; }

    virtual void visit(SceneEntity* entity) override;
    virtual void visit(SceneGroup* group) override;

private:
    SceneCamera* camera_;
    std::vector<SceneEntity*> visible_entities_;
};


}
