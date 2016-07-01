#include <unordered_map>
#include <vector>

namespace dragonslave {


using NavLocationId = int;


struct NavEdge
{
    NavLocationId from = 0;
    NavLocationId to = 0;
    double weight = 0.;
};


class NavGraph
{
public:
    virtual ~NavGraph();

    const has_location(NavLocationId id) = 0;
    const std::vector<NavEdge>& get_adjacent(NavLocationId id) = 0;
};


}
