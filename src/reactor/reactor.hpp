#ifndef AOC_REACTOR_REACTOR_HPP
#define AOC_REACTOR_REACTOR_HPP

#include <vector>
#include <iostream>
#include <unordered_set>

#include "common.hpp"
#include "geom.hpp"

namespace aoc::reactor {

/// Boot step for reactor
///
struct Boot_step
{
    Boot_step(Range3 const& cores_, bool status_)
        : cores(cores_), status(status_) {}
    Range3 cores;
    bool status;
};


/// The reactor
///
class Reactor
{
public:
    enum class Mode { INIT, BOOT };

    Reactor(Range3 const& init_cores);
    std::size_t active_cores() const;
    void apply(Boot_step const& step, Mode const& mode);

private:
    Range3 const init_cores_;
    std::unordered_set<Point, Point_hash> active_cores_;

private:
    void apply_helper(Range3 const& cores, bool status);
    void turn_on(Range3 const& cores);
    void turn_off(Range3 const& cores);
};

std::ostream& operator<<(std::ostream& o, Boot_step const& s);

} // ~ namespace aoc::reactor

#endif // ~ AOC_REACTOR_REACTOR_HPP