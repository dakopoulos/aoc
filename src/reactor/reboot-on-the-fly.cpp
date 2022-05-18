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
    
    std::cout << "applying boot sequence on the fly..." << std::endl;
    apply_boot_sequence(reactor,
        boost::lexical_cast<std::string>(argv[1]));
    std::cout << "...done" << std::endl;

    // prints
    std::cout << "tota active cores: " << reactor.active_cores() << std::endl;
    
    return 0;
}