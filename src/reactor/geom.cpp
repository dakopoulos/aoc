#include <iostream>
#include "geom.hpp"

namespace aoc::reactor {
    
std::optional<Range> Range::overlap_with(Range const& r) const
{
    Coord out_lo = std::max(lo_, r.lo());
    Coord out_hi = std::min(hi_, r.hi());

    std::optional<Range> out;
    if(out_lo <= out_hi) {
        out = Range{out_lo, out_hi};
    }
    return out;
}

bool Range::contains(Range const& r) const
{
    return lo_ <= r.lo() && hi_ >= r.hi();
}
    
std::list<Range> Range::split(Range const& r, bool reverse) const
{
    auto* a = this;
    auto* b = &r;
    if(reverse) {
        std::swap(a, b);
    }

    std::vector<Coord> points = {a->lo_};
    if(b->lo() > a->lo() && b->lo() < a->hi_ && b->lo() != points.back()) {
        points.emplace_back(b->lo());
    }
    if(b->hi() > a->lo() && b->hi() < a->hi() && b->hi() != points.back()) {
        points.emplace_back(b->hi());
    }
    if(points.size() == 1 || a->hi() != points.back()) {
        points.emplace_back(a->hi());
    }

    std::list<Range> out;
    for(std::size_t i = 0; i < points.size() - 1; ++i) {
        auto end = i + 2 != points.size() ? points[i + 1] - 1 : points[i + 1];
        out.emplace_back(points[i], end);
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
    
bool Range3::contains(Range3 const& r) const
{
    return x.contains(r.x) && y.contains(r.y) && z.contains(r.z);
}
    
std::list<Range3> Range3::split(Range3 const& r, bool reverse) const
{
    auto x_split = x.split(r.x, reverse);
    auto y_split = y.split(r.y, reverse);
    auto z_split = z.split(r.z, reverse);

    std::list<Range3> out;
    for(auto const& i: x_split) {
        for(auto const& j: y_split) {
            for(auto const& k: z_split) {
                out.emplace_back(i, j, k);
            }
        }
    }
    return out;
}

std::ostream& operator<<(std::ostream& o, Range const& r)
{
    o << "range(" << r.lo() << ", " << r.hi() << ")";
    return o;
}

std::ostream& operator<<(std::ostream& o, Range3 const& r)
{
    o << "range3[" << r.x << ", " << r.y << ", " << r.z << "]";
    return o;
}

} // ~ namespace aoc::reactor