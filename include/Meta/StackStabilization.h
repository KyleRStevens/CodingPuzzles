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

// Meta Puzzle: Stack Stabilization
class Solution_StackStabilization
{
public:
	int getMinimumDeflatedDiscCount(int N, std::vector<int>& R) // O(N)
	{
		int numDiscsDeflated = 0;

		// For each disc in R (working backwards)
		for (int i = R.size() - 1; i > 0; --i) // O(N)
		{
			// If at any point the current disc is <= the value of 'i' + 1, this will not be possible, so immediately return -1
			if (R[i] < i + 1)
			{
				numDiscsDeflated = -1;
				break;
			}

			// Comparing with the next (lower index) disc, if the next disc is >= the current disc...
			if (R[i - 1] >= R[i])
			{
				// Make the next disc 1 unit smaller than the current disc
				R[i - 1] = R[i] - 1;

				// And incriment the deflate counter
				numDiscsDeflated++;
			}
		}

		// Return the deflate counter
		return numDiscsDeflated;
	}

	void Test()
	{
		std::vector<int> stackStabilizationDiscs{ 6, 5, 4, 3 };
		auto stackStabilizationResult = getMinimumDeflatedDiscCount(stackStabilizationDiscs.size(), stackStabilizationDiscs);
	}
};