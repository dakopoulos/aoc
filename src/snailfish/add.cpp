#include <sstream>
#include <cmath>
#include "num.hpp"
#include "add.hpp"

namespace aoc::snailfish {

// reduction helpers ///////////////////////////////////////////////////////////

/// Recursive function that explodes the first number (if any) that must be
/// exploded. The original snailfish number which is hierarchical, is processed
/// recursively, processing first the left and then the right elements
///
/// @param[in] n Current number
/// @param[in] depth Current depth
/// @param[in] fragments The left and right parts of the exploded number if and
/// when found
/// @param[in] exploded If true, a number has exploded
/// @param[in] finished If true, the number has exploded and both fragments of
/// the explosion are added (this is just to allow a quicker termination of the
/// recursion)
///
void explode(
    Number& n,
    std::size_t depth,
    std::unique_ptr<std::pair<Number, Number>>& fragments,
    Number*& last_left_regular,
    bool& exploded,
    bool& finished)
{
    // both fragments are added
    if(finished) {
        return;
    }

    // explode number if
    // - there has be no explosion before AND
    // - depth >= 4 AND
    // - number is a pair of two regulars
    if(fragments == nullptr && depth > 3 && n.is_pair()) {
        fragments = std::move(n.explode());
        exploded = true;
        // add left value of the exploded number to the last last regular on
        // its left (if any)
        if(fragments != nullptr && last_left_regular != nullptr) {
            *last_left_regular += *fragments->first.value();
        }
    // add right of exploded number to the current number which is on the right
    // of the exploded number if
    // - number has exploded in a previous recursion step
    // - current value is a regular
    } else if(fragments != nullptr && n.is_regular() && exploded) {
        n += *fragments->second.value();
        finished = true;
        return;
    }

    // keep track of last regular on the left up until explosion happens
    if(fragments == nullptr && n.is_regular()) {
        last_left_regular = &n;
    }

    // continue recursion left to right:
    // will keep looking for number to explode
    // OR find the next regular (if any) on the right of the explosion
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

/// Split a number (recursively)
///
/// @param[in] n The number to split
/// @return True if number was split, false if no splitting was necessary
///
bool split(Number& n)
{
    if(n.is_regular() && *n.value() > 9) {
        auto div = (double) *n.value() / 2;
        n = Number(Number(std::floor(div)), Number(std::ceil(div)));
        return true;
    } else if(n.lr()) {
        if(split(n.lr()->first)) {
            return true;
        }
        return split(n.lr()->second);
    }
    return false;
}

void reduce(Number& n) {
    while(1) {
        // first check if there is a pair to explode
        auto number_exploded = explode(n);
        // if no pair has exploded, then split a number if required
        if(!number_exploded) {
            auto number_split = split(n);
            // stop reduction if neither explosion or split was performed
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