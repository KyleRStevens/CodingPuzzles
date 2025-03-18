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

class Solution_RotaryLock2
{
public:
	inline int shorterPath(int N, int num1, int num2)
	{
		// Determine the shorter path to the following digit
		int diff1 = std::abs(num1 - num2);
		int diff2 = N - diff1;
		return std::min(diff1, diff2);
	}

	long long getMinCodeEntryTime(int N, int M, std::vector<int>& C) // O(N)
	{
		long long minCodeEntryTime = 0;
		int dial1Position = C[C.size() - 1];
		int dial2Position = 1;
		if (C.size() > 1)
		{
			dial2Position = C[C.size() - 2];
		}

		// For each digit in C
		for (int i = C.size() - 1; i >= 0; --i) // O(N)
		{
			// Determine the distance to the next digit for dial 1
			int dial1Distance = shorterPath(N, dial1Position, C[i]);

			// Determine the distance to the next digit for dial 2
			int dial2Distance = shorterPath(N, dial2Position, C[i]);

			// Move the dial with the shorter path
			if (dial1Distance <= dial2Distance)
			{
				dial1Position = C[i];
			}
			else
			{
				dial2Position = C[i];
			}

			// Add that many seconds to your running count
			minCodeEntryTime += std::min(dial1Distance, dial2Distance);
		}

		// Since we're working backwards, we have to return BOTH dial positions back to position 1
		{
			minCodeEntryTime += shorterPath(N, dial1Position, 1);
			minCodeEntryTime += shorterPath(N, dial2Position, 1);
		}

		// Return min total min time
		return minCodeEntryTime;
	}
};