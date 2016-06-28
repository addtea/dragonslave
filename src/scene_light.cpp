#include "scene_light.hpp"

namespace dragonslave {


SceneLight::SceneLight() { }


SceneLight::~SceneLight() { }


void SceneLight::create(Scene* scene)
{
    SceneSpatial::create(scene);
    type = SceneLightType::POINT;
    ambient  = {0.0f, 0.0f, 0.0f};
    diffuse  = {1.0f, 1.0f, 1.0f};
    specular = {1.0f, 1.0f, 1.0f};
    constant_attenuation  = 0.0f;
    linear_attenuation    = 0.0;
    quadratic_attenuation = 1.0f;
    spot_exponent = 50.0f;
    inner_cutoff  = 1.0f;
    outer_cutoff = 1.0f;
}


void SceneLight::accept(SceneVisitor* visitor)
{
    visitor->visit(this);
}


}
