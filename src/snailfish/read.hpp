#include <vector>
#include "num.hpp"

namespace aoc::snailfish {

Number from_str(std::string const& s);

std::vector<Number> from_file(std::string const& filename,
    bool validate = false);

} // ~ namespace aoc::snailfish

