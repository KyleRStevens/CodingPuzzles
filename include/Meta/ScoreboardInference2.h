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

class Solution_ScoreboardInference2
{
public:
	int getMinProblemCount(int N, std::vector<int>& S) // O(N)
	{
		int minProblemCount = 0;

		bool allNumbersDivisibleBy3 = true;
		bool remainder1Found = false;
		bool remainder2Found = false;

		// Find the max score & next highest score (and flagging special conditions)
		int maxScore = 0;
		int secondToMaxScore = 0;
		int thirdToMaxScore = 0;
		for (int i = 0; i < S.size(); ++i) // O(N)
		{
			// Keep updating the max
			if (S[i] > maxScore)
			{
				thirdToMaxScore = secondToMaxScore;
				secondToMaxScore = maxScore;
				maxScore = S[i];
			}

			// Check if there are numbers that are 'non-divisible by 3' OR 'non-divisible by 3 or 2'
			if (S[i] % 3 != 0)
			{
				allNumbersDivisibleBy3 = false;

				if (S[i] % 3 == 1)
				{
					remainder1Found = true;
				}
				else // (S[i] % 3 == 2)
				{
					remainder2Found = true;
				}
			}
		}

		// Determine if all 'non-divisible by 3' numbers have the same remainder (when dividing by 3)
		bool allNumbersNotDivisibleBy3ShareTheSameRemainder = (remainder1Found != remainder2Found);

		// If there is a 'non-divisible by 3' number in the list, the result is (max score / 2) + 1
		if (allNumbersDivisibleBy3)
		{
			// If there are no 'non-divisible by 3' numbers, the result is just (max score / 3)
			minProblemCount = maxScore / 3;
		}
		else if (allNumbersNotDivisibleBy3ShareTheSameRemainder)
		{
			// If there are 'non-divisible by 3' numbers AND they all have the same remainder (when dividing by 3), only 1 additional problem is required
			minProblemCount = (maxScore / 3) + 1;
		}
		else
		{
			// If there are 'non-divisible by 3' numbers AND they do NOT all share the same remainder (when dividing by 3), 2 additional problems are required
			int num3s = (maxScore / 3);
			if (maxScore % 3 == 0)
			{
				num3s--;
			}
			else if (maxScore % 3 == 1 && maxScore - 2 == secondToMaxScore && maxScore - 3 != thirdToMaxScore)
			{
				// Special case - in this scenario, it is "cheaper" to use a second 2-point question rather than needlessly having a 3-point question and a 1-point question
				// If there is a remainder of 2 num, a remainder of 1 number, and the remainder of 1 number is the max and 2 above the remainder of 2 number, then --1
				num3s--;
			}
			minProblemCount = num3s + 2;
		}

		// Return the inferred min problem count
		return minProblemCount;
	}
};