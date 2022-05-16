#include <iostream>
#include "geom.hpp"

namespace aoc::reactor {
    
std::optional<Range> Range::overlap_with(Range const& r) const
{
    int out_lo = std::max(lo, r.lo);
    int out_hi = std::min(hi, r.hi);

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
    auto y_overlap = y.overlap_with(r.y);
    auto z_overlap = z.overlap_with(r.z);
    if(x_overlap && y_overlap && z_overlap) {
        out = Range3(*x_overlap, *y_overlap, *z_overlap);
    }
    return out;
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