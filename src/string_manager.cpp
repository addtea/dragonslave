#include "string_manager.hpp"

namespace dragonslave {

StringManager::StringManager() { }


StringManager::~StringManager() { }


void StringManager::init(StringHashFunc* hash_func)
{
    hash_func_ = hash_func;
}


void StringManager::destroy()
{
    hash_func_ = nullptr;
    lookup_map_.clear();
}


std::string StringManager::lookup(StringId s_id) const
{
    return lookup_map_.at(s_id);
}

StringId StringManager::intern(const std::string& s)
{
    StringId s_id = hash_func_->hash(s);
    if (lookup_map_.find(s_id) == lookup_map_.end()) {
        lookup_map_[s_id] = s;
    }
    return s_id;
}


}
