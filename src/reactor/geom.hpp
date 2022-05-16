#ifndef AOC_REACTOR_POINT_HPP
#define AOC_REACTOR_POINT_HPP

#include <stdexcept>
#include <optional>

namespace aoc::reactor {

struct Range
{
    Range(int lo_, int hi_) : lo(lo_), hi(hi_)
    {
        if(lo_ > hi_) {
            throw std::runtime_error("range's lo must be <= range's hi");
        }
    }

    int size() const { return hi - lo; }
    std::optional<Range> overlap_with(Range const& r) const;

    int lo{0};
    int hi{0};
};

std::ostream& operator<<(std::ostream& o, Range const& r);

struct Range3
{
    Range3(Range const& x_, Range const& y_, Range const& z_)
        : x(x_), y(y_), z(z_) {}
    std::size_t size() const { return x.size() * y.size() * z.size(); }
    std::optional<Range3> overlap_with(Range3 const& r) const;
    
    Range x;
    Range y;
    Range z;
};

std::ostream& operator<<(std::ostream& o, Range3 const& r);

struct Point2
{
    Point2(int x_, int y_) : x(x_), y(y_) {}
    int x{0};
    int y{0};
};

struct Point3 : public Point2
{
    Point3(int x_, int y_, int z_) : Point2(x_, y_), z(z_) {}
    int z{0};
};

} // ~ namespace aoc::reactor

#endif // ~ AOC_REACTOR_POINT_HPP