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

    /// Construct a regular number
    Number(Int value);

    /// Construct with a pair of any other snailfish numbers
    Number(Number const& left, Number const& right);

    Number(Number const& n);
    Number& operator=(Number const& n);

    std::optional<Int> const& value() const { return value_; }
    std::unique_ptr<std::pair<Number, Number>> const& lr() const { return lr_; }

    Number& operator+=(Number const& n);
    Number& operator+=(Int value);
    std::unique_ptr<std::pair<Number, Number>> explode();

    /// Calculate the magnitude of the number
    Int magnitude() const;

    /// Check if the number is empty
    bool empty() const;

    /// Convert to string
    std::string to_string() const;

    /// Returns true if it's a pair of regular numbers
    bool is_pair() const;

    /// Return true if it's a regular number
    bool is_regular() const;

private:
    std::optional<Int> value_; // regular
    std::unique_ptr<std::pair<Number, Number>> lr_ = nullptr; // pair of numbers
};

std::ostream& operator<<(std::ostream& out, Number const& n);

} // ~ namespace aoc

#endif // ~ AOC_SNAILFISH_NUM_HPP