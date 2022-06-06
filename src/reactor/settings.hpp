#ifndef AOC_REACTOR_SETTINGS_HPP
#define AOC_REACTOR_SETTINGS_HPP

#include <string>
#include <vector>
#include <boost/program_options.hpp>

namespace aoc::reactor {

struct Settings
{
    Settings() = default;

    bool init(int argc, char* argv[])
    {
        namespace po = boost::program_options;
        po::options_description desc("Reactor options");
        desc.add_options()
            ("help", "produce help message")
            ("init,i", po::value<std::vector<std::string>>()->multitoken(),
             "Initialization files")
            ("reboot,r", po::value<std::vector<std::string>>()->multitoken(),
             "Reboot files")
        ;

        po::variables_map vm;        
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if(vm.count("init")) {
            init_files = vm["init"].as<std::vector<std::string>>();
        }
        if(vm.count("reboot")) {
            reboot_files = vm["reboot"].as<std::vector<std::string>>();
        }

        if(vm.count("help")) {
            std::cout << desc << "\n";
            return false;
        }
        return true;
    }
    std::vector<std::string> init_files;
    std::vector<std::string> reboot_files;
};

};

#endif // ~ AOC_REACTOR_SETTINGS_HPP