#include <fstream>
#include <boost/lexical_cast.hpp>
#include "read.hpp"

namespace aoc::snailfish {

std::pair<Number, std::string::const_iterator> from_str(
    std::string::const_iterator begin,
    std::string::const_iterator end)
{
    std::optional<Number> left;
    std::optional<Number> right;
    for(auto i = begin; i != end; ++i) {
        if(*i == '[') {
            ++i;
            // digit
            if(std::isdigit(*i)) {
                left = Number(boost::lexical_cast<Int>(*i));
            // nested number
            } else {
                std::tie(left, i) = from_str(i, end);
            }
        } else if(*i == ',') {
            ++i;
            if(std::isdigit(*i)) {
                right = Number(boost::lexical_cast<Int>(*i));
            } else {
                std::tie(right, i) = from_str(i, end);
            }
            if(!left || !right) {
                throw std::runtime_error("formatting error");
            }
            Number out(*left, *right);
            return {out, i};
        }
    }
}

Number from_str(std::string const& s)
{
    auto begin = s.begin();
    auto end = s.end();
    return from_str(begin, end).first;
}

std::vector<Number> from_file(std::string const& filename, bool validate)
{
    std::vector<Number> out;
    std::ifstream fp(filename.c_str());
    std::cout << "reading numbers from: " << filename << "..." << std::endl;
    while(fp.good()) {
        // one line per number
        std::string line;
        std::getline(fp, line);
        out.emplace_back(std::move(from_str(line)));
        
        // error checking
        if(validate) {
            if(line != out.back().to_string()) {
                throw std::runtime_error(
                    "error comparing line and number read");
            }
        }
    }
    std::cout << "..." << out.size() << " numbers read" << std::endl;
    return out;
}

} // ~ namespace aoc::snailfish