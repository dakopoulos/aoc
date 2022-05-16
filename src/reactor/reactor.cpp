#include <algorithm>
#include "reactor.hpp"

namespace aoc::reactor {

Reactor::Reactor(Range3 const& range)
    : range_(range)
{
}
    
void Reactor::apply(Boot_step const& step)
{
    auto const overlap = range_.overlap_with(step.range);
    if(overlap) {
        for(int x = overlap->x.lo; x <= overlap->x.hi; ++x) {
            for(int y = overlap->y.lo; y <= overlap->y.hi; ++y) {
                for(int z = overlap->z.lo; z <= overlap->z.hi; ++z) {
                    auto index = point_to_core_index(x, y, z);
                    if(step.status) {
                        active_cores_.insert(index);
                    } else {
                        auto found = active_cores_.find(index);
                        if(found != active_cores_.end()) {
                            active_cores_.erase(found);
                        }
                    }
                }
            }
        }
    }
}

std::size_t Reactor::active_cores() const
{
    return active_cores_.size();
}
    
std::size_t Reactor::point_to_core_index(int x, int y, int z) const
{
    return z + range_.z.size() * (y + range_.y.size() * x);
}

std::ostream& operator<<(std::ostream& o, Boot_step const& s)
{
    o << "Boot_step[" << s.range << ", status: " << s.status << "]";
    return o;
}

} // ~ namespace aoc::reactor