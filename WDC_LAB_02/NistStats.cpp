/*
	This module implements two statistical tests from NIST
	Statistics Suite creating to judge if the random numbers
	are in fact random
*/

#include "NistStats.h"
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <iostream>
#include <math.h>
using namespace boost::multiprecision;

//Monobit test: a simple test that works by adding or subtracting 1 
//to a sum, if a bit is 1 then we add, if 0 then we subtract. From 
//the sum we can see the imbalance of 0 and 1 in sequence
bool monobitTest(std::vector<uint8_t> v)
{
	int64_t sum = 0;
	float s_obs = 0;
	float p_val = 0;
	for(uint64_t i = 0; i < v.size(); i++) //S_n = X_1 + X_2 + ... + X_n
	{
		if(v[i] == 1)
		{
			sum += 1;
		}
		else if(v[i] == 0)
		{
			sum -= 1;
		}
	}
	s_obs = static_cast<float>(abs(sum) / sqrt(static_cast<double>(v.size()))); // S_obs = |S_n| / sqrt(n)
	p_val = erfc(static_cast<float>(s_obs / 1.41421356237)); // P-value = erfc(S_obs / sqrt(2))
	if (p_val < 0.01) //Decision rule at 1% level
	{
		return 0;
	}
	else 
	{
		return 1; //if random (passed)
	}
}

//This tests the proportion of ones within M-bir block and determine if the frequency
//is around M/2, as would be expected if sequence is random
bool frequencyWithinBlockTest(std::vector<uint8_t> v)
{
	uint64_t M, n = 0;
	if (v.size() < 400) //Meaningful results require large enoufg sequence
	{
		std::cerr << "Vector is too small to yield meaningful results\n";
		return 0;
	}
	else if (v.size() >= 400 && v.size() < 1000) //Assigning block sizes in relation to vector size
	{
		M = 20;
	}
	else if (v.size() >= 1000 && v.size() < 10000)
	{
		M = 50;
	}
	else
	{
		M = 50;
	}
	n = v.size() / M;
	double chi_square = 0.0;
	for (uint64_t i = 0; i < n; ++i)
	{
		uint64_t ones = 0;
		for (uint64_t j = 0; j < M; ++j)
		{
			ones += v[i * M + j]; //2.2.4 (2) from NIST test suite
		}
		double pi = static_cast<double>(ones) / M; 
		chi_square += std::pow(pi - 0.5, 2);
	}
	chi_square *= 4.0 * M; //?2(obs) = 4 M ?(?i - ?)^2.
	//P-value = igamc(N/2, ?2(obs) / 2)
	double p_val = boost::math::gamma_q(static_cast<double>(n) / 2.0, chi_square / 2.0); 
	if (p_val < 0.01)
	{
		return 0;
	}
	else
	{
		return 1; // if random (pass)
	}
}

