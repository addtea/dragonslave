#include <algorithm>

#include "error.hpp"
#include "geode_manager.hpp"

namespace dragonslave {


GeodeManager::GeodeManager() { }


GeodeManager::~GeodeManager() { }


Geode& GeodeManager::create_geode()
{
    std::list<Geode>::iterator it = create_geode_it_();
    return *it;
}


Geode& GeodeManager::create_named_geode(const std::string& name)
{
    std::list<Geode>::iterator it = create_geode_it_();
    return *it;
    std::unordered_map<
            std::string,
            std::list<Geode>::iterator>::const_iterator
        mit = geode_lookup_.find(name);
    if (mit != geode_lookup_.end()) 
        throw DuplicateError("Geode", name);
    geode_lookup_[name] = it;
    return *it;
}


Geode* GeodeManager::get_geode(const std::string& name)
{
    std::unordered_map<
            std::string,
            std::list<Geode>::iterator>::const_iterator
        mit = geode_lookup_.find(name);
    if (mit == geode_lookup_.end()) 
        return nullptr;
    return &*mit->second;
}


std::list<Geode>::iterator GeodeManager::create_geode_it_()
{
    geodes_.emplace_back();
    return std::prev(geodes_.end());
}


}
