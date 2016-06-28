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

    const glm::vec3& get_forward() { return forward_; }
    const glm::vec3& get_up() { return up_; }
    const glm::vec3& get_right() { return right_; }

    void update_view();
    void update_frustrum();
    void look_at(const glm::vec3& target, const glm::vec3& up);

private:
    glm::vec3 forward_;
    glm::vec3 up_;
    glm::vec3 right_;
};

    
}
