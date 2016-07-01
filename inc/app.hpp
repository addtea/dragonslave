#pragma once

#include "error.hpp"
#include "graphics_context.hpp"
#include "geometry_manager.hpp"
#include "geometry_generator.hpp"
#include "image_loader.hpp"
#include "image_manager.hpp"
#include "input_queue.hpp"
#include "material_manager.hpp"
#include "mesh_loader.hpp"
#include "mesh_manager.hpp"
#include "scene.hpp"
#include "scene_renderer.hpp"
#include "shader_manager.hpp"
#include "window.hpp"

namespace dragonslave {


class App : public InputEventHandler
{
public:
    ImageLoader image_loader;
    MeshLoader mesh_loader;

    GraphicsContext gc;
    GeometryManager geometry_manager;
    GeometryGenerator geometry_generator;
    ImageManager image_manager;
    InputQueue input;
    MaterialManager material_manager;
    MeshManager mesh_manager;
    ShaderManager shader_manager;
    Window window;

    Scene scene;
    SceneRenderer scene_renderer;

    App();
    virtual ~App();

    void run();
    void handle(const KeyboardInputEvent& event) override;
    void handle(const MouseMotionInputEvent& event) override;
    void handle(const MouseButtonInputEvent& event) override;
    void handle(const MouseScrollInputEvent& event) override;

private:
    bool is_running_ = false;

    void init_();
    void destroy_();
    void poll_();
    void setup_scene_();
};


}
