#pragma once

// Standard
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <stack>
#include <unordered_set>
#include <vector>

// 1st Party
#include "MyMinHeap.h"

// Meta Puzzle: Hops
class Solution_Hops
{
public:
	long long getSecondsRequired(long long N, int F, std::vector<long long>& P) // O(F)
	{
		long long minFrogIndex = N;

		// Find the min frog index
		for (int i = 0; i < P.size(); ++i) // O(F)
		{
			if (P[i] < minFrogIndex)
			{
				minFrogIndex = P[i];
			}
		}

		// The answer will always be N - minFrogIndex
		return N - minFrogIndex;
	}

	void Test()
	{
		std::vector<long long> hopsFrogs{ 5, 2, 4 };
		auto hopsResult = getSecondsRequired(6, hopsFrogs.size(), hopsFrogs);
	}
};