#include "scene.hpp"
#include "scene_spatial.hpp"

namespace dragonslave {


SceneSpatial::SceneSpatial() { }


SceneSpatial::~SceneSpatial() { }


void SceneSpatial::create(Scene* scene) 
{
    this->scene = scene;
    position = glm::vec3{0.f, 0.f, 0.f};
    orientation = glm::quat{1.f, 0.f, 0.f, 0.f};
}


void SceneSpatial::destroy() { }


}
