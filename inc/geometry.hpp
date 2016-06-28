#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_integer.hpp>
#include "graphics_context.hpp"

namespace dragonslave {


class Geometry
{
public:
    bool has_normals = false;
    bool has_tex_coords = false;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> tex_coords;
    std::vector<GLuint> indices;
    GLenum type = GL_TRIANGLES;

    Geometry();
    virtual ~Geometry();

    void create(GraphicsContext* gc);
    void destroy();

    void upload();
    void bind();
    void stream();
    void stream_instances(int num_instances);

private:
    GraphicsContext* gc_ = nullptr;

    GLuint vao_ = 0u;
    GLuint vbo_positions_  = 0u;
    GLuint vbo_normals_    = 0u;
    GLuint vbo_tex_coords_ = 0u;
    GLuint ebo_ = 0u;
    GLsizei count_ = 0;
};


}
