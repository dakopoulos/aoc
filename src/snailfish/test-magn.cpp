#include <fstream>
#include <boost/lexical_cast.hpp>
#include "num.hpp"
#include "read.hpp"

using namespace aoc::snailfish;

void read_and_test_data(
    std::string const& filename)
{
    std::ifstream fp(filename.c_str());
    std::cout << "reading data from: " << filename << "..." << std::endl;
    while(fp.good()) {
        // read number
        std::string line;
        std::getline(fp, line);
        auto n = from_str(line);
        if(!fp.good()) {
            throw std::runtime_error("integer is expected");
        }

        // read expected magnitude
        std::getline(fp, line);
        auto exp_magn = boost::lexical_cast<Int>(line);

        // test
        auto magn = n.magnitude();
        if(magn == exp_magn) {
            std::cout << "pass!" << std::endl;
        } else {
            std::cout << "fail: number: " << n << " has expected magnitude: "
                << exp_magn << " but calculated is: " << magn << std::endl;
        }

    }
}

int main(int argc, char* argv[])
{
    if(argc == 2) {
        auto const filename = boost::lexical_cast<std::string>(argv[1]);
        read_and_test_data(filename);
    } else {
        std::cout << "doing nothing...\n";
    }
    return 0;
}