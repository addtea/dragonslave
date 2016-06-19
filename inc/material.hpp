#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace dragonslave {

// Placeholder
// TODO: Implement an actual Material struct
struct Material {
    glm::vec3 ambient, diffuse, specular;
    GLfloat shininess;
}

}
