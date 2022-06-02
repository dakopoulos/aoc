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

static
void turn_on(
    Range3 const& cores,
    std::list<Range3>& active_cores,
    std::list<Range3>::iterator start,
    std::vector<Range3>& to_activate,
    std::vector<std::list<Range3>::iterator>& to_deactivate)
{
    bool no_overlaps{true};
    for(auto i = start; i != active_cores.end(); ++i) {
        auto const& ac = *i;
        auto overlap = ac.overlap_with(cores);
        if(overlap) {
            no_overlaps = false;

            // split active cores
            auto split_i = ac.split(cores);
            active_cores.insert(active_cores.end(), split_i.begin(),
                split_i.end());
            
            // remove old active cores
            to_deactivate.push_back(i);

            // split input cores
            auto split_cores = cores.split(ac);
            
            // run again for each split core
            start = i;
            ++start;
            for(auto const& j: split_cores) {
                turn_on(j, active_cores, start, to_activate, to_deactivate);
            }
        }
    }

    // if there are no overlaps with any of the cores, activate!
    if(no_overlaps == true) {
        to_activate.emplace_back(cores.x, cores.y, cores.z);
        // active_cores.emplace_back(cores.x, cores.y, cores.z);
    }
}

static
void turn_off(
    Range3 const& cores,
    std::list<Range3>& active_cores,
    std::list<Range3>::iterator start,
    std::vector<std::list<Range3>::iterator>& to_deactivate)
{
    for(auto i = start; i != active_cores.end(); ++i) {
        auto const& ac = *i;

        // de-activate / erase 
        if(ac == cores) {
            to_deactivate.push_back(i);
        } else {
            auto overlap = ac.overlap_with(cores);
            if(overlap) {
                // split active cores
                auto split_i = ac.split(cores);
                active_cores.insert(active_cores.end(), split_i.begin(),
                    split_i.end());

                // mark active core to remove
                to_deactivate.push_back(i);

                // split input cores
                auto split_cores = cores.split(ac);
                
                // run again for each split core
                start = i;
                ++start;
                for(auto const& j: split_cores) {
                    turn_off(j, active_cores, ++start, to_deactivate);
                }
            }
        }
    }
}

void Reactor::apply_helper(Range3 const& cores, bool status)
{
    std::vector<Range3> to_activate;
    std::vector<std::list<Range3>::iterator> to_deactivate;
    if(status) {
        turn_on(cores, active_cores_, active_cores_.begin(), to_activate, to_deactivate);
    } else {
        turn_off(cores, active_cores_, active_cores_.begin(), to_deactivate);
    }

    for(auto const& i: to_deactivate) {
        active_cores_.erase(i);
    }
    for(auto const& i: to_activate) {
        active_cores_.push_back(i);
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