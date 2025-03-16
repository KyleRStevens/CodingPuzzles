#pragma once

// Standard
#include <vector>
#include <iostream>
#include <unordered_set>
#include <set>
#include <stack>
#include <cstdint>
#include <map>
#include <mutex>

class Solution_RotaryLock
{
public:
	inline int shorterPath(int N, int num1, int num2)
	{
		// Determine the shorter path to the following digit
		int diff1 = std::abs(num1 - num2);
		int diff2 = N - diff1;
		return std::min(diff1, diff2);
	}

	long long getMinCodeEntryTime(int N, int M, std::vector<int>& C)
	{
		long long minCodeEntryTime = 0;

		// Remember to include the time to the first digit
		minCodeEntryTime += shorterPath(N, 1, C[0]);

		// For each digit in C (minus 1)
		for (int i = 0; i < C.size() - 1; ++i)
		{
			// Determine the shorter path to the next digit & add that many seconds to your running count
			int num1 = C[i];
			int num2 = C[i + 1];
			minCodeEntryTime += shorterPath(N, num1, num2);
		}

		// Return min total min time
		return minCodeEntryTime;
	}
};