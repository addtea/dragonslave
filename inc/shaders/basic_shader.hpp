#pragma once

#include "shader.hpp"

namespace dragonslave {


class BasicShader : public Shader
{
public:
    BasicShader();
    virtual ~BasicShader();

    void setup(GraphicsContext* gc) override;
    void cleanup(GraphicsContext* gc) override;

    void use() override;
    void set_view_projection(
        const glm::mat4& view,
        const glm::mat4& projection) override;
    void set_material(Material* material) override;
    void set_skeleton(Skeleton* skeleton) override;
    void draw(const glm::mat4& model_matrix, Geometry* geometry) override;
    void draw_instances(
        std::vector<glm::mat4> model_matrices,
        Geometry* geometry) override;

private:
    glm::mat4 view_matrix_;
    glm::mat4 projection_matrix_;
    Material* material_ = nullptr;

    GLuint program_;
    GLuint vertex_;
    GLuint fragment_;
    GLint model_view_location_;
    GLint inverse_transpose_model_view_location_;
    GLint model_view_projection_location_;
    GLint material_has_ambient_map_location_;
    GLint material_has_diffuse_map_location_;
    GLint material_has_specular_map_location_;
    GLint material_ambient_color_location_;
    GLint material_diffuse_color_location_;
    GLint material_specular_color_location_;
    GLint material_shininess_location_;
    GLint material_ambient_map_location_;
    GLint material_diffuse_map_location_;
    GLint material_specular_map_location_;
};


}
