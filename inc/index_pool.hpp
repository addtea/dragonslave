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

    void clear();
    int request_index();
    void free_index(int index);

private:
    int capacity_ = 0;
    std::vector<uint32_t> lookup_;
    int max_depth_;
};


}
