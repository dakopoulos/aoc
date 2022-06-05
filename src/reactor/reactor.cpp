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
    std::cout << "\tactive cores: " << active_cores() << std::endl;
    std::cout << "\tactive cores groups: " << active_cores_ << std::endl;
}

void Reactor::apply_helper(
    std::list<Range3>& input_cores,
    bool status)
{
    bool split{true};

    while(split == true) {
        // reset
        std::cout << "staring loop\n";
        split = false;
    
        // for every (active_core, input_core) pair
        for(auto ac = active_cores_.begin(); ac != active_cores_.end(); ++ac) {
            for(auto ic = input_cores.begin(); ic != input_cores.end();) {
                std::cout << "\t\tchecking overlap: " << *ac << " with " << *ic << "\n";
                // find their overlap
                auto ac_ic_overlap = ac->overlap_with(*ic);
                if(ac_ic_overlap) {
                    std::cout << "\t\toverlap: " << *ac_ic_overlap << "\n";
                    // turning on and full overlap --> remove input core
                    if(status && ac->contains(*ic)) {
                        std::cout << "\t\tfull overlap. removing\n";
                        ic = input_cores.erase(ic);
                    // turning off and exact overlap --> remove input core and active_core
                    } else if(!status && ic->contains(*ac)) {
                        ac = active_cores_.erase(ac);
                    // partial overlap --> split and continue
                    } else {
                        std::cout << "\t\tsplitting\n";

                        // split both active core & input cores
                        // add to the pool and continue testing pairs
                        auto split_ac = ac->split(*ic);
                        active_cores_.insert(active_cores_.end(), split_ac.begin(), split_ac.end());
                        std::cout << "\t\tsplit active cores: " << split_ac << "\n";

                        auto split_ic = ic->split(*ac);
                        input_cores.insert(input_cores.end(), split_ic.begin(), split_ic.end());
                        std::cout << "\t\tsplit input cores: " << split_ic << "\n";

                        // erase old cores that are now split and reset iterators
                        // to restart loops 
                        active_cores_.erase(ac);
                        input_cores.erase(ic);
                        std::cout << "total active cores: " << active_cores() << "\n";
                        std::cout << "total input cores: " << input_cores.size() << "\n";
                        split = true;
                    }
                } else {
                    std::cout << "\t\tno overlap! contd\n";
                    ++ic;
                }
                if(split == true) {
                    break;
                }
            }
            if(split == true) {
                break;
            }
        }
    }

    // add input cores that are not erased (i.e. overlapping after all the
    // splitting)
    if(status) {
        for(auto const& ic: input_cores) {
            std::cout << "\t\tadding core: " << ic << std::endl;
            active_cores_.push_back(ic);
        }
    }
}

void Reactor::apply_helper(Range3 const& cores, bool status)
{
    std::list<Range3> input_cores{cores};
    apply_helper(input_cores, status);
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