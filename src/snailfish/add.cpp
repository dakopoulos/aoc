#include <sstream>
#include <cmath>
#include "num.hpp"
#include "add.hpp"

namespace aoc::snailfish {

// reduction helpers ///////////////////////////////////////////////////////////

void explode(
    Number& n,
    std::size_t depth,
    std::unique_ptr<std::pair<Number, Number>>& fragments,
    Number*& last_left_regular,
    bool& exploded,
    bool& finished)
{
    if(finished) {
        return;
    }

    // check for explosion
    if(fragments == nullptr && depth > 3 && n.is_pair()) {
        fragments = std::move(n.explode());
        exploded = true;
        // explosion happened: add to the last regular on the left (if any)
        if(fragments != nullptr && last_left_regular != nullptr) {
            *last_left_regular += *fragments->first.value();
        }
    } else if(fragments != nullptr && n.is_regular() && exploded) {
        n += *fragments->second.value();
        finished = true;
        return;
    }

    // keep track of last regular on the left up until explosion happens
    if(fragments == nullptr && n.is_regular()) {
        last_left_regular = &n;
    }

    // continue recursion: either to find the number that will explode or to
    // find the next regular on the right of the explosion
    if(n.lr()) {
        explode(n.lr()->first, depth + 1, fragments, last_left_regular,
            exploded, finished);
        explode(n.lr()->second, depth + 1, fragments, last_left_regular,
            exploded, finished);
    }
}

bool explode(Number& n)
{
    std::unique_ptr<std::pair<Number, Number>> fragments = nullptr;
    Number* last_left_regular = nullptr;
    bool exploded(false);
    bool finished(false);
    explode(n, 0, fragments, last_left_regular, exploded, finished);
    return fragments != nullptr;
}

bool split(Number& n)
{
    if(n.is_regular() && *n.value() >= 10) {
        Number left(std::floor((double) *n.value() / 2));
        Number right(std::ceil((double) *n.value() / 2));
        n = Number(left, right);
        return true;
    } else if(n.lr()) {
        if(!split(n.lr()->first)) {
            return split(n.lr()->second);
        } else {
            return true;
        }
    }
    return false;
}

void reduce(Number& n) {
    while(1) {
        auto number_exploded = explode(n);
        if(!number_exploded) {
            auto number_split = split(n);
            if(!number_split) {
                break;
            }
        }
    }
}

Number add(Number const& n1, Number const& n2)
{
    Number out(n1, n2);
    reduce(out);
    return out;
}

} // ~ namespace aoc::snailfish 