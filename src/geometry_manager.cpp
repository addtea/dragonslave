#include <algorithm>
#include "geometry_manager.hpp"

namespace dragonslave {


GeometryManager::GeometryManager() { }


GeometryManager::~GeometryManager() { }


void GeometryManager::initialize(GraphicsContext* gc) 
{ 
    gc_ = gc;
}


void GeometryManager::terminate()
{
    for (Geometry& geometry : geometries_) {
        geometry.destroy();
    }
    geometries_.clear();
    gc_ = nullptr;
}


Geometry* GeometryManager::create_geometry()
{
    geometries_.emplace_back();
    Geometry& geometry = geometries_.back();
    geometry.create(gc_);
    return &geometry;
}


void GeometryManager::destroy_geometry(Geometry* geometry)
{
    geometry->destroy();
    std::remove_if(
        geometries_.begin(),
        geometries_.end(),
        [=](Geometry& stored_geometry) {
            return &stored_geometry == geometry;
        });
}


}
