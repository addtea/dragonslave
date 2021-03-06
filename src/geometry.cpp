#include "geometry.hpp"

namespace dragonslave {


Geometry::Geometry() { }


Geometry::~Geometry() { }


void Geometry::create(GraphicsContext* gc)
{
    gc_ = gc;
    vao_ = gc_->create_vertex_array();
    vbo_positions_ = gc_->create_buffer();
    vbo_normals_ = gc_->create_buffer();
    vbo_tex_coords_ = gc_->create_buffer();
    ebo_ = gc_->create_buffer();

    type = GL_TRIANGLES;
}


void Geometry::destroy()
{
    if (vao_) gc_->destroy_vertex_array(vao_);
    if (vbo_positions_) gc_->destroy_buffer(vbo_positions_);
    if (vbo_normals_) gc_->destroy_buffer(vbo_normals_);
    if (vbo_tex_coords_) gc_->destroy_buffer(vbo_tex_coords_);
    if (ebo_) gc_->destroy_buffer(ebo_);

    positions.clear();
    normals.clear();
    tex_coords.clear();
    indices.clear();
}


void Geometry::upload()
{
    glBindVertexArray(vao_);

    // Positions
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_positions_);
    glBufferData(
        GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3),
        positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Normals
    if (has_normals) {
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_normals_);
        glBufferData(
            GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3),
            normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
    }

    // Tex coords
    if (has_tex_coords) {
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_tex_coords_);
        glBufferData(
            GL_ARRAY_BUFFER, tex_coords.size() * sizeof(glm::vec2),
            tex_coords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    // Elements
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        indices.data(), GL_STATIC_DRAW);
    count_ = indices.size();

    glBindVertexArray(0u);
    glBindBuffer(GL_ARRAY_BUFFER, 0u);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
}


void Geometry::bind()
{
    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
}


void Geometry::stream() 
{
    glDrawElements(type, count_, GL_UNSIGNED_INT, 0);
}


void Geometry::stream_instances(int num_instances)
{
    glDrawElementsInstanced(type, count_, GL_UNSIGNED_INT, 0, num_instances);
}


}
