#ifndef AOC_REACTOR_READ_HPP
#define AOC_REACTOR_READ_HPP

#include <vector>
#include "reactor.hpp"

namespace aoc::reactor {

std::vector<Boot_step> read_boot_sequence(std::string const& filename);

void apply_boot_sequence(Reactor& reactor, std::string const& filename);

} // ~ namespace aoc::reactor

#endif // ~ AOC_REACTORE_READ_HPP