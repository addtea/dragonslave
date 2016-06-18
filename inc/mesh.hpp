#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "graphics.hpp"

namespace dragonslave {


class Mesh
{
public:
    std::vector<glm::vec3> positions;

    bool has_normals = false;
    bool has_tex_coords = false;
    bool has_skeleton = false;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tex_coords;
    std::vector<glm::imat4> bone_ids;
    std::vector<glm::mat4> bone_weights;

    Mesh(Graphics& graphics);
    virtual ~Mesh();

    void upload();

private:
    Graphics& graphics_;
};


}
