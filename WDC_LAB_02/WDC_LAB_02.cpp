#include "BlumBlumShub.h"

int main() 
{
    cpp_int p("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171");
    cpp_int q("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084167");
    cpp_int seed = 123456789;

    BlumBlumShub bbs(p, q, seed);

    auto bits = bbs.makeBits(20);
    std::cout << "Bits: ";
    for (auto b : bits) std::cout << int(b);
    std::cout << "\n";

    auto bytes = bbs.makeBytes(5);
    std::cout << "Bytes: ";
    for (auto b : bytes) std::cout << std::hex << (int)b << " ";
    std::cout << std::dec << "\n";
}