#include <vector>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "app.hpp"
#include "log.hpp"
#include "shaders/basic_shader.hpp"
#include "nav_grid.hpp"

namespace dragonslave {


// Temporary POD for storing game state
struct GameState
{
    float cursor_x;
    float cursor_y;
    int grid_x;
    int grid_y;

    float magnify = 1.f;

    Geometry* path_geometry = nullptr;
    Geometry* prev_geometry = nullptr;
    SceneCamera* camera = nullptr;
    SceneEntity* cursor_entity = nullptr;
    Material* cursor_material = nullptr;
    Mesh* obstacle_mesh = nullptr;
    std::unordered_map<int, SceneEntity*> block_map;
    NavGrid grid;
} gs;


void update_cursor()
{
    gs.camera->position = {gs.cursor_x + 0.5f, gs.magnify * 10.f, gs.cursor_y + gs.magnify * 5.f + 1.5f};
    gs.camera->look_at({gs.cursor_x + 0.5f, 0.f, gs.cursor_y + 0.5f}, {0.f, 1.f, 0.f});
    gs.grid_x = glm::round(gs.cursor_x);
    gs.grid_y = glm::round(gs.cursor_y);
    bool is_blocked = !gs.grid.is_passable({gs.grid_x, gs.grid_y});
    gs.cursor_entity->position.x = gs.grid_x + 0.5f;
    gs.cursor_entity->position.y = (is_blocked) ? 1.1f : 0.1f;
    gs.cursor_entity->position.z = gs.grid_y + 0.5f;
    gs.cursor_material->diffuse_color = (is_blocked) 
        ? glm::vec3{1.f, 0.f, 0.f}
        : glm::vec3{0.f, 1.f, 0.f};
    gs.camera->update_view();
    gs.cursor_entity->need_world_update();
    gs.path_geometry->type = GL_LINE_STRIP;
    gs.path_geometry->positions.push_back(gs.cursor_entity->position);
    gs.path_geometry->indices.push_back(gs.path_geometry->indices.size());
    gs.path_geometry->upload();
}


int hash_location(int x, int y)
{
    return y * gs.grid.get_width() + x;
}


void toggle_block(Scene* scene)
{
    if (!gs.grid.check_bound({gs.grid_x, gs.grid_y})) return;
    SceneEntity* block = nullptr;
    int location_id = hash_location(gs.grid_x, gs.grid_y);
    if ((block = gs.block_map[location_id])) {
        scene->destroy_entity(block);
        gs.block_map[location_id] = nullptr;
        gs.grid.set_passable({gs.grid_x, gs.grid_y}, true);
    } else {
        block = scene->create_entity();
        block->mesh = gs.obstacle_mesh;
        block->position = {gs.grid_x + 0.5f, 0.5f, gs.grid_y + 0.5f};
        scene->get_root()->add_child(block);
        gs.block_map[location_id] = block;
        gs.grid.set_passable({gs.grid_x, gs.grid_y}, false);
    }
    update_cursor();
}


void find_path(int from_x, int from_y, int to_x, int to_y)
{
}


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

    gs.path_geometry = geometry_manager.create_geometry();
    gs.prev_geometry = geometry_manager.create_geometry();

    geometry_generator.generate_plane(1.f, plane);
    plane->upload();

    geometry_generator.generate_cube(0.5f, cube);
    cube->upload();

    geometry_generator.generate_cylinder(2.f, 0.5f, 32, cylinder);
    cylinder->upload();

    Material* path_material = material_manager.create_material();
    Material* prev_material = material_manager.create_material();
    Material* ground_material = material_manager.create_material();
    gs.cursor_material = material_manager.create_material();
    Material* obstacle_material = material_manager.create_material();

    path_material->ambient_color = {0.0f, 1.0f, 1.0f};
    prev_material->ambient_color = {1.0f, 1.0f, 0.0f};
    ground_material->diffuse_color = {0.8f, 0.8f, 0.8f};
    gs.cursor_material->diffuse_color = {0.0f, 1.f, 0.0f};
    obstacle_material->diffuse_color = {1.0f, 1.f, 1.0f};

    Mesh* graph_debug_mesh = mesh_manager.create_mesh();
    graph_debug_mesh->add_submesh(gs.path_geometry, path_material, shader);
    graph_debug_mesh->add_submesh(gs.prev_geometry, prev_material, shader);
    gs.path_geometry->upload();
    gs.prev_geometry->upload();

    Mesh* ground_mesh = mesh_manager.create_mesh();
    ground_mesh->add_submesh(plane, ground_material, shader);

    Mesh* cursor_mesh = mesh_manager.create_mesh();
    cursor_mesh->add_submesh(cylinder, gs.cursor_material, shader);

    gs.obstacle_mesh = mesh_manager.create_mesh();
    gs.obstacle_mesh->add_submesh(cube, obstacle_material, shader);

    SceneEntity* debug_entity = scene.create_entity();
    debug_entity->mesh = graph_debug_mesh;
    scene.get_root()->add_child(debug_entity);

    SceneEntity* ground_entity = scene.create_entity();
    ground_entity->mesh = ground_mesh;
    ground_entity->position = {32.f, 0.f, 32.f};
    ground_entity->scale = {32.f, 0.f, 32.f};

    gs.cursor_entity = scene.create_entity();
    gs.cursor_entity->mesh = cursor_mesh;
    gs.cursor_entity->scale = glm::vec3{0.55f, 0.2f, 0.55f};

    scene.get_root()->add_child(ground_entity);
    scene.get_root()->add_child(gs.cursor_entity);

    gs.grid.create(64, 64);
    gs.cursor_x = 32.f;
    gs.cursor_y = 32.f;

    gs.camera = scene.create_camera();
    float aspect = 800.f / 600.f;
    gs.camera->projection_matrix = glm::perspective(1.f, aspect, 0.1f, 1000.f);

    update_cursor();
    
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
    gs.cursor_x += event.dx * camera_speed;
    gs.cursor_y += event.dy * camera_speed;
    update_cursor();
    // Calculate where vision is pointing at
}


void App::handle(const MouseButtonInputEvent& event) 
{
    if (event.button == 0 && event.action == GLFW_RELEASE) {
        toggle_block(&scene);
    }
}


void App::handle(const MouseScrollInputEvent& event)
{
    float camera_speed = 0.02f;
    gs.magnify -= camera_speed * event.scroll_y;
    if (gs.magnify < 0.2f) gs.magnify = 0.2f;
    if (gs.magnify > 5.f) gs.magnify = 5.f;
    update_cursor();
}


}
