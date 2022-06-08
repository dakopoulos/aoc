#include <iostream>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/discrete_interval.hpp>
#include "geom.hpp"

namespace aoc::reactor {
    
std::optional<Range> Range::overlap_with(Range const& r) const
{
    auto const out_lo = std::max(lo_, r.lo());
    auto const out_hi = std::min(hi_, r.hi());

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
    
std::list<Range> Range::split(Range const& r) const
{
    using Interval_set = boost::icl::interval_set<Coord>;
    using Interval = boost::icl::discrete_interval<Coord>;

    auto make_set = [](auto l, auto h) {
        Interval_set s;
        s.insert(Interval(l, h, boost::icl::interval_bounds::closed()));
        return s;
    };

    auto const s1 = make_set(lo_, hi_);
    auto const s2 = make_set(r.lo(), r.hi());
    
    std::list<Range> out;
    auto add_set = [&out](auto const& s) {
        for(auto const& i: s) {
            if(i.bounds() == boost::icl::interval_bounds::closed()) {
                out.emplace_back(i.lower(), i.upper());
            } else if(i.bounds() == boost::icl::interval_bounds::open()) {
                out.emplace_back(i.lower() + 1, i.upper() - 1);
            } else if(i.bounds() == boost::icl::interval_bounds::right_open()) {
                out.emplace_back(i.lower(), i.upper() - 1);
            } else if(i.bounds() == boost::icl::interval_bounds::left_open()) {
                out.emplace_back(i.lower() + 1, i.upper());
            }
        }
    };
    add_set(s1 - s2);
    add_set(s1 & s2);

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
    
bool Range3::contains(Range3 const& r) const
{
    return x.contains(r.x) && y.contains(r.y) && z.contains(r.z);
}
    
std::list<Range3> Range3::split(Range3 const& r) const
{
    auto x_split = x.split(r.x);
    auto y_split = y.split(r.y);
    auto z_split = z.split(r.z);

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