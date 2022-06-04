#include <algorithm>
#include <numeric>
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
    std::list<Range3>& input_cores,
    std::list<Range3>& active_cores)
{
    bool split{true};

    while(split == true) {
        // reset
        split = false;
    
        // for every (active_core, input_core) pair
        for(auto ac = active_cores.begin(); ac != active_cores.end(); ++ac) {
            for(auto ic = input_cores.begin(); ic != input_cores.end();) {
                // find their overlap
                auto ac_ic_overlap = ac->overlap_with(*ic);
                if(ac_ic_overlap) {

                    // if they full overlap remove input core
                    if(ac_ic_overlap == *ic) {
                        ic = input_cores.erase(ic);
                        continue;
                    }

                    // if they overlap partially, split both active core & input
                    // cores, add to the pool and continue testing pairs
                    auto split_ac = ac->split(*ic, false);
                    active_cores.insert(active_cores.end(), split_ac.begin(), split_ac.end());

                    auto split_ic = ic->split(*ac, true);
                    input_cores.insert(input_cores.end(), split_ic.begin(), split_ic.end());

                    // erase old cores that are now split and reset iterators
                    // to restart loops 
                    active_cores.erase(ac);
                    ac = active_cores.end();
                    input_cores.erase(ic);
                    ic = input_cores.end();

                    split = true;
                }
                ++ic;
            }
        }
    }

    // add input cores that are not erased (i.e. overlapping after all the
    // splitting)
    for(auto const& ic: input_cores) {
        active_cores.push_back(ic);
    }
}

static
void turn_off(
    std::list<Range3> const&,
    std::list<Range3>& )
{
}

void Reactor::apply_helper(Range3 const& cores, bool status)
{
    std::list<Range3> input_cores{cores};
    if(status) {
        turn_on(input_cores, active_cores_);
    } else {
        turn_off(input_cores, active_cores_);
    }
}

std::size_t Reactor::active_cores() const
{
    return std::accumulate(active_cores_.begin(), active_cores_.end(), 0,
        [](auto const& curr, auto const& i) { return curr + i.size(); });
}
    
std::ostream& operator<<(std::ostream& o, Boot_step const& s)
{
    o << "Boot_step[" << s.cores << ", status: " << s.status << "]";
    return o;
}

} // ~ namespace aoc::reactor