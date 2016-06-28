#pragma once

#include "scene.hpp"
#include "scene_camera.hpp"

namespace dragonslave {


class SceneRenderer
{
public:
    SceneRenderer();
    virtual ~SceneRenderer();

    void initialize(GraphicsContext* gc);
    void terminate();

    void set_scene(Scene* scene);
    void set_active_camera(SceneCamera* camera);
    void set_viewport(int width, int height);

    void render();

private:
    GraphicsContext* gc_ = nullptr;
    Scene* scene_ = nullptr;
    SceneCamera* active_camera_ = nullptr;
};


}
