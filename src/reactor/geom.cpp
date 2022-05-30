#include <iostream>
#include "geom.hpp"

namespace aoc::reactor {
    
std::optional<Range> Range::overlap_with(Range const& r) const
{
    Coord out_lo = std::max(lo, r.lo);
    Coord out_hi = std::min(hi, r.hi);

    std::optional<Range> out;
    if(out_lo <= out_hi) {
        out = Range{out_lo, out_hi};
    }
    return out;
}
    
std::optional<Range3> Range3::overlap_with(Range3 const& r) const
{
    std::optional<Range3> out;
    auto x_overlap = x.overlap_with(r.x);
    if(x_overlap) {
        auto y_overlap = y.overlap_with(r.y);
        if(y_overlap) {
            auto z_overlap = z.overlap_with(r.z);
            if(z_overlap) {
                out = Range3(*x_overlap, *y_overlap, *z_overlap);
            }
        }
    }
    return out;
}
    
bool Range3::contains(Point const& p) const
{
    return x.contains(p.x) && y.contains(p.y) && z.contains(p.z);
}

std::ostream& operator<<(std::ostream& o, Range const& r)
{
    o << "range(" << r.lo << ", " << r.hi << ")";
    return o;
}

std::ostream& operator<<(std::ostream& o, Range3 const& r)
{
    o << "range3[" << r.x << ", " << r.y << ", " << r.z << "]";
    return o;
}

} // ~ namespace aoc::reactor