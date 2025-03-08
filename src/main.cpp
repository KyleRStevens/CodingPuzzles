// Standard
#include <iostream>

// 1st Party
#include "TwoSum.h"

int main()
{
	// Two Sum
	std::vector<int> twoSumTestCase{ 2,7,11,15 };
	int twoSumTarget = 9;
	Solution_TwoSum twoSumSolution;
	auto twoSumResult = twoSumSolution.twoSum(twoSumTestCase, twoSumTarget);

	return 0;
}