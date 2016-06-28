#pragma once

#include "scene_node.hpp"

namespace dragonslave {


enum class SceneLightType
{
    POINT,
    DIRECTIONAL,
    SPOT
};


class SceneLight : public SceneNode
{
public:
    SceneLightType type;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant_attenuation;
    float linear_attenuation;
    float quadratic_attenuation;
    float spot_exponent;
    float inner_cutoff;
    float outer_cutoff;

    SceneLight();
    virtual ~SceneLight();

    virtual void create(Scene* scene) override;

    virtual void accept(SceneVisitor* visitor) override;
};


}
