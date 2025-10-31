#include "BlumBlumShub.h"
#include "NistStats.h"

int main() 
{
    cpp_int p = 499;
    cpp_int q = 547;

    BlumBlumShub bbs(p, q);

    auto bits = bbs.makeBits(10000);
    std::cout << "Bits: ";
    for (auto b : bits) std::cout << int(b);
    std::cout << "\n";
    std::cout << "Monobit test result [0/1]: " << monobitTest(bits) << "\n";
    std::cout << "Frequency within a block test result [0/1]: " << frequencyWithinBlockTest(bits) << "\n";
}