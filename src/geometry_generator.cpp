#include <vector>
#include <queue>
#include <glm/gtc/constants.hpp>
#include "geometry_generator.hpp"

namespace dragonslave {


GeometryGenerator::GeometryGenerator() { }


GeometryGenerator::~GeometryGenerator() { }


void GeometryGenerator::generate_cube(float radius, Geometry* geometry)
{
    float scale = radius / glm::sqrt(3);
    glm::vec3 v0 {-scale, scale, scale};
    glm::vec3 v1 { scale, scale, scale};
    glm::vec3 v2 { scale, scale,-scale};
    glm::vec3 v3 {-scale, scale,-scale};
    glm::vec3 v4 {-scale,-scale, scale};
    glm::vec3 v5 { scale,-scale, scale};
    glm::vec3 v6 { scale,-scale,-scale};
    glm::vec3 v7 {-scale,-scale,-scale};

    geometry->has_normals = true;
    geometry->has_tex_coords = false;
    geometry->positions.clear();
    geometry->normals.clear();

    geometry->positions.push_back(v0);
    geometry->normals.push_back({0.f, 1.f, 0.f});
    geometry->positions.push_back(v1);
    geometry->normals.push_back({0.f, 1.f, 0.f});
    geometry->positions.push_back(v2);
    geometry->normals.push_back({0.f, 1.f, 0.f});
    geometry->positions.push_back(v3);
    geometry->normals.push_back({0.f, 1.f, 0.f});

    geometry->positions.push_back(v4);
    geometry->normals.push_back({0.f, 0.f, 1.f});
    geometry->positions.push_back(v5);
    geometry->normals.push_back({0.f, 0.f, 1.f});
    geometry->positions.push_back(v1);
    geometry->normals.push_back({0.f, 0.f, 1.f});
    geometry->positions.push_back(v0);
    geometry->normals.push_back({0.f, 0.f, 1.f});

    geometry->positions.push_back(v5);
    geometry->normals.push_back({1.f, 0.f, 0.f});
    geometry->positions.push_back(v6);
    geometry->normals.push_back({1.f, 0.f, 0.f});
    geometry->positions.push_back(v2);
    geometry->normals.push_back({1.f, 0.f, 0.f});
    geometry->positions.push_back(v1);
    geometry->normals.push_back({1.f, 0.f, 0.f});

    geometry->positions.push_back(v6);
    geometry->normals.push_back({0.f, 0.f,-1.f});
    geometry->positions.push_back(v7);
    geometry->normals.push_back({0.f, 0.f,-1.f});
    geometry->positions.push_back(v3);
    geometry->normals.push_back({0.f, 0.f,-1.f});
    geometry->positions.push_back(v2);
    geometry->normals.push_back({0.f, 0.f,-1.f});

    geometry->positions.push_back(v7);
    geometry->normals.push_back({-1.f, 0.f, 0.f});
    geometry->positions.push_back(v4);
    geometry->normals.push_back({-1.f, 0.f, 0.f});
    geometry->positions.push_back(v0);
    geometry->normals.push_back({-1.f, 0.f, 0.f});
    geometry->positions.push_back(v3);
    geometry->normals.push_back({-1.f, 0.f, 0.f});

    geometry->positions.push_back(v7);
    geometry->normals.push_back({0.f,-1.f, 0.f});
    geometry->positions.push_back(v6);
    geometry->normals.push_back({0.f,-1.f, 0.f});
    geometry->positions.push_back(v5);
    geometry->normals.push_back({0.f,-1.f, 0.f});
    geometry->positions.push_back(v4);
    geometry->normals.push_back({0.f,-1.f, 0.f});

    geometry->indices.push_back(0);
    geometry->indices.push_back(1);
    geometry->indices.push_back(2);
    geometry->indices.push_back(0);
    geometry->indices.push_back(2);
    geometry->indices.push_back(3);

    geometry->indices.push_back(4);
    geometry->indices.push_back(5);
    geometry->indices.push_back(6);
    geometry->indices.push_back(4);
    geometry->indices.push_back(6);
    geometry->indices.push_back(7);

    geometry->indices.push_back(8);
    geometry->indices.push_back(9);
    geometry->indices.push_back(10);
    geometry->indices.push_back(8);
    geometry->indices.push_back(10);
    geometry->indices.push_back(11);

    geometry->indices.push_back(12);
    geometry->indices.push_back(13);
    geometry->indices.push_back(14);
    geometry->indices.push_back(12);
    geometry->indices.push_back(14);
    geometry->indices.push_back(15);

    geometry->indices.push_back(16);
    geometry->indices.push_back(17);
    geometry->indices.push_back(18);
    geometry->indices.push_back(16);
    geometry->indices.push_back(18);
    geometry->indices.push_back(19);

    geometry->indices.push_back(20);
    geometry->indices.push_back(21);
    geometry->indices.push_back(22);
    geometry->indices.push_back(20);
    geometry->indices.push_back(22);
    geometry->indices.push_back(23);

    geometry->type = GL_TRIANGLES;
}


void GeometryGenerator::generate_sphere(float radius, int subdivides, Geometry* geometry)
{
    int vslices = subdivides / 2 + 2;
    int hslices = subdivides;

    geometry->has_normals = true;
    geometry->has_tex_coords = false;
    geometry->positions.clear();
    geometry->normals.clear();

    for (int i = 0; i < vslices; i++) {
        float a = (glm::pi<float>() * i) / (vslices - 1);
        float y = glm::cos(a);
        float hradius = glm::sin(a);
        for (int j = 0; j < hslices; j++) {
            float b = (2 * glm::pi<float>() * j) / (hslices - 1);
            float x = hradius * glm::cos(b);
            float z = hradius * glm::sin(b);
            geometry->positions.push_back(radius * glm::vec3{x, y, z});
        }
    }

    for (const glm::vec3& position : geometry->positions) {
        geometry->normals.push_back(glm::normalize(position));
    }

    for (int i = 0; i < vslices - 1; i++) {
        for (int j = 0; j < hslices; j++) {
            int used_j = j;
            if (i % 2) used_j = hslices - j - 1;
            geometry->indices.push_back(i * hslices + used_j);
            geometry->indices.push_back((i + 1) * hslices + used_j);
        }
    }
    geometry->type = GL_TRIANGLE_STRIP;
}


void GeometryGenerator::generate_cylinder(float height, float radius, int subdivides, Geometry* geometry)
{
    int hslices = subdivides;

    geometry->has_normals = true;
    geometry->has_tex_coords = false;
    geometry->positions.clear();
    geometry->normals.clear();

    for (int j = 0; j < hslices; j++) {
        geometry->positions.push_back({0.f, height, 0.f});
        geometry->normals.push_back({0.f, 1.f, 0.f});
    }
    for (int j = 0; j < hslices; j++) {
        float a = (2 * glm::pi<float>() * j) / (hslices - 1);
        float x = glm::cos(a);
        float z = glm::sin(a);
        geometry->positions.push_back(radius * glm::vec3{x, height, z});
        geometry->normals.push_back({0.f, 1.f, 0.f});
    }
    for (int j = 0; j < hslices; j++) {
        float a = (2 * glm::pi<float>() * j) / (hslices - 1);
        float x = glm::cos(a);
        float z = glm::sin(a);
        geometry->positions.push_back(radius * glm::vec3{x, height, z});
        geometry->normals.push_back({x, 0.f, z});
    }
    for (int j = 0; j < hslices; j++) {
        float a = (2 * glm::pi<float>() * j) / (hslices - 1);
        float x = glm::cos(a);
        float z = glm::sin(a);
        geometry->positions.push_back(radius * glm::vec3{x, -height, z});
        geometry->normals.push_back({x, 0.f, z});
    }
    for (int j = 0; j < hslices; j++) {
        float a = (2 * glm::pi<float>() * j) / (hslices - 1);
        float x = glm::cos(a);
        float z = glm::sin(a);
        geometry->positions.push_back(radius * glm::vec3{x, -height, z});
        geometry->normals.push_back({0.f, -1.f, 0.f});
    }
    for (int j = 0; j < hslices; j++) {
        geometry->positions.push_back({0.f, -height, 0.f});
        geometry->normals.push_back({0.f, -1.f, 0.f});
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < hslices; j++) {
            int used_j = j;
            if (i % 2) used_j = hslices - j - 1;
            geometry->indices.push_back(i * hslices + used_j);
            geometry->indices.push_back((i + 1) * hslices + used_j);
        }
    }
    geometry->type = GL_TRIANGLE_STRIP;
}


}
