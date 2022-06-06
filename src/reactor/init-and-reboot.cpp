#include <iostream>
#include <boost/lexical_cast.hpp>

#include "read.hpp"
#include "reactor.hpp"
#include "settings.hpp"

using namespace aoc::reactor;

int main(int argc, char* argv[])
{
    // settings
    Settings sets;
    if(!sets.init(argc, argv)) {
        return 0;
    }

    // create reactor
    Reactor reactor({{-50, 50}, {-50, 50}, {-50, 50}});

    // init
    for(auto const& i: sets.init_files) {
        std::cout << "read & apply init sequence..." << std::endl;
        apply_boot_sequence(reactor, i, Reactor::Mode::INIT);
        std::cout << "...done" << std::endl;
    }

    // boot
    for(auto const& i: sets.reboot_files) {
        std::cout << "read & apply boot sequence..." << std::endl;
        apply_boot_sequence(reactor, i, Reactor::Mode::BOOT);
        std::cout << "...done" << std::endl;
    }

    // print
    std::cout << "total active cores: " << reactor.active_cores() << std::endl;
    std::cout << "total active groups of cores: " << reactor.active_core_groups() << std::endl;

    return 0;
}