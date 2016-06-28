#pragma once

#include <glm/glm.hpp>
#include "geometry.hpp"
#include "graphics_context.hpp"
#include "material.hpp"
#include "skeleton.hpp"

namespace dragonslave {


class Shader
{
public:
    virtual ~Shader() { }

    void create(GraphicsContext* gc);
    void destroy();

    virtual void activate() = 0;
    virtual void set_view_projection(
        const glm::mat4& view,
        const glm::mat4& projection) = 0;
    virtual void set_material(Material* material) = 0;
    virtual void set_skeleton(Skeleton* skeleton) = 0;
    virtual void draw(const glm::mat4& model_matrix, Geometry* geometry) = 0;
    virtual void draw_instances(
        std::vector<glm::mat4> model_matrices,
        Geometry* geometry) = 0;

protected:
    virtual void on_setup(GraphicsContext* gc) = 0;
    virtual void on_cleanup(GraphicsContext* gc) = 0;

private:
    GraphicsContext* gc_ = nullptr;
};


}
