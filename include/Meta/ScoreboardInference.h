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

class Solution_ScoreboardInference
{
public:
	int getMinProblemCount(int N, std::vector<int>& S) // O(N)
	{
		int minProblemCount = 0;

		// Find the max score (flagging if there are any odd numbers in the list)
		bool oddExists = false;
		long long maxScore = 0;
		for (int i = 0; i < S.size(); ++i) // O(N)
		{
			// Keep updating the max
			if (S[i] > maxScore)
			{
				maxScore = S[i];
			}

			// Until an odd is found, keep checking for odds
			if (oddExists == false && S[i] % 2 != 0)
			{
				oddExists = true;
			}
		}

		// If there is an odd number in the list, the result is (max score / 2) + 1
		if (oddExists)
		{
			minProblemCount = (maxScore / 2) + 1;
		}
		else
		{
			// If there are no odd numbers, the result is just (max score / 2)
			minProblemCount = maxScore / 2;
		}

		// Return the inferred min problem count
		return minProblemCount;
	}
};