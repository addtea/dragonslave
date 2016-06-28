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
    active_camera_->update_view();

    SceneCullVisitor visitor (active_camera_);
    scene_->traverse(&visitor);

    // TODO(eugene): Add state sorting and state-aware rendering
    for (SceneEntity* entity : visitor.get_visible_entities()) {
        for (Mesh& mesh : entity->model->get_meshes()) {
            mesh.shader->activate();
            mesh.shader->set_view_projection(
                active_camera_->view_matrix,
                active_camera_->projection_matrix);
            mesh.shader->set_material(mesh.material);
            mesh.shader->draw(
                entity->model_matrix,
                mesh.geometry);
        }
    }
}


}
