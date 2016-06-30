#include <glm/gtc/type_ptr.hpp>
#include "error.hpp"
#include "shaders/basic_shader.hpp"

namespace dragonslave {


BasicShader::BasicShader() { }


BasicShader::~BasicShader() { }


void BasicShader::use() 
{
    glUseProgram(program_);
}


void BasicShader::set_view_projection(
        const glm::mat4& view,
        const glm::mat4& projection)
{
    view_matrix_ = view;
    projection_matrix_ = projection;
}


void BasicShader::set_material(Material* material)
{
    material_ = material;
    glUniform1i(material_has_ambient_map_location_, material->has_ambient_map);
    glUniform1i(material_has_diffuse_map_location_, material->has_diffuse_map);
    glUniform1i(material_has_specular_map_location_, material->has_specular_map);
    if (!material->has_ambient_map)
        glUniform3fv(material_ambient_color_location_, 1, glm::value_ptr(material->ambient_color));
    if (!material->has_diffuse_map)
        glUniform3fv(material_diffuse_color_location_, 1, glm::value_ptr(material->diffuse_color));
    if (!material->has_specular_map)
        glUniform3fv(material_specular_color_location_, 1, glm::value_ptr(material->specular_color));
    glUniform1f(material_shininess_location_, material->shininess);
    int tex_id = 0;
    if (material->has_ambient_map) {
        glActiveTexture(GL_TEXTURE0 + tex_id);
        glBindTexture(GL_TEXTURE_2D, material->ambient_map);
        glUniform1i(material_ambient_map_location_, tex_id++);
    }
    if (material->has_diffuse_map) {
        glActiveTexture(GL_TEXTURE0 + tex_id);
        glBindTexture(GL_TEXTURE_2D, material->diffuse_map);
        glUniform1i(material_diffuse_map_location_, tex_id++);
    }
    if (material->has_specular_map) {
        glActiveTexture(GL_TEXTURE0 + tex_id);
        glBindTexture(GL_TEXTURE_2D, material->specular_map);
        glUniform1i(material_specular_map_location_, tex_id++);
    }
}


void BasicShader::set_skeleton(Skeleton* skeleton)
{
    throw FatalError("NotImplementedError", "Function is not implemented");
}


void BasicShader::draw(const glm::mat4& model_matrix, Geometry* geometry)
{
    glm::mat4 model_view = view_matrix_ * model_matrix;
    glm::mat4 inverse_tranpose_model_view = glm::transpose(glm::inverse(model_view));
    glm::mat4 model_view_projection = projection_matrix_ * model_view;

    glUniformMatrix4fv(model_view_location_, 1, GL_FALSE, glm::value_ptr(model_view));
    glUniformMatrix4fv(inverse_transpose_model_view_location_, 1, GL_FALSE, glm::value_ptr(inverse_tranpose_model_view));
    glUniformMatrix4fv(model_view_projection_location_, 1, GL_FALSE, glm::value_ptr(model_view_projection));

    geometry->stream();
} 


void BasicShader::draw_instances(
        std::vector<glm::mat4> model_matrices,
        Geometry* geometry)
{
    throw FatalError("NotImplementedError", "Function is not implemented");
}


void BasicShader::on_setup(GraphicsContext* gc) 
{
    vertex_ = gc->load_shader(GL_VERTEX_SHADER, "shaders/basic/vert.glsl");
    fragment_ = gc->load_shader(GL_FRAGMENT_SHADER, "shaders/basic/frag.glsl");
    program_ = gc->load_program({vertex_, fragment_});

    model_view_location_ = glGetUniformLocation(program_, "model_view");
    inverse_transpose_model_view_location_ = glGetUniformLocation(program_, "inverse_transpose_model_view");
    model_view_projection_location_ = glGetUniformLocation(program_, "model_view_projection");
    material_has_ambient_map_location_ = glGetUniformLocation(program_, "material.has_ambient_map");
    material_has_diffuse_map_location_ = glGetUniformLocation(program_, "material.has_diffuse_map");
    material_has_specular_map_location_ = glGetUniformLocation(program_, "material.has_specular_map");
    material_ambient_color_location_ = glGetUniformLocation(program_, "material.ambient_color");
    material_diffuse_color_location_ = glGetUniformLocation(program_, "material.diffuse_color");
    material_specular_color_location_ = glGetUniformLocation(program_, "material.specular_color");
    material_shininess_location_ = glGetUniformLocation(program_, "material.shininess");
    material_ambient_map_location_ = glGetUniformLocation(program_, "material.ambient_map");
    material_diffuse_map_location_ = glGetUniformLocation(program_, "material.diffuse_map");
    material_specular_map_location_ = glGetUniformLocation(program_, "material.specular_map");
}


void BasicShader::on_cleanup(GraphicsContext* gc)
{
    gc->destroy_shader(vertex_);
    gc->destroy_shader(fragment_);
    gc->destroy_program(program_);
}


}
