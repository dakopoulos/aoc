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
    bool no_overlaps{true};
    for(auto i = active_cores_.begin(); i != active_cores_.end();) {
        auto overlap = i->overlap_with(cores);
        if(overlap) {
            no_overlaps = false;

            // split active cores
            auto split_i = i->split(cores);
            active_cores_.insert(active_cores_.end(), split_i.begin(),
                split_i.end());

            // split input cores
            auto split_cores = cores.split(*i);
            
            // remove old active cores
            i = active_cores_.erase(i);
            // run again for each split core
            for(auto const& j: split_cores) {
                turn_on(j);
            }
        } else {
            ++i;
        }
    }

    // if there are no overlaps with any of the cores, activate!
    if(no_overlaps == true) {
        active_cores_.emplace_back(cores.x, cores.y, cores.z);
    }
}

void Reactor::turn_off(Range3 const& cores)
{
    for(auto i = active_cores_.begin(); i != active_cores_.end();) {
        // de-activate / erase 
        if(*i == cores) {
            i = active_cores_.erase(i);
        } else {
            auto overlap = i->overlap_with(cores);
            if(overlap) {
                // split active cores
                auto split_i = i->split(cores);
                active_cores_.insert(active_cores_.end(), split_i.begin(),
                    split_i.end());

                // split input cores
                auto split_cores = cores.split(*i);
                
                // remove old active cores
                i = active_cores_.erase(i);
                
                // run again for each split core
                for(auto const& j: split_cores) {
                    turn_off(j);
                }
            } else {
                ++i;
            }
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