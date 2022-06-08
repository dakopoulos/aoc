#ifndef AOC_REACTOR_POINT_HPP
#define AOC_REACTOR_POINT_HPP

#include <stdexcept>
#include <optional>
#include <boost/functional/hash.hpp>

#include "common.hpp"

namespace aoc::reactor {

/// 1D range of integers
///
class Range
{
public:
    Range(Coord lo, Coord hi) : lo_(lo), hi_(hi)
    {
        if(lo > hi) {
            throw std::runtime_error("range's lo must be <= range's hi");
        }
    }

    bool operator==(Range const&) const = default;
    Coord size() const { return hi_ - lo_ + 1; }
    std::optional<Range> overlap_with(Range const& r) const;
    bool contains(Range const& r) const;
    Coord lo() const noexcept { return lo_; }
    Coord hi() const noexcept { return hi_; }
    std::list<Range> split(Range const&) const;

private:
    Coord lo_{0};
    Coord hi_{0};
};

std::ostream& operator<<(std::ostream& o, Range const& r);

/// 3D range of integers
///
struct Range3
{
    Range3(Range const& x_, Range const& y_, Range const& z_)
        : x(x_), y(y_), z(z_) {}
    bool operator==(Range3 const&) const = default;
    std::size_t size() const { return x.size() * y.size() * z.size(); }
    std::optional<Range3> overlap_with(Range3 const& r) const;
    bool contains(Range3 const&) const;
    std::list<Range3> split(Range3 const&) const;
    
    Range x;
    Range y;
    Range z;
};

std::ostream& operator<<(std::ostream& o, Range3 const& r);

} // ~ namespace aoc::reactor

#endif // ~ AOC_REACTOR_POINT_HPP