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
    std::cout << "\tapplying boot/init step: " << step << "...\n";
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
    // std::cout << "\tactive cores: " << active_cores() << std::endl;
}

void Reactor::apply_helper(
    std::list<Range3>& input_cores,
    bool status)
{
    // for every (active_core, input_core) pair
    for(auto ic = input_cores.begin(); ic != input_cores.end();) {
        bool ic_erased{false};
        for(auto ac = active_cores_.begin(); ac != active_cores_.end();) {
            auto ac_ic_overlap = ac->overlap_with(*ic);

            // active core and input core overlap
            if(ac_ic_overlap) {
                // turning on and full overlap
                // --> remove input core and continue to next input core
                if(status && ac->contains(*ic)) {
                    ic = input_cores.erase(ic);
                    ic_erased = true;
                    break;
                // turning off and exact overlap
                // --> remove active core and continue to next active core
                } else if(!status && ic->contains(*ac)) {
                    ac = active_cores_.erase(ac);
                // partial overlap --> split and restart loops
                } else {
                    // split both active core & input cores
                    // add to the pool and continue testing pairs
                    auto ac_split = ac->split(*ic);
                    active_cores_.insert(active_cores_.end(), ac_split.begin(),
                        ac_split.end());

                    auto ic_split = ic->split(*ac);
                    input_cores.insert(input_cores.end(), ic_split.begin(),
                        ic_split.end());

                    // erase old unsplit cores and restart active cores loop
                    active_cores_.erase(ac);
                    ic = input_cores.erase(ic);
                    ic_erased = true;
                    break;
                }
            // no overlap --> check next pair
            } else {
                ++ac;
            }
        }

        // input core is not erased or split --> continue to next input core
        if(!ic_erased) {
            ++ic;
        }
    }

    // add input cores that are not erased (i.e. overlapping after all the
    // splitting)
    if(status) {
        for(auto const& ic: input_cores) {
            active_cores_.push_back(ic);
        }
    }
}

void Reactor::apply_helper(Range3 const& cores, bool status)
{
    std::list<Range3> input_cores{cores};
    apply_helper(input_cores, status);
}

Size Reactor::active_cores() const
{
    Size total{0};
    for(auto const& i: active_cores_) {
        total += i.size();
    }
    return total;
}
    
std::ostream& operator<<(std::ostream& o, Boot_step const& s)
{
    o << "Boot_step[" << s.cores << ", status: " << s.status << "]";
    return o;
}

} // ~ namespace aoc::reactor