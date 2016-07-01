#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "app.hpp"
#include "log.hpp"
#include "shaders/basic_shader.hpp"

namespace dragonslave {


// Temporary POD for storing game state
struct GameState
{
    SceneCamera* camera = nullptr;
    SceneEntity* cursor = nullptr;
    Mesh* obstacle_mesh = nullptr;
};


static GameState gs;


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
    mesh_manager.initialize(
        &geometry_manager,
        &material_manager,
        &image_manager,
        &shader_manager,
        &mesh_loader);
}


void App::setup_scene_()
{
    glViewport(0, 0, 800, 600);

    Shader* shader = shader_manager.create_shader<BasicShader>();
    shader_manager.set_default_shader(shader);

    Geometry* plane = geometry_manager.create_geometry();
    Geometry* cube = geometry_manager.create_geometry();
    Geometry* cylinder = geometry_manager.create_geometry();

    geometry_generator.generate_plane(1.f, plane);
    plane->upload();

    geometry_generator.generate_cube(0.5f, cube);
    cube->upload();

    geometry_generator.generate_cylinder(2.f, 0.5f, 16, cylinder);
    cylinder->upload();

    Material* ground_mat = material_manager.create_material();
    Material* selected_mat = material_manager.create_material();
    Material* obstacle_mat = material_manager.create_material();

    ground_mat->diffuse_color = glm::vec3{0.8f, 0.8f, 0.8f};
    selected_mat->diffuse_color = glm::vec3{0.0f, 1.f, 0.0f};
    obstacle_mat->diffuse_color = glm::vec3{1.0f, 1.f, 1.0f};

    Mesh* ground_mesh = mesh_manager.create_mesh();
    ground_mesh->add_submesh(plane, ground_mat, shader);

    Mesh* cursor_mesh = mesh_manager.create_mesh();
    cursor_mesh->add_submesh(cylinder, selected_mat, shader);

    gs.obstacle_mesh = mesh_manager.create_mesh();
    gs.obstacle_mesh->add_submesh(cube, obstacle_mat, shader);

    SceneEntity* ground_entity = scene.create_entity();
    ground_entity->mesh = ground_mesh;
    ground_entity->scale = glm::vec3{64.5f, 0.f, 64.5f};

    gs.cursor = scene.create_entity();
    gs.cursor->position = glm::vec3{0.f, 0.1f, 0.f};
    gs.cursor->mesh = cursor_mesh;
    gs.cursor->scale = glm::vec3{0.55f, 0.2f, 0.55f};

    scene.get_root()->add_child(ground_entity);
    scene.get_root()->add_child(gs.cursor);

    gs.camera = scene.create_camera();
    float aspect = 800.f / 600.f;
    gs.camera->projection_matrix = glm::perspective(1.f, aspect, 0.1f, 1000.f);
    gs.camera->position = glm::vec3{0.f, 12.f, 4.f};
    gs.camera->look_at({0.f, 0.f, 0.f}, {0.f, 0.f, -1.f});
    gs.camera->update_view();
    
    scene_renderer.set_scene(&scene);
    scene_renderer.set_active_camera(gs.camera);

    window.set_cursor_mode(WindowCursorMode::LOCKED);
}


void App::destroy_() {
    mesh_manager.terminate();
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
    if (event.key == GLFW_KEY_ESCAPE && event.action == GLFW_RELEASE) {
        LOG(INFO) << "quit";
        is_running_ = false;
    }
}


void App::handle(const MouseMotionInputEvent& event) 
{
    float camera_speed = 0.02f;
    float offset_scale = gs.camera->position.y / glm::dot(glm::vec3{0.f, -1.f, 0.f}, gs.camera->get_forward());
    // Calculate where vision is pointing at
    gs.camera->translate({event.dx * camera_speed, 0.f, event.dy * camera_speed});
    gs.camera->update_view();
    glm::vec3 ground_pos = 
        gs.camera->position +
        offset_scale * gs.camera->get_forward();
    gs.cursor->position.x = static_cast<int>(ground_pos.x);
    gs.cursor->position.z = static_cast<int>(ground_pos.z);
    gs.cursor->need_world_update();
}


void App::handle(const MouseButtonInputEvent& event) 
{
    if (event.button == 0 && event.action == GLFW_RELEASE) {
        SceneEntity* obstacle = scene.create_entity();
        obstacle->mesh = gs.obstacle_mesh;
        obstacle->position = gs.cursor->position;
        obstacle->position.y = 0.5f;
        scene.get_root()->add_child(obstacle);
    }
}


void App::handle(const MouseScrollInputEvent& event)
{
    float camera_speed = 0.02f;
    gs.camera->translate(static_cast<float>(event.scroll_y) * gs.camera->get_forward());
    gs.camera->update_view();
}


}
