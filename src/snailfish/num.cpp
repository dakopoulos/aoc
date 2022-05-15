#include <sstream>
#include "num.hpp"

namespace aoc::snailfish {
 
// constructors
Number::Number(Int value) : value_(value) {}

Number::Number(Number const& left, Number const& right)
{
    lr_ = std::make_unique<std::pair<Number, Number>>(left, right);
}

Number::Number(Number const& n)
{
    *this = n;
}

bool Number::is_pair() const
{
    return !value_ && lr_ && lr_->first.is_regular()
        && lr_->second.is_regular();
}

bool Number::is_regular() const
{
    return value_ && !lr_;
}

bool Number::empty() const
{
    return !value_ && !lr_;
}

Number& Number::operator=(Number const& n)
{
    if(&n != this) {
        value_ = n.value();
        if(n.lr()) {
            lr_ = std::make_unique<std::pair<Number, Number>>(*n.lr());
        } else {
            lr_.reset();
        }
    }
    return *this;
}

std::unique_ptr<std::pair<Number, Number>> Number::explode()
{
    value_ = 0;
    return std::move(lr_);
}

Number& Number::operator+=(Int value)
{
    if(is_pair()) {
        throw std::runtime_error("cannot add two numbers of not the same type");
    }
    if(!value_) {
        value_ = 0;
    }
    *value_ += value;
}

Number& Number::operator+=(Number const& n)
{
    *this = Number(*this, n);
    return *this;
}

std::string Number::to_string() const
{
    std::stringstream out;
    out << *this;
    return out.str();
}

Int Number::magnitude() const
{
    Int m{0};
    if(is_regular()) {
        m = *value_;
    } else if(lr_) {
        m = 3 * lr_->first.magnitude() + 2 * lr_->second.magnitude();
    }
    return m;
}

std::ostream& operator<<(std::ostream& out, Number const& n)
{
    if(n.value()) {
        out << *n.value();
    }
    if(n.lr()) {
        out << "[" << n.lr()->first << "," << n.lr()->second << "]";
    }
    return out;
}

} // ~ namespace aoc::snailfish 