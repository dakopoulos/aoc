#ifndef AOC_REACTOR_REACTOR_HPP
#define AOC_REACTOR_REACTOR_HPP

#include <vector>
#include <iostream>
#include <unordered_set>

#include "geom.hpp"

namespace aoc::reactor {

/// Boot step for reactor
///
struct Boot_step
{
    Boot_step(Range3 const& range_, bool status_)
        : range(range_), status(status_) {}
    Range3 range;
    bool status;
};


/// The reactor
///
class Reactor
{
public:
    Reactor(Range3 const& range);
    std::size_t active_cores() const;
    void apply(Boot_step const& step);

private:
    Range3 const range_;
    std::unordered_set<int> active_cores_;

private:
    std::size_t point_to_core_index(int x, int y, int z) const;
};

std::ostream& operator<<(std::ostream& o, Boot_step const& s);

} // ~ namespace aoc::reactor

#endif // ~ AOC_REACTOR_REACTOR_HPP