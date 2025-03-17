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

class Solution_MissingMail
{
public:
	double getMaxExpectedProfit(std::vector<int>& values, int costToEnter, double probOfSteal) // O(N)
	{
		bool yesterdayWasCollected = true; // Start as true because on day 1, there is no package from yesterday (same as if collected)
		double currentProfit = 0.0;
		double yesterdaysExpectedValueFromNotCollecting = 0.0;
		double runningUncollectedValues = 0.0;

		// For each day
		for (int day = 0; day < values.size() - 1; ++day) // O(N)
		{
			// Get tomorrow's expected value if collecting today
			double tommorrowsExpectedValueIfCollecting = (values[day] - costToEnter) + (values[day + 1] - costToEnter);

			// Get tomorrow's expected value if NOT collecting today
			double tommorrowsExpectedValueIfNotCollecting = ((1 - probOfSteal) * (runningUncollectedValues + values[day])) + values[day + 1] - costToEnter;
			runningUncollectedValues += (1 - probOfSteal) * values[day];

			// Decide action based on which is higher
			bool weAreCollecting = tommorrowsExpectedValueIfCollecting >= tommorrowsExpectedValueIfNotCollecting;

			// If collecting:
			if (weAreCollecting)
			{
				// If yesterday WAS collected:
				if (yesterdayWasCollected)
				{
					// Add in the current collection profit (todays box - C)
					currentProfit += (values[day] - costToEnter);
				}
				else // Yesterday was NOT collected
				{
					// Use yesterday's not-collecting expected value to add to running total profit
					currentProfit += yesterdaysExpectedValueFromNotCollecting;
				}

				// If collecting, reset the running total of uncollected values
				runningUncollectedValues = 0;
			}

			// Save todays necessary info for tomorrow
			yesterdayWasCollected = weAreCollecting;
			yesterdaysExpectedValueFromNotCollecting = tommorrowsExpectedValueIfNotCollecting;
		}

		// Factor in last day
		{
			double profitFromCollecting = runningUncollectedValues + values[values.size() - 1] - costToEnter;
			if (profitFromCollecting > 0)
			{
				currentProfit += profitFromCollecting;
			}
		}

		// Write your code here
		return currentProfit;
	}
};