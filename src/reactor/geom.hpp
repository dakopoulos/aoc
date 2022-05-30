#ifndef AOC_REACTOR_POINT_HPP
#define AOC_REACTOR_POINT_HPP

#include <stdexcept>
#include <optional>
#include <boost/functional/hash.hpp>

#include "common.hpp"

namespace aoc::reactor {

/// 3D point
///
struct Point
{
    Point(Coord x_, Coord y_, Coord z_) : x(x_), y(y_), z(z_) {}
    bool operator==(Point const&) const = default;
    Coord x{0};
    Coord y{0};
    Coord z{0};
};


/// Hashing of Point
///
struct Point_hash
{
    std::size_t operator()(Point const& p) const
    {
        std::size_t seed{0};
        boost::hash_combine(seed, p.x);
        boost::hash_combine(seed, p.y);
        boost::hash_combine(seed, p.z);
        return seed;
    }
};


/// 1D range of integers
///
struct Range
{
    Range(Coord lo_, Coord hi_) : lo(lo_), hi(hi_)
    {
        if(lo_ > hi_) {
            throw std::runtime_error("range's lo must be <= range's hi");
        }
    }

    Coord size() const { return hi - lo + 1; }
    std::optional<Range> overlap_with(Range const& r) const;
    bool contains(Coord i) const { return i >= lo && i <= hi; }

    Coord lo{0};
    Coord hi{0};
};

std::ostream& operator<<(std::ostream& o, Range const& r);

/// 3D range of integers
///
struct Range3
{
    Range3(Range const& x_, Range const& y_, Range const& z_)
        : x(x_), y(y_), z(z_) {}
    std::size_t size() const { return x.size() * y.size() * z.size(); }
    std::optional<Range3> overlap_with(Range3 const& r) const;
    bool contains(Point const& p) const;
    
    Range x;
    Range y;
    Range z;
};

std::ostream& operator<<(std::ostream& o, Range3 const& r);

} // ~ namespace aoc::reactor

#endif // ~ AOC_REACTOR_POINT_HPP