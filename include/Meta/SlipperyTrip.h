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

class Solution_SlipperyTrip
{
private:
	struct RowInfo
	{
		int numCoins = 0; // Total coins in the row (the number you'll get if you loop)
		int numCoinsSidewaysCollectable = 0; // The number of coins you could collect between a right arrow and a down arrow
		bool containsLoop = false; // You CAN loop if you want
		bool allRight = false; // You WILL be FORCED into a loop
	};

private:
	RowInfo getRowInfo(std::vector<char>& row)
	{
		RowInfo rowInfo{};
		rowInfo.allRight = true;

		bool isRightArrow = false;
		bool isDownArrow = false;
		bool collecting = false;
		int currentSidewaysCoins = 0;
		int startSidewaysCoins = 0;

		// For each character in the row
		for (char& c : row)
		{
			switch (c)
			{
			case '.':
				// We know that the row isn't all right arrows
				rowInfo.allRight = false;
				break;

			case '*':
				// Add to the total number of coins in the row
				rowInfo.numCoins++;

				// If we're collecting coins (between a right arrow and a down arrow), keep track of that amount
				if (collecting)
				{
					currentSidewaysCoins++;
				}
				else if (isDownArrow == false)
				{
					// If we're not collecting but haven't seen a down arrow yet, keep track of the coins because there might be a wrapped sideways path
					startSidewaysCoins++;
				}

				// We know that the row isn't all right arrows
				rowInfo.allRight = false;
				break;

			case 'v':
				// Flag that we have seen a down arrow
				isDownArrow = true;

				// Collect the current sideways coins collected (keep track of the max possible)
				if (collecting)
				{
					rowInfo.numCoinsSidewaysCollectable = std::max(rowInfo.numCoinsSidewaysCollectable, currentSidewaysCoins);
					currentSidewaysCoins = 0;
				}

				// Turn off our sideways coin collecting (until we see another right arrow)
				collecting = false;

				// We know that the row isn't all right arrows
				rowInfo.allRight = false;
				break;

			case '>':
				// Flag that we have seen a right arrow
				isRightArrow = true;

				// IF we've seen a down arrow
				if (isDownArrow)
				{
					// Turn on our sideways coin collecting (until we see another down arrow)
					collecting = true;
				}
				break;

			default:
				// Invalid character... this should never get hit!
				break;
			}
		}

		// Check for loops and sideways paths
		if (isRightArrow && !isDownArrow)
		{
			// A loop is contained (could be forced or not)
			rowInfo.containsLoop = true;
		}
		else if (isRightArrow && isDownArrow)
		{
			// There is a sideways path, account for possible wrapped sideways coins
			rowInfo.numCoinsSidewaysCollectable = std::max(rowInfo.numCoinsSidewaysCollectable, currentSidewaysCoins + startSidewaysCoins);
		}

		// Return the gathered info
		return rowInfo;
	}

public:
	int getMaxCollectableCoins(std::vector<std::vector<char>>& G)
	{
		int coinsCollected = 0;
		int maxCoinsIfLooping = 0;

		// For each row, you can collect at most this many coins:
		// If the row contains a right arrow, but NOT a down arrow, save the amount of total coins in the row to max loopable
		// If the row contains at least 1 right arrow and at least 1 down arrow, the max number of coins between the right arrow and the down arrow (moving right only)
		// Else if the row contains at least 1 coin, you can at most collect 1 coin
		// Else if row is all right arrows, break
		// Else 0

		// For each row
		for (int row = 0; row < G.size(); ++row)
		{
			RowInfo rowInfo = getRowInfo(G[row]);

			// If the row contains a right arrow, but NOT a down arrow, update the max looping coins if we were to choose to do so here
			if (rowInfo.containsLoop)
			{
				maxCoinsIfLooping = std::max(maxCoinsIfLooping, coinsCollected + rowInfo.numCoins);
			}

			// Continue checking other scenarios...
			if (rowInfo.numCoinsSidewaysCollectable > 0)
			{
				// If the row contains at least 1 right arrow and at least 1 down arrow, the max number of coins between the right arrow and the down arrow (moving right only)
				coinsCollected += rowInfo.numCoinsSidewaysCollectable;
			}
			else if (rowInfo.numCoins > 0)
			{
				// Else if the row contains at least 1 coin, you can at most collect 1 coin
				coinsCollected += 1;
			}
			else if (rowInfo.allRight)
			{
				// Else if row is all right arrows, break out of the loop because we're forced to be done here
				break;
			}
			else
			{
				// Else, no coins can be collected in this row, move on to the next row...
			}
		}

		// Return either the coins collected if continuing to the end, OR the max found if chosen to stop in a row and loop forever (whichever is more)
		return std::max(coinsCollected, maxCoinsIfLooping);
	}
};