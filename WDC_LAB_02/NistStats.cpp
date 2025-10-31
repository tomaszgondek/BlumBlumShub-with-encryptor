#include "NistStats.h"
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <math.h>
using namespace boost::multiprecision;

bool monobitTest(std::vector<uint8_t> v)
{
	std::cout << "Monobit test begin\n";
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
	std::cout << "Sum: " << sum << "\n";
	s_obs = static_cast<float>(abs(sum) / sqrt(static_cast<double>(v.size())));
	p_val = erfc(static_cast<float>(s_obs / 1.41421356237));
	std::cout << "P value: " << p_val << "\n";
	if (p_val < 0.01)
	{
		std::cout << "Sequence is not random, P value is lower than 0.01 \n";
		return 0;
	}
	else 
	{
		std::cout << "Sequence is random, P value is higher than 0.01 \n";
		return 1;
	}
}

