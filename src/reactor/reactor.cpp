#include <algorithm>
#include "reactor.hpp"

namespace aoc::reactor {

Reactor::Reactor(Range3 const& init_cores)
    : init_cores_(init_cores)
{
}
    
void Reactor::apply(Boot_step const& step, Mode const& mode)
{
    std::cout << "\tapplying boot/init step...\n";
    if(mode == Mode::BOOT) {
        // during boot phase, any core can be utilized (in theory infinite)
        apply_helper(step.cores, step.status);
    } else if (mode == Mode::INIT) {
        // during the initialization phase, use only only cores within the
        // initialization range e.g. [-50, 50]
        auto const overlap = init_cores_.overlap_with(step.cores);
        if(overlap) {
            apply_helper(*overlap, step.status);
        }
    }
}

void Reactor::turn_on(Range3 const& cores)
{
    // iterate through all incoming cores
    for(Coord x = cores.x.lo; x <= cores.x.hi; ++x) {
        for(Coord y = cores.y.lo; y <= cores.y.hi; ++y) {
            for(Coord z = cores.z.lo; z <= cores.z.hi; ++z) {
                Point p(x, y, z);
                // activate if not active
                if(active_cores_.find(p) == active_cores_.end()) {
                    active_cores_.insert(p);
                }
            }
        }
    }
}

void Reactor::turn_off(Range3 const& cores)
{
    for(auto i = active_cores_.begin(); i != active_cores_.end();) {
        if(cores.contains(*i)) {
            i = active_cores_.erase(i);
        } else {
            ++i;
        }
    }
}

void Reactor::apply_helper(Range3 const& cores, bool status)
{
    if(status) {
        turn_on(cores);
    } else {
        turn_off(cores);
    }
}

std::size_t Reactor::active_cores() const
{
    return active_cores_.size();
}
    
std::ostream& operator<<(std::ostream& o, Boot_step const& s)
{
    o << "Boot_step[" << s.cores << ", status: " << s.status << "]";
    return o;
}

} // ~ namespace aoc::reactor