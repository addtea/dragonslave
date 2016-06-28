#pragma once

#include <cstdint>
#include <string>

namespace dragonslave {


class StringHashFunc
{
public:
    virtual ~StringHashFunc() { }

    virtual uint32_t hash(const std::string& s) = 0;
};


class CRC32HashFunc : public StringHashFunc
{
public:
    uint32_t hash(const std::string& s) override;
};


}
