#ifndef AOC_SNAILFISH_READ_HPP
#define AOC_SNAILFISH_READ_HPP

#include <vector>
#include "num.hpp"

namespace aoc::snailfish {

/// Convert a string to a snailfish number
/// @param[in] s The input string
/// @return the snailfish number
///
Number from_str(std::string const& s);

/// Reads a file that contains snailfish numbers
/// @param[in] filename Path to input filename
/// @param[in] validate Flag to perform some validations
/// @return list of the read numbers
///
std::vector<Number> from_file(std::string const& filename,
    bool validate = false);

} // ~ namespace aoc::snailfish

#endif // ~ AOC_SNAILFISH_READ_HPP