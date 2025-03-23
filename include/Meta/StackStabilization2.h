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

class Solution_StackStabilization2
{
private:
	int getAverage(std::vector<int>& R) // O(N)
	{
		long long total = 0;

		for (int& number : R)
		{
			total += number;
		}

		double average = static_cast<double>(total) / static_cast<double>(R.size());
		return std::round(average);
	}

public:
	long long getMinimumSecondsRequired(std::vector<int>& R, int A, int B)
	{
		long long secondsRequired = 0;

		// Get the average (or median?) of the list
		int average = getAverage(R);

		// Get the middle index in the list
		int iMiddle = R.size() / 2;

		// For each disc in R (working backwards)
		for (int i = R.size() - 1; i >= 0; --i) // O(N)
		{
			// Determine target for the current tube (closest to average/median without going below the 'i' + 1 threshold)
			// target = average/median (offset by the current index since we'd want the average to be in the middle of the list?)
			// but clamped at:
			// 'i' + 1 < target < R[i + 1]
			int target = average + (i - iMiddle);
			target = std::max(target, i + 1);
			if (i < R.size() - 1)
			{
				target = std::min(target, R[i + 1] - 1);
			}

			secondsRequired += std::abs(R[i] - target);

			R[i] = target;
		}

		// Return the deflate counter
		return secondsRequired;
	}
};