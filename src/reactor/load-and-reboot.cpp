#include <iostream>
#include <boost/lexical_cast.hpp>

#include "read.hpp"
#include "reactor.hpp"

using namespace aoc::reactor;

int main(int argc, char* argv[])
{
    // create reactor
    Reactor reactor({{-50, 50}, {-50, 50}, {-50, 50}});

    // read boost sequence
    if(argc != 2) {
        std::cerr << "incorrect arguments; usage: ./reboot-reactor "
            " <boost-sequence-file>" << std::endl;
    }
    std::cout << "reading boot sequence..." << std::endl;
    auto const boot_seq = read_boot_sequence(
        boost::lexical_cast<std::string>(argv[1]));
    std::cout << "..." << boot_seq.size() << " boot steps" << std::endl;
    std::cout << "...done" << std::endl;

    // apply in reactor
    std::cout << "applying boot sequence..." << std::endl;
    for(auto const& i: boot_seq) {
        reactor.apply(i);
    }
    std::cout << "...done" << std::endl;

    // prints
    std::cout << "tota active cores: " << reactor.active_cores() << std::endl;
    
    return 0;
}