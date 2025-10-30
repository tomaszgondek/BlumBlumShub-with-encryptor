#include "BlumBlumShub.h"

int main() 
{
    cpp_int p = 11;
    cpp_int q = 1;

    BlumBlumShub bbs(p, q);

    auto bits = bbs.makeBits(40);
    std::cout << "Bits: ";
    for (auto b : bits) std::cout << int(b);
    std::cout << "\n";
    auto bytes = bbs.makeBytes(5);
    std::cout << "Bytes: ";
    for (auto b : bytes) std::cout << std::hex << (int)b << " ";
    std::cout << std::dec << "\n";
}