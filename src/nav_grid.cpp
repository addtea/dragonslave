#include <algorithm>
#include "nav_grid.hpp"

namespace dragonslave {


NavGrid::NavGrid() { }


NavGrid::~NavGrid() { }


void NavGrid::create(int width, int height)
{
    width_ = width;
    height_ = height;
    is_passable_grid_.resize(width_ * height_);
    std::fill(is_passable_grid_.begin(), is_passable_grid_.end(), true);
}


void NavGrid::destroy()
{
    is_passable_grid_.clear();
}


bool NavGrid::check_bound(NavGridLocation location)
{
    return 
        (0 <= location.x && location.x < width_) &&
        (0 <= location.y && location.y < height_);
}


std::vector<NavGridLocation> NavGrid::get_adjacent(NavGridLocation location)
{
    std::vector<NavGridLocation> locations;
    if (is_passable({location.x - 1, location.y}))
        locations.push_back({location.x - 1, location.y});
    if (is_passable({location.x + 1, location.y}))
        locations.push_back({location.x + 1, location.y});
    if (is_passable({location.x, location.y - 1}))
        locations.push_back({location.x, location.y - 1});
    if (is_passable({location.x, location.y + 1}))
        locations.push_back({location.x, location.y + 1});
    return locations;
}


bool NavGrid::is_passable(NavGridLocation location)
{
    return 
        check_bound(location) && 
        is_passable_grid_[location.y * width_ + location.x];
}


void NavGrid::set_passable(NavGridLocation location, bool is_passable)
{
    if (check_bound(location)) {
        is_passable_grid_[location.y * width_ + location.x] = is_passable;
    }
}


}
