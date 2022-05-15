#include <boost/lexical_cast.hpp>
#include "num.hpp"
#include "read.hpp"
#include "add.hpp"

using namespace aoc::snailfish;

int main(int argc, char* argv[])
{
    if(argc == 2) {
        auto const filename = boost::lexical_cast<std::string>(argv[1]);
        auto const nums = aoc::snailfish::from_file(filename);
        if(nums.size() < 3 != 0) {
            throw std::runtime_error("at least 3 numbers are expected");
        }

        // add all numbers but the last
        Number result = nums.front();
        for(std::size_t i = 1; i < nums.size() - 1; ++i) {
            result = add(result, nums[i]);
        }

        // read the last number which is the expected
        Number expected = nums.back();

        // compare number in a silly way (by converting to strings)
        if(result.to_string() != expected.to_string()) {
            std::cerr << "failed to add"
                << "\n\tactual  : " << result
                << "\n\texpected: " << expected << std::endl;
        } else {
            std::cout << "result: " << result << std::endl;
            std::cout << "pass with magnitude: " << result.magnitude() << std::endl;
        }
    } else {
        std::cout << "doing nothing...\n";
    }
    return 0;
}