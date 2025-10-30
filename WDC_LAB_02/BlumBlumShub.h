#pragma once

#include <math.h>
#include <iostream>
#include <numeric>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;


class BlumBlumShub
{
private:
	//functions
	cpp_int gcd(const cpp_int& a, const cpp_int& b);
	//variables
	cpp_int p;
	cpp_int q;
	cpp_int seed;
	cpp_int N;
	cpp_int xi_state;

public:
	//constructor / deconstructor
	BlumBlumShub(const cpp_int& _p, const cpp_int& _q, const cpp_int& _seed);
	virtual ~BlumBlumShub();
	//functions
	uint8_t nextBit();
	std::vector<uint8_t>makeBits(size_t k);
	std::vector<uint8_t>makeBytes(size_t k);
};