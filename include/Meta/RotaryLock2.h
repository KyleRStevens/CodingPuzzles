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

// Meta Puzzle: Rotary Lock 2
class Solution_RotaryLock2
{
private:
	struct Dial
	{
		int position = 1;
		long long totalTimeSpent = 0;
	};

public:
	inline int cost(int N, int num1, int num2)
	{
		// Determine the shorter path to the following digit
		int diff1 = std::abs(num1 - num2);
		int diff2 = N - diff1;
		return std::min(diff1, diff2);
	}

	long long getMinCodeEntryTime(int N, int M, std::vector<int>& C) // O(N)
	{
		long long minCodeEntryTime = 0;
		int dial1PrevDigit = 1;
		int dial2PrevDigit = 1;

		// For each digit in C
		for (int i = 0; i < C.size(); ++i) // O(N)
		{
			// For each dial, get cost between the dials previous digit, the current digit, and the next digit
			int initialDial1Cost = cost(N, dial1PrevDigit, C[i]);
			int initialDial2Cost = cost(N, dial2PrevDigit, C[i]);
			if (i < C.size() - 1)
			{
				initialDial1Cost += cost(N, C[i], C[i + 1]);
				initialDial2Cost += cost(N, C[i], C[i + 1]);
			}

			// For each dial, get cost between the dials previous digit, and the next digit (what it would be if removing the current digit)
			int hypotheticalDial1Cost = 0;
			int hypotheticalDial2Cost = 0;
			if (i < C.size() - 1)
			{
				hypotheticalDial1Cost = cost(N, dial1PrevDigit, C[i + 1]);
				hypotheticalDial2Cost = cost(N, dial2PrevDigit, C[i + 1]);
			}

			// For each dial, determine the difference in above costs (the improvement - or not - from removing the current digit from their path)
			int dial1Diff = initialDial1Cost - hypotheticalDial1Cost;
			int dial2Diff = initialDial2Cost - hypotheticalDial2Cost;

			// Remove the digit from the dial with the greater reduction in cost (add to the total cost the difference between the dial that kept the current digit, and that dial's previous digit)
			if (dial1Diff == dial2Diff)
			{
				// If there is no difference, choose the one with the lower actual cost...?
				if (initialDial1Cost <= initialDial2Cost)
				{
					minCodeEntryTime += cost(N, dial1PrevDigit, C[i]);
					dial1PrevDigit = C[i];
				}
				else
				{
					minCodeEntryTime += cost(N, dial2PrevDigit, C[i]);
					dial2PrevDigit = C[i];
				}
			}
			else if (dial1Diff > dial2Diff)
			{
				minCodeEntryTime += cost(N, dial2PrevDigit, C[i]);
				dial2PrevDigit = C[i];
			}
			else // (dial1Diff > dial2Diff)
			{
				minCodeEntryTime += cost(N, dial1PrevDigit, C[i]);
				dial1PrevDigit = C[i];
			}
		}

		// Return min total min time
		return minCodeEntryTime;
	}

	void Test()
	{
		std::vector<int> rotaryLock2Code{ 5, 4, 5, 4, 5, 4, 2 };
		auto rotaryLock2Result = getMinCodeEntryTime(10, rotaryLock2Code.size(), rotaryLock2Code);
	}
};