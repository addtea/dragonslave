#include <algorithm>
#include <cmath>
#include <iostream>
#include "bit_utils.hpp"
#include "index_pool.hpp"

namespace dragonslave {


IndexPool::IndexPool() { }


IndexPool::~IndexPool() { }


void IndexPool::create(int capacity)
{
    capacity_ = capacity;
    max_depth_ = ceil(log(capacity_) / log(32));
    int tree_size_ = (pow(32, max_depth_) - 1) / 31 + (capacity / 32);
    lookup_.resize(tree_size_);
}


void IndexPool::destroy() 
{
    clear();
}


int IndexPool::request_index()
{
    int depth = 0;
    int base  = 0;
    int width = 1;

    int cursor = 0;

    while (depth < max_depth_) {
        int offset = bit_utils::index_of_first_set_bit(lookup_[base + cursor]);
        if (offset < 0) {
            return -1;
        }
        cursor = 32 * cursor + offset;
        base += width;
        width *= 32;
        depth++;
    }

    if (cursor >= capacity_)
        return -1;

    int index = cursor;

    do {
        depth--;
        width /= 32;
        base -= width; 
        int offset = cursor % 32;
        cursor /= 32;
        lookup_[base + cursor] &= ~(1 << offset);
    } while (depth >= 0 && bit_utils::index_of_first_set_bit(lookup_[base + cursor]) < 0);

    return index;
}


void IndexPool::free_index(int index)
{
    int cursor = index;
    int depth = max_depth_;
    int width = pow(32, max_depth_);
    int base = int(width - 1) / 31;

    do {
        depth--;
        width /= 32;
        base -= width; 
        int offset = cursor % 32;
        cursor /= 32;
        lookup_[base + cursor] |= 1 << offset;
    } while (depth > 0);
}


void IndexPool::clear()
{
    std::fill(lookup_.begin(), lookup_.end(), 0xFFFFFFFF);
}


}
