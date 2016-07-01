#include "scene_renderer.hpp"

namespace dragonslave {


SceneRenderer::SceneRenderer() { }


SceneRenderer::~SceneRenderer() { }


void SceneRenderer::initialize(GraphicsContext* gc)
{
    gc_ = gc;
}


void SceneRenderer::terminate()
{
    gc_ = nullptr;
}


void SceneRenderer::set_scene(Scene* scene)
{
    scene_ = scene;
}


void SceneRenderer::set_active_camera(SceneCamera* camera)
{
    active_camera_ = camera;
}


void SceneRenderer::set_viewport(int width, int height)
{
    // TODO(eugene): Make draw buffers for multi-pass rendering
}


void SceneRenderer::render()
{
    SceneCullVisitor visitor (active_camera_);
    scene_->traverse(&visitor);

    // TODO(eugene): Add state sorting and state-aware rendering
    Shader* prev_shader = nullptr;
    for (SceneEntity* entity : visitor.get_visible_entities()) {
        for (Submesh& submesh : entity->mesh->get_submeshes()) {
            if (prev_shader != submesh.shader) {
                submesh.shader->use();
                submesh.shader->set_view_projection(
                    active_camera_->view_matrix,
                    active_camera_->projection_matrix);
                prev_shader = submesh.shader;
            }
            submesh.shader->set_material(submesh.material);
            submesh.geometry->bind();
            submesh.shader->draw(
                entity->model_matrix,
                submesh.geometry);
        }
    }
}


}
