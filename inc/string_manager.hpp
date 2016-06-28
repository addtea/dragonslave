#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include "string_hash.hpp"

namespace dragonslave {


using StringId = uint32_t;


class StringManager
{
public:
    StringManager();
    virtual ~StringManager();

    void init(StringHashFunc* hash_func);
    void destroy();

    StringId intern(const std::string& s);
    std::string lookup(StringId s_id) const;

private:
    StringHashFunc* hash_func_ = nullptr;
    std::unordered_map<StringId, std::string> lookup_map_;
};


}
