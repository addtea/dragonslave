#pragma once

#include <list>
#include <unordered_map>

#include "geode.hpp"

namespace dragonslave {


class GeodeManager 
{
public:
    GeodeManager();
    ~GeodeManager();

    Geode& create_geode();
    Geode& create_named_geode(const std::string& name);

    Geode* get_geode(const std::string& name);

private:    
    std::unordered_map<
            std::string,
            std::list<Geode>::iterator>
        geode_lookup_;
    std::list<Geode> geodes_;

    std::list<Geode>::iterator create_geode_it_();
};


}
