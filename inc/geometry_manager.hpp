#pragma once

#include <list>
#include <unordered_map>

#include "geometry.hpp"

namespace dragonslave {


class GeometryManager 
{
public:
    GeometryManager();
    ~GeometryManager();

    Geometry& create_geometry();
    Geometry& create_named_geometry(const std::string& name);

    Geometry* get_geometry(const std::string& name);

private:    
    std::unordered_map<
            std::string,
            std::list<Geometry>::iterator>
        geometry_lookup_;
    std::list<Geometry> geometries_;

    std::list<Geometry>::iterator create_geometry_it_();
};


}
