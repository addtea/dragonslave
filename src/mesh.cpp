#include "mesh.hpp"

namespace dragonslave {


Mesh::Mesh() { }


Mesh::~Mesh() { }


void Mesh::upload(Graphics& graphics)
{
    vao = graphics.create_vertex_array();
    vbo_positions = graphics.create_buffer();
    vbo_normals = graphics.create_buffer();
    vbo_tex_coords = graphics.create_buffer();
    ebo = graphics.create_buffer();

    glBindVertexArray(vao);

    // Positions
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_positions);
    glBufferData(
        GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3),
        positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Normals
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glBufferData(
        GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3),
        normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Tex coords
    glBindBuffer(GL_ARRAY_BUFFER, vbo_tex_coords);
    glBufferData(
        GL_ARRAY_BUFFER, tex_coords.size() * sizeof(glm::vec2),
        tex_coords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    // Elements
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0u);
    glBindBuffer(GL_ARRAY_BUFFER, 0u);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
}


}
