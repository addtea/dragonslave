#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace dragonslave {


struct Material 
{
    bool has_ambient_map = false;
    bool has_diffuse_map = false;
    bool has_specular_map = false;

    glm::vec3 ambient_color {0.f, 0.f, 0.f};
    glm::vec3 diffuse_color {1.f, 1.f, 1.f};
    glm::vec3 specular_color {0.f, 0.f, 0.f};
    float shininess;

    GLuint ambient_map = 0u;
    GLuint diffuse_map = 0u;
    GLuint specular_map = 0u;
};


}
