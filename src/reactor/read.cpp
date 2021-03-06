#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <optional>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "reactor.hpp"

namespace aoc::reactor {

Range read_range(std::string const& s)
{
    std::vector<std::string> toks;
    boost::split(toks, s, boost::is_any_of("=,. \t"), boost::token_compress_on);
    if(toks.size() != 3) {
        throw std::runtime_error("");
    }
    return Range(boost::lexical_cast<Coord>(toks[1]),
        boost::lexical_cast<Coord>(toks[2]));
}

std::optional<Boot_step> read_boot_step(std::string const& s)
{
    std::vector<std::string> tokens;
    std::optional<Boot_step> out;

    if(!s.empty()) {
        try {
        
        boost::split(tokens, s, boost::is_any_of("\t, "), boost::token_compress_on);
        if(!tokens.empty()) {
            if(tokens.size() != 4) {
                throw std::runtime_error("");
            }

            // lower case (just for safefy...) 
            for(auto& i: tokens) {
                boost::to_lower(i);
            }
            
            // status
            bool status = false;
            if(tokens[0] == "on") {
                status = true;
            }

            // ranges
            std::optional<Range> range_x;
            std::optional<Range> range_y;
            std::optional<Range> range_z;
            for(auto i = std::size_t(1); i != tokens.size(); ++i) {
                if(boost::starts_with(tokens[i], "x")) {
                    range_x = read_range(tokens[i]);
                } else if(boost::starts_with(tokens[i], "y")) {
                    range_y = read_range(tokens[i]);
                } else if(boost::starts_with(tokens[i], "z")) {
                    range_z = read_range(tokens[i]);
                }
            }
            if(!range_x || !range_y || !range_z) {
                std::runtime_error("");
            }

            out = Boot_step({*range_x, *range_y, *range_z}, status);
        }
        
        } catch(...) { // catch all errors...
            std::stringstream msg;
            msg << "string \"" << s << "\" has incorrect format";
            throw std::runtime_error(msg.str());
        }
    }

    return out;
}

std::vector<Boot_step> read_boot_sequence(std::string const& filename)
{
    std::vector<Boot_step> out;
    std::ifstream fp(filename.c_str());
    while(fp.good()) {
        std::string line;
        getline(fp, line);
        auto boot_step = read_boot_step(line);
        if(boot_step) {
            out.emplace_back(*boot_step);
        }
    }
    fp.close();
    return out;
}

void apply_boot_sequence(
    Reactor& reactor,
    std::string const& filename,
    Reactor::Mode const& mode)
{
    std::ifstream fp(filename.c_str());
    while(fp.good()) {
        std::string line;
        getline(fp, line);
        auto boot_step = read_boot_step(line);
        if(boot_step) {
            reactor.apply(*boot_step, mode);
        }
    }
    fp.close();
}

} // ~ namespace aoc::reactor