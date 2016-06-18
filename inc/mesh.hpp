#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_integer.hpp>

#include "graphics.hpp"

namespace dragonslave {


class Mesh
{
public:

    bool has_positions = false;
    bool has_normals = false;
    bool has_tex_coords = false;
    bool has_skeleton = false;
    bool has_indices = false;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> tex_coords;
    std::vector<glm::imat4> bone_ids;
    std::vector<glm::mat4> bone_weights;
    std::vector<GLuint> indices;

    GLuint VAO_positions, VBO_positions;
    GLuint VAO_normals, VBO_normals;
    GLuint VAO_texcoords, VBO_texcoords;

    Mesh(Graphics& graphics)
    : graphics_(graphics)
    { }
    virtual ~Mesh() { };

    void upload();

private:
    Graphics& graphics_;

};


}
