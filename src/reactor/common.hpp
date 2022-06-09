#ifndef AOC_REACTOR_COMMON_HPP
#define AOC_REACTOR_COMMON_HPP

#include <boost/multiprecision/cpp_int.hpp>

namespace aoc::reactor {

using Coord = int;
using Size = boost::multiprecision::cpp_int;

template<class T>
std::ostream& operator<<(std::ostream& out, std::list<T> const& data)
{
    out << "[";
    for(auto i = data.begin(); i != data.end(); ) {
        out << *i;
        if(++i != data.end()) {
            out << ", ";
        }
    }
    out << "]";
    return out;
}

} // ~ namespace aoc::reactor

#endif