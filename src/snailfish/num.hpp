#ifndef AOC_SNAILFISH_NUM_HPP
#define AOC_SNAILFISH_NUM_HPP

#include <iostream>
#include <memory>
#include <optional>

namespace aoc::snailfish {

using Int = int;

/// Snailfish number
///
class Number
{
public:
    // constructors
    Number(Int value);
    Number(Number const& left, Number const& right);
    Number(Number const& n);
    Number& operator=(Number const& n);

    // getters
    std::optional<Int> const& value() const { return value_; }
    std::unique_ptr<std::pair<Number, Number>> const& lr() const { return lr_; }

    // arithmetics
    Number& operator+=(Number const& n);
    Number& operator+=(Int value);
    std::unique_ptr<std::pair<Number, Number>> explode();
    Int magnitude() const;

    // other
    bool empty() const;
    std::string to_string() const;
    bool is_pair() const;
    bool is_regular() const;

private:
    std::optional<Int> value_;
    std::unique_ptr<std::pair<Number, Number>> lr_ = nullptr;
};

std::ostream& operator<<(std::ostream& out, Number const& n);

} // ~ namespace aoc

#endif // ~ AOC_SNAILFISH_NUM_HPP