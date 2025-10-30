#pragma once
#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <random>

using namespace boost::multiprecision;


class BlumBlumShub
{
private:
	//functions
	cpp_int gcd(const cpp_int& a, const cpp_int& b);
	cpp_int makeRandomBigInt(const cpp_int& N);
	cpp_int makeACoprimeSeed(const cpp_int& N);
	//variables
	cpp_int p;
	cpp_int q;
	cpp_int seed;
	cpp_int N;
	cpp_int xi_state;

public:
	//constructor / deconstructor
	BlumBlumShub(const cpp_int& _p, const cpp_int& _q);
	virtual ~BlumBlumShub();
	//functions
	uint8_t nextBit();
	std::vector<uint8_t>makeBits(size_t k);
	std::vector<uint8_t>makeBytes(size_t k);
};