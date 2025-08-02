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

// Meta Puzzle: Missing Mail
class Solution_MissingMail
{
private:
	double getTableValue(std::vector<int>& values, int day, int packageIndex, double probOfSteal, int costToEnter)
	{
		double sum = 0;

		// For each iDay from the day given through the last day
		for (int iPackage = packageIndex; iPackage <= day; ++iPackage)
		{
			// Add in the cumulative expected value of each item from the given day onward
			sum += (values[iPackage] * std::pow((1 - probOfSteal), day - iPackage));
		}

		return sum - costToEnter;
	}

public:
	double getMaxExpectedProfit(std::vector<int>& values, int costToEnter, double probOfSteal) // O(N)
	{
		double currentProfit = 0;

		std::vector<std::vector<double>> table;
		table.resize(values.size());

		// For N iterations
		for (int i = 0; i < values.size(); ++i) // O(N) => O(N^2)
		{
			// For 'i' (the current value of N) days, starting from the last day
			for (int j = 0; j <= i; ++j) // O(N)
			{
				int day = values.size() - 1 - j;
				int packageIndex = values.size() - 1 - i;

				double currentValue = getTableValue(values, day, packageIndex, probOfSteal, costToEnter);
				table[i].push_back(currentValue);
			}
		}

		// For each row in the table...
		int row = 0;
		int prevCol = -1;
		while (row < table.size() - 1)
		{
			// A = the last entry in row 'i'
			int lastColInThisRow = table[row].size() - 1;
			if (prevCol != -1)
			{
				lastColInThisRow = prevCol;
			}
			double A = table[row][lastColInThisRow];

			// B = the last entry in row 'i+1'
			int lastColInNextRow = table[row + 1].size() - 1;
			double B = table[row + 1][lastColInNextRow];
				
			// If A + B >= row of 'B', col of 'A'
			if (A + B >= table[row + 1][lastColInThisRow])
			{
				// Add A to total profit if positve
				if (A > 0)
				{
					currentProfit += A;
				}

				// Reset the prevCol
				prevCol = -1;
			}
			else
			{
				// Use prevCol in next A instead of the last col of the row
				prevCol = lastColInThisRow;
			}

			// Move to next row
			row++;
		}

		// Include the last row
		if (prevCol != -1)
		{
			// Only add to profit if the value is positive?
			if (table[row][prevCol] > 0)
			{
				currentProfit += table[row][prevCol];
			}
		}
		else
		{
			// Only add to profit if the value is positive?
			if (table[row][table[row].size() - 1] > 0)
			{
				currentProfit += table[row][table[row].size() - 1];
			}
		}

		// Return the summed max profit
		return currentProfit;
	}

	void Test()
	{
		std::vector<int> missingMailValues{ 10, 2, 8, 6, 4 };
		auto missingMailResult = getMaxExpectedProfit(missingMailValues, 3, 0.15);
	}
};