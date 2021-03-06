#ifndef AOC_SNAILFISH_ADD_HPP
#define AOC_SNAILFISH_ADD_HPP

#include "num.hpp"

namespace aoc::snailfish {

class Number; // fw

/// Add two snailfish numbers and return the result
///
Number add(Number const& n1, Number const& n2);

} // ~ namespace aoc::snailfish 

#endif // ~ AOC_SNAILFISH_ADD_HPP