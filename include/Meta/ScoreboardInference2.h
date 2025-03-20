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
private:
	std::vector<std::vector<int>> extrasTable{
		{0,	0,	0,	0,	0,	0,	0},
		{0,	0,	0,	0,	0,	1,	1},
		{0,	0,	0,	0,	1,	0,	1},
		{0,	0,	0,	0,	1,	1,	2},
		{0,	0,	0,	1,	0,	0,	0},
		{0,	0,	0,	1,	0,	1,	1},
		{0,	0,	0,	1,	1,	0,	1},
		{0,	0,	0,	1,	1,	1,	2},
		{0,	0,	1,	0,	0,	1,	1},
		{0,	0,	1,	0,	1,	0,	1},
		{0,	0,	1,	0,	1,	1,	2},
		{0,	0,	1,	1,	0,	0,	1},
		{0,	0,	1,	1,	0,	1,	1},
		{0,	0,	1,	1,	1,	0,	2},
		{0,	0,	1,	1,	1,	1,	2},
		{0,	1,	0,	0,	0,	1,	2},
		{0,	1,	0,	0,	1,	0,	1},
		{0,	1,	0,	0,	1,	1,	2},
		{0,	1,	0,	1,	0,	0,	1},
		{0,	1,	0,	1,	0,	1,	2},
		{0,	1,	0,	1,	1,	0,	1},
		{0,	1,	0,	1,	1,	1,	2},
		{0,	1,	1,	0,	0,	1,	2},
		{0,	1,	1,	0,	1,	0,	2}, //
		{0,	1,	1,	0,	1,	1,	2},
		{0,	1,	1,	1,	0,	0,	1},
		{0,	1,	1,	1,	0,	1,	2},
		{0,	1,	1,	1,	1,	0,	2},
		{0,	1,	1,	1,	1,	1,	2},
		{1,	0,	0,	0,	0,	1,	1},
		{1,	0,	0,	0,	1,	0,	1},
		{1,	0,	0,	0,	1,	1,	2},
		{1,	0,	0,	1,	0,	0,	0},
		{1,	0,	0,	1,	0,	1,	1},
		{1,	0,	0,	1,	1,	0,	1},
		{1,	0,	0,	1,	1,	1,	2},
		{1,	0,	1,	0,	0,	1,	1},
		{1,	0,	1,	0,	1,	0,	1},
		{1,	0,	1,	0,	1,	1,	2},
		{1,	0,	1,	1,	0,	0,	1},
		{1,	0,	1,	1,	0,	1,	1},
		{1,	0,	1,	1,	1,	0,	2},
		{1,	0,	1,	1,	1,	1,	2},
		{1,	1,	0,	0,	0,	1,	2},
		{1,	1,	0,	0,	1,	0,	1},
		{1,	1,	0,	0,	1,	1,	2},
		{1,	1,	0,	1,	0,	0,	1},
		{1,	1,	0,	1,	0,	1,	2},
		{1,	1,	0,	1,	1,	0,	1},
		{1,	1,	0,	1,	1,	1,	2},
		{1,	1,	1,	0,	0,	1,	0},
		{1,	1,	1,	0,	1,	0,	2},
		{1,	1,	1,	0,	1,	1,	2},
		{1,	1,	1,	1,	0,	0,	1},
		{1,	1,	1,	1,	0,	1,	2},
		{1,	1,	1,	1,	1,	0,	2},
		{1,	1,	1,	1,	1,	1,	2},
	};

private:
	int getExtraRequiredProblems(int remainder0Count, int remainder1Count, int remainder2Count, int highestScore, int secondHighestScore, int thirdHighestScore)
	{
		int extraProblemsRequired = 0;

		bool r0InLast = false;
		bool r1InLast = false;
		bool r2InLast = false;
		bool r0OutsideOfLast = false;
		bool r1OutsideOfLast = false;
		bool r2OutsideOfLast = false;

		// Set the flags for the last group (the group of 3 susequent numbers starting from the largest multiple of 3 at or below the highest number)
		if (highestScore % 3 == 0)
		{
			r0InLast = true;
		}
		else if (highestScore % 3 == 1)
		{
			r1InLast = true;

			if (secondHighestScore == highestScore - 1)
			{
				r0InLast = true;
			}
		}
		else if (highestScore % 3 == 2)
		{
			r2InLast = true;

			if (secondHighestScore == highestScore - 2)
			{
				r0InLast = true;
			}
			else if (secondHighestScore == highestScore - 1)
			{
				r1InLast = true;

				if (thirdHighestScore == highestScore - 2)
				{
					r0InLast = true;
				}
			}
		}

		// Set the flags for the rest of the table values
		if ((remainder0Count > 1) || (remainder0Count == 1 && r0InLast == false))
		{
			r0OutsideOfLast = true;
		}
		if ((remainder1Count > 1) || (remainder1Count == 1 && r1InLast == false))
		{
			r1OutsideOfLast = true;
		}
		if ((remainder2Count > 1) || (remainder2Count == 1 && r2InLast == false))
		{
			r2OutsideOfLast = true;
		}

		// Search the table for the correct output value number of extra problems (this will have to do for now)
		//for (auto& row : extrasTable)
		for (int row = 0; row < extrasTable.size(); ++row)
		{
			bool testPassed = true;
			int testRow[] = {r0OutsideOfLast, r1OutsideOfLast, r2OutsideOfLast, r0InLast, r1InLast, r2InLast};
			for (int col = 0; col < 6; ++col)
			{
				if (extrasTable[row][col] != testRow[col])
				{
					testPassed = false;
					break;
				}
			}

			if (testPassed)
			{
				//std::cout << "Table row: " << row << " used" << std::endl;
				extraProblemsRequired = extrasTable[row][6];
				break;
			}
		}

		return extraProblemsRequired;
	}

public:
	int getMinProblemCount(int N, std::vector<int>& S) // O(N)
	{
		int minProblemCount = 0;

		int remainder0Count = 0;
		int remainder1Count = 0;
		int remainder2Count = 0;

		int prevRemainder0Number = 0;
		int prevRemainder1Number = 0;
		int prevRemainder2Number = 0;

		// Go through each known score
		int highestScore = 0;
		int secondHighestScore = 0;
		int thirdHighestScore = 0;
		for (int i = 0; i < S.size(); ++i) // O(N)
		{
			// Keep track of the highest scores (excluding duplicates)
			if (S[i] > highestScore)
			{
				thirdHighestScore = secondHighestScore;
				secondHighestScore = highestScore;
				highestScore = S[i];
			}

			// Flag scenarios we're interested in
			switch (S[i] % 3)
			{
			case 0:
				if (S[i] != prevRemainder0Number)
				{
					// The counter doesn't actually need to be accurate - we just need to know if there are multiple DIFFERENT numbers with this remainder
					remainder0Count++;
				}
				break;

			case 1:
				if (S[i] != prevRemainder1Number)
				{
					// The counter doesn't actually need to be accurate - we just need to know if there are multiple DIFFERENT numbers with this remainder
					remainder1Count++;
				}
				break;

			case 2:
				if (S[i] != prevRemainder2Number)
				{
					// The counter doesn't actually need to be accurate - we just need to know if there are multiple DIFFERENT numbers with this remainder
					remainder2Count++;
				}
				break;

			default:
				// This should never occur
				break;
			}
		}

		// Get the base amount of problems required
		minProblemCount = highestScore / 3;

		// Get the extra amount of required problems
		minProblemCount += getExtraRequiredProblems(remainder0Count, remainder1Count, remainder2Count, highestScore, secondHighestScore, thirdHighestScore);

		// Return the inferred min problem count
		return minProblemCount;
	}
};