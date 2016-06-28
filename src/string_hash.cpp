#include "bit_utils.hpp"
#include "string_hash.hpp"

namespace dragonslave {


uint32_t CRC32HashFunc::hash(const std::string& s)
{
    uint32_t bytes, crc, mask;
    crc = 0xFFFFFFFF;
    for (char c : s) {
        bytes = bit_utils::reverse_bits(static_cast<uint32_t>(c));
        crc ^= bytes;
        for (int i = 0; i < 8 ; i++) {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
    }
    return ~crc;
}


}
