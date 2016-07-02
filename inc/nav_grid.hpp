#include <vector>

namespace dragonslave {


struct NavGridLocation
{
    int x;
    int y;
};


class NavGrid
{
public:
    NavGrid();
    virtual ~NavGrid();

    void create(int width, int height);
    void destroy();

    int get_width() { return width_; }
    int get_height() { return height_; }
    bool check_bound(NavGridLocation location);
    std::vector<NavGridLocation> get_adjacent(NavGridLocation location);
    bool is_passable(NavGridLocation location);
    void set_passable(NavGridLocation location, bool is_passable);

private:
    int width_ = 0;
    int height_ = 0;
    std::vector<bool> is_passable_grid_;
};


}
