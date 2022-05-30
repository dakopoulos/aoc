#include <iostream>
#include <boost/lexical_cast.hpp>

#include "read.hpp"
#include "reactor.hpp"

using namespace aoc::reactor;

int main(int argc, char* argv[])
{
    // create reactor
    Reactor reactor({{-50, 50}, {-50, 50}, {-50, 50}});

    // args
    if(argc != 2 && argc != 3) {
        std::cerr << "incorrect arguments; usage: ./reboot-reactor "
            " <init-sequence-file> [<boot-sequence-file]" << std::endl;
    }

    // init
    std::cout << "read & apply init sequence..." << std::endl;
    apply_boot_sequence(reactor,
        boost::lexical_cast<std::string>(argv[1]),
        Reactor::Mode::INIT);
    std::cout << "...done" << std::endl;

    // boot
    if(argc == 3) {
        std::cout << "read & apply boot sequence..." << std::endl;
        apply_boot_sequence(reactor,
            boost::lexical_cast<std::string>(argv[2]),
            Reactor::Mode::BOOT);
        std::cout << "...done" << std::endl;
    }

    // print
    std::cout << "total active cores: " << reactor.active_cores() << std::endl;

    return 0;
}