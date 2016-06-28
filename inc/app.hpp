#pragma once

#include "error.hpp"
#include "graphics_context.hpp"
#include "geometry_manager.hpp"
#include "geometry_generator.hpp"
#include "image_loader.hpp"
#include "image_manager.hpp"
#include "input_queue.hpp"
#include "material_manager.hpp"
#include "model_loader.hpp"
#include "model_manager.hpp"
#include "scene.hpp"
#include "scene_renderer.hpp"
#include "shader_manager.hpp"
#include "window.hpp"

namespace dragonslave {


// Temporary POD for exploring scene
struct FlightState
{
    SceneCamera* camera = nullptr;
    float forward_speed = 0.f;
    float lateral_speed = 0.f;
};



class App : public InputEventHandler
{
public:
    ImageLoader image_loader;
    ModelLoader model_loader;

    GraphicsContext gc;
    GeometryManager geometry_manager;
    GeometryGenerator geometry_generator;
    ImageManager image_manager;
    InputQueue input;
    MaterialManager material_manager;
    ModelManager model_manager;
    ShaderManager shader_manager;
    Window window;

    Scene scene;
    SceneRenderer scene_renderer;

    FlightState flight;

    App();
    virtual ~App();

    void run();
    void handle(const KeyboardInputEvent& event) override;
    void handle(const MouseMotionInputEvent& event) override;

private:
    bool is_running_ = false;

    void init_();
    void destroy_();
    void poll_();
    void setup_scene_();
};


}
