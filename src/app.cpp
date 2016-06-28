#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "app.hpp"
#include "log.hpp"
#include "shaders/basic_shader.hpp"

namespace dragonslave {


App::App() { }


App::~App() { }


void App::run()
{
    init_();
    setup_scene_();

    glEnable(GL_DEPTH_TEST);
    is_running_ = true;
    while (is_running_ && !window.should_close()) {
        while (int error = glGetError()) { 
            LOG(ERROR) << "GL error " << error;
        }
        poll_();
        input.flush_events();

        scene.update();
        flight.camera->translate(flight.camera->get_forward() * flight.forward_speed * 0.2f);
        flight.camera->translate(flight.camera->get_right() * flight.lateral_speed * 0.2f);

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        scene_renderer.render();

        window.swap_buffers();
    }

    destroy_();
}


void App::init_()
{
    if (!glfwInit()) {
        throw FatalError("AppInitError", "Failed to initialize GLFW");
    }

    GLFormat gl_format;
    WindowConfig window_config;
    window_config.title = "Game";

    input.add_handler(this);

    window.initialize(&input, gl_format, window_config);
    gc.initialize(&window);
    geometry_manager.initialize(&gc);
    material_manager.initialize();
    image_manager.initialize(&gc, &image_loader);
    shader_manager.initialize(&gc);
    model_manager.initialize(
        &geometry_manager,
        &material_manager,
        &image_manager,
        &shader_manager,
        &model_loader);
}


void App::setup_scene_()
{
    glViewport(0, 0, 800, 600);

    Shader* shader = shader_manager.create_shader<BasicShader>();
    shader_manager.set_default_shader(shader);

    Geometry* geometry = geometry_manager.create_geometry();
    geometry_generator.generate_cylinder(1.f, 2.f, 20, geometry);
    geometry->upload();
    Material* material = material_manager.create_material();
    material->has_diffuse_map = false;
    material->diffuse_color = {1.f, 1.f, 0.f};
    Model* model = model_manager.create_model();
    model->add_mesh(geometry, material, shader);
    
    SceneEntity* entity = scene.create_entity();
    entity->model = model;
    scene.get_root()->add_child(entity);

    SceneCamera* camera = scene.create_camera();
    float aspect = 800.f / 600.f;
    camera->projection_matrix = glm::perspective(1.f, aspect, 0.1f, 1000.f);
    camera->position = glm::vec3{0.f, 10.f, 20.f};
    camera->look_at({0.f, 0.f, 0.f}, {0.f, 1.f, 0.f});
    camera->update_view();
    
    scene_renderer.set_scene(&scene);
    scene_renderer.set_active_camera(camera);

    flight.camera = camera;

    window.set_cursor_mode(WindowCursorMode::LOCKED);
}


void App::destroy_() {
    model_manager.terminate();
    shader_manager.terminate();
    image_manager.terminate();
    material_manager.terminate();
    geometry_manager.terminate();
    gc.terminate();
    window.terminate();

    glfwTerminate();
}


void App::poll_() 
{
    glfwPollEvents();
}


void App::handle(const KeyboardInputEvent& event) 
{
    LOG(INFO) << "key event " << event.key << " " << event.action;
    if (event.key == GLFW_KEY_ESCAPE && event.action == GLFW_RELEASE) {
        LOG(INFO) << "quit";
        is_running_ = false;
    }
    if (event.key == GLFW_KEY_W) {
        if (event.action == GLFW_PRESS)
            flight.forward_speed += 1.f;
        if (event.action == GLFW_RELEASE)
            flight.forward_speed -= 1.f;
    }
    if (event.key == GLFW_KEY_D) {
        if (event.action == GLFW_PRESS)
            flight.lateral_speed += 1.f;
        if (event.action == GLFW_RELEASE)
            flight.lateral_speed -= 1.f;
    }
    if (event.key == GLFW_KEY_S) {
        if (event.action == GLFW_PRESS)
            flight.forward_speed -= 1.f;
        if (event.action == GLFW_RELEASE)
            flight.forward_speed += 1.f;
    }
    if (event.key == GLFW_KEY_A) {
        if (event.action == GLFW_PRESS)
            flight.lateral_speed -= 1.f;
        if (event.action == GLFW_RELEASE)
            flight.lateral_speed += 1.f;
    }
}


void App::handle(const MouseMotionInputEvent& event) 
{
    float angle_x = 0.002f * event.dx;
    float angle_y = 0.002f * event.dy;
    glm::vec4 forward = glm::vec4(flight.camera->get_forward(), 0);
    forward = 
        glm::rotate(glm::mat4{1.f}, -angle_x, glm::vec3{0.f, 1.f, 0.f}) * 
        glm::rotate(glm::mat4{1.f}, -angle_y, flight.camera->get_right()) * 
        forward;
    flight.camera->look_at(
        flight.camera->position + glm::vec3(forward),
        glm::vec3{0.f, 1.f, 0.f});
}


}
