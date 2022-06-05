#ifndef AOC_REACTOR_COMMON_HPP
#define AOC_REACTOR_COMMON_HPP

namespace aoc::reactor {

using Coord = int;

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