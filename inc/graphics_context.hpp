#pragma once

#include <GL/glew.h>
#include "window.hpp"

namespace dragonslave {


class GraphicsContext
{
public:
    GraphicsContext();
    virtual ~GraphicsContext();

    void initialize(Window* window);
    void terminate();

    GLuint create_buffer();
    GLuint create_program();
    GLuint create_shader(GLenum type);
    GLuint create_texture(); 
    GLuint create_vertex_array();
    GLuint load_program(const std::vector<GLuint>& shaders);
    GLuint load_shader(GLenum type, const std::string& path);
    void destroy_buffer(GLuint buffer);
    void destroy_program(GLuint program);
    void destroy_shader(GLuint shader);
    void destroy_texture(GLuint texture);
    void destroy_vertex_array(GLuint vertex_array);

private:
    std::vector<GLuint> buffers_;
    std::vector<GLuint> programs_;
    std::vector<GLuint> shaders_;
    std::vector<GLuint> textures_;
    std::vector<GLuint> vertex_arrays_;
};


}
