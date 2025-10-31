#include "BlumBlumShub.h"

using namespace boost::multiprecision;

BlumBlumShub::BlumBlumShub(const cpp_int& _p, const cpp_int& _q)
{
    std::cout << "RNG Blum Blum Shaft starts\n\n";
    if (_p % 4 != 3 || _q % 4 != 3)
        throw std::invalid_argument("p and q must be congruent to 3 mod 4");
    this->p = _p;
    this->q = _q;
    this->N = _p * _q;
    this->seed = makeACoprimeSeed(N);
    this->xi_state = (seed * seed) % N;
}

BlumBlumShub::~BlumBlumShub()
{
}

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

uint8_t BlumBlumShub::nextBit()
{
    xi_state = (xi_state * xi_state) % N; 
    return static_cast<uint8_t>(xi_state % 2);
}

std::vector<uint8_t> BlumBlumShub::makeBits(size_t k)
{
    std::vector<uint8_t> bits;
    bits.reserve(k);
    std::cout << "Generetaing " << k << " bits..." << "\n\n";
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

cpp_int BlumBlumShub::makeRandomBigInt(const cpp_int& N)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);
    cpp_int value = 0;
    size_t bits = msb(N);              
    size_t chunks = (bits + 63) / 64;  
    for (size_t i = 0; i < chunks; i++)
    {
        value <<= 64;
        value += dist(gen);
    }
    return value % (N - 1) + 1;
}

cpp_int BlumBlumShub::makeACoprimeSeed(const cpp_int& N)
{
    cpp_int seed;
    do 
    {
        seed = BlumBlumShub::makeRandomBigInt(N);
    } while (gcd(seed, N) != 1);
    std::cout << "The seed is: " << seed << "\n\n";
    return seed;
}
