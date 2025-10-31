#include "NistStats.h"
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <iostream>
#include <math.h>
using namespace boost::multiprecision;

bool monobitTest(std::vector<uint8_t> v)
{
	int64_t sum = 0;
	float s_obs = 0;
	float p_val = 0;
	for(uint64_t i = 0; i < v.size(); i++)
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
	s_obs = static_cast<float>(abs(sum) / sqrt(static_cast<double>(v.size())));
	p_val = erfc(static_cast<float>(s_obs / 1.41421356237));
	if (p_val < 0.01)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}

bool frequencyWithinBlockTest(std::vector<uint8_t> v)
{
	uint64_t M, n = 0;
	if (v.size() < 400)
	{
		std::cerr << "Vector is too small to yield meaningful results\n";
		return 0;
	}
	else if (v.size() >= 400 && v.size() < 1000)
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
			ones += v[i * M + j];
		}
		double pi = static_cast<double>(ones) / M; 
		chi_square += std::pow(pi - 0.5, 2);
	}
	chi_square *= 4.0 * M;
	double p_val = boost::math::gamma_q(static_cast<double>(n) / 2.0, chi_square / 2.0);
	if (p_val < 0.01)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

