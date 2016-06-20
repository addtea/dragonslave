#include <algorithm>

#include "error.hpp"
#include "geometry_manager.hpp"

namespace dragonslave {


GeometryManager::GeometryManager() { }


GeometryManager::~GeometryManager() { }


Geometry& GeometryManager::create_geometry()
{
    std::list<Geometry>::iterator it = create_geometry_it_();
    return *it;
}


Geometry& GeometryManager::create_named_geometry(const std::string& name)
{
    std::list<Geometry>::iterator it = create_geometry_it_();
    return *it;
    std::unordered_map<
            std::string,
            std::list<Geometry>::iterator>::const_iterator
        mit = geometry_lookup_.find(name);
    if (mit != geometry_lookup_.end()) 
        throw DuplicateError("Geometry", name);
    geometry_lookup_[name] = it;
    return *it;
}


Geometry* GeometryManager::get_geometry(const std::string& name)
{
    std::unordered_map<
            std::string,
            std::list<Geometry>::iterator>::const_iterator
        mit = geometry_lookup_.find(name);
    if (mit == geometry_lookup_.end()) 
        return nullptr;
    return &*mit->second;
}


std::list<Geometry>::iterator GeometryManager::create_geometry_it_()
{
    geometries_.emplace_back();
    return std::prev(geometries_.end());
}


}
