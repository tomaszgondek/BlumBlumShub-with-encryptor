#include "BlumBlumShub.h"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

cpp_int BlumBlumShub::gcd(const cpp_int& a, const cpp_int& b)
{
    cpp_int x = a, y = b;
    while (y != 0) 
    {
        cpp_int t = y;
        y = x % y;
        x = t;
    }
    return x;
}

BlumBlumShub::BlumBlumShub(const cpp_int& _p, const cpp_int& _q, const cpp_int& _seed)
{
    if (_p % 4 != 3 || _q % 4 != 3)
        throw std::invalid_argument("p and q must be congruent to 3 mod 4");
    this->p = _p;
    this->q = _q;
    this->seed = _seed;
    this->N = _p * _q;
    if (gcd(seed, N) != 1)
        throw std::invalid_argument("Seed must be coprime with N");
    this->xi_state = (seed * seed) % N;
}

BlumBlumShub::~BlumBlumShub()
{
}

uint8_t BlumBlumShub::nextBit()
{
    xi_state = (xi_state * xi_state) % N; // x_{i+1} = x_i^2 mod N
    return static_cast<uint8_t>(xi_state % 2);
}

std::vector<uint8_t> BlumBlumShub::makeBits(size_t k)
{
    std::vector<uint8_t> bits;
    bits.reserve(k);
    for (size_t i = 0; i < k; ++i)
        bits.push_back(nextBit());
    return bits;
}

std::vector<uint8_t> BlumBlumShub::makeBytes(size_t k)
{
    std::vector<uint8_t> res;
    res.reserve(k);
    for (size_t i = 0; i < k; ++i) {
        uint8_t byte = 0;
        for (int b = 0; b < 8; ++b)
            byte = (byte << 1) | nextBit();
        res.push_back(byte);
    }
    return res;
}
