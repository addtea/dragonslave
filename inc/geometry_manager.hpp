#pragma once

#include <list>
#include "graphics_context.hpp"
#include "geometry.hpp"

namespace dragonslave {


class GeometryManager
{
public:
    GeometryManager();
    virtual ~GeometryManager();

    void initialize(GraphicsContext* gc);
    void terminate();

    Geometry* create_geometry();
    void destroy_geometry(Geometry* geometry);

private:
    GraphicsContext* gc_;
    std::list<Geometry> geometries_;
};

    
}
