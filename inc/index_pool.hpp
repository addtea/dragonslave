#pragma once

#include <vector>

namespace dragonslave {


class IndexPool 
{
public:
    IndexPool();
    virtual ~IndexPool();

    void create(int capacity);
    void destroy();

    int get_capacity() const { return capacity_; }

    int request_index();
    void free_index(int index);
    void clear();

private:
    int capacity_ = 0;
    int max_depth_ = 0;
    std::vector<uint32_t> lookup_;
};


}
