#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "scene_spatial.hpp"
#include "frustrum.hpp"

namespace dragonslave {


class SceneCamera : public SceneSpatial
{
public:
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;
    Frustrum frustrum;

    SceneCamera();
    virtual ~SceneCamera();

    virtual void create(Scene* scene) override;
    virtual void destroy() override;

    void update_view();
    void update_frustrum();
    void look_at(const glm::vec3& target, const glm::vec3& up);
};

    
}
