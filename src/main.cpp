#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "app.hpp"
#include "error.hpp"
#include "event_listener.hpp"
#include "input.hpp"
#include "input_queue.hpp"
#include "window.hpp"


class ViewUpdater : public dragonslave::EventListener<dragonslave::WindowResizeEvent>
{
public:
    ViewUpdater(glm::mat4& projection)
      : dragonslave::EventListener<dragonslave::WindowResizeEvent> ()
      , projection_ (projection)
    { }

    void handle(const dragonslave::WindowResizeEvent& ev)
    {
        std::cout << "Resize view to " << ev.width << ", " << ev.height << std::endl;
        float aspect = static_cast<float>(ev.width) / ev.height;
        projection_ = glm::perspective(1.0f, aspect, 0.1f, 1000.f);
        glViewport(0, 0, ev.width, ev.height);
    }

private:
    glm::mat4& projection_;
};


int main(int argc, char** argv) 
{
    try {
        dragonslave::App app;
        dragonslave::AppConfig app_config;
        app_config.title = "Lina is a cute";
        app_config.resizable = true;
        app.initiate(app_config);

        glm::mat4 projection;
        glm::mat4 view = glm::lookAt(
            glm::vec3 {0.f, -10.f, 0.f},
            glm::vec3 {0.f, 0.f, 0.f},
            glm::vec3 {0.f, 0.f, 1.f});

        ViewUpdater vu (projection);

        app.window.get_resize_target().add_event_listener(&vu);

        dragonslave::Model& lina_model = app.asset.model.load_named_model("Lina", "assets/models/Lina/lina.dae");

        GLuint program;
        try {
            program = app.graphics.load_program({
                app.graphics.load_shader(GL_VERTEX_SHADER, "shaders/basic/vert.glsl"),
                app.graphics.load_shader(GL_FRAGMENT_SHADER, "shaders/basic/frag.glsl")
            });
        } catch (const dragonslave::ShaderCompileError& ev) {
            std::cout << ev.log << std::endl;
            throw ev;
        } catch (const dragonslave::ProgramLinkError& ev) {
            std::cout << ev.log << std::endl;
            throw ev;
        }

        GLint world_view_loc = glGetUniformLocation(program, "world_view");
        GLint inverse_transpose_world_view_loc = 
            glGetUniformLocation(program, "inverse_transpose_world_view");
        GLint world_view_projection_loc = 
            glGetUniformLocation(program, "world_view_projection");
        GLint material_has_diffuse_map_loc = glGetUniformLocation(program, "material.has_diffuse_map");
        GLint material_diffuse_color_loc = glGetUniformLocation(program, "material.diffuse_color");
        GLint material_diffuse_map_loc = glGetUniformLocation(program, "material.diffuse_map");

        glEnable(GL_DEPTH_TEST);

        bool is_running = true;
        dragonslave::InputQueue& input_queue = app.input.get_queue();
        while (is_running) {
            while (int error = glGetError()) { std::cout << "GL error " << error << std::endl; }
            app.poll();
            while (input_queue.has_events()) {
                const dragonslave::InputEvent* ev = input_queue.next_event(); 
                if (ev->type == dragonslave::InputEventType::KEYBOARD) {
                    const dragonslave::KeyboardInputEvent* kev =
                        static_cast<const dragonslave::KeyboardInputEvent*>(ev);
                    if (kev->action == GLFW_PRESS &&
                            kev->key == GLFW_KEY_ESCAPE) {
                        is_running = false;
                    }
                }
                input_queue.pop_event();
            }

            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            glm::mat4 world_view = view;
            glm::mat4 inverse_transpose_world_view = glm::transpose(glm::inverse(view));
            glm::mat4 world_view_projection = projection * view;

            glUseProgram(program);
            glUniformMatrix4fv(world_view_loc, 1, GL_FALSE,  glm::value_ptr(world_view));
            glUniformMatrix4fv(
                inverse_transpose_world_view_loc, 1, GL_FALSE,
                glm::value_ptr(inverse_transpose_world_view));
            glUniformMatrix4fv(
                world_view_projection_loc, 1, GL_FALSE,
                glm::value_ptr(world_view_projection));

            int mesh_idx = 0;
            for (const dragonslave::Mesh& mesh : lina_model.meshes) {
                glUniform1i(material_has_diffuse_map_loc, mesh.material->has_diffuse_map);
                glUniform3fv(material_diffuse_color_loc, 1, glm::value_ptr(mesh.material->diffuse_color));
                if (mesh.material->has_diffuse_map) {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, mesh.material->diffuse_map);
                    glUniform1i(material_diffuse_map_loc, 0);
                }
                glBindVertexArray(mesh.geode->vao);
                glDrawElements(GL_TRIANGLES, mesh.geode->indices.size(), GL_UNSIGNED_INT, 0);
            }

            app.window.swap_buffers();
        }

        app.terminate();

    } catch (const dragonslave::FatalError& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
