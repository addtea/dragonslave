#pragma once

#include "model.hpp"
#include "scene_spatial.hpp"

namespace dragonslave {


class SceneEntity : public SceneSpatial
{
public:
    glm::vec3 scale;
    glm::mat4 model_matrix;
    Model* model;

    SceneEntity();
    virtual ~SceneEntity();

    virtual void create(Scene* scene) override;

    virtual void accept(SceneVisitor* visitor) override;
    virtual void update_world() override;
};


}
