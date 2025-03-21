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
		bool forcedLoop = false; // You WILL be FORCED into a loop
	};

private:
	RowInfo getRowInfo(std::vector<char>& row)
	{
		// Initialize the row info
		RowInfo rowInfo{};
		rowInfo.forcedLoop = true;

		// Helpful temporary data while info gathering
		bool aRightArrowExists = false;
		bool aDownArrowExists = false;
		bool collecting = false;
		int currentSidewaysCoins = 0;
		int startSidewaysCoins = 0;

		// For each character in the row
		for (char& c : row)
		{
			switch (c)
			{
			case '.':
				// We know that the row isn't a forced loop (all right arrows)
				rowInfo.forcedLoop = false;
				break;

			case '*':
				// Add to the total number of coins in the row
				rowInfo.numCoins++;

				// If we're currently collecting coins (between a right arrow and a down arrow), keep track of that amount
				if (collecting)
				{
					currentSidewaysCoins++;
				}
				else if (aDownArrowExists == false)
				{
					// If we're not collecting but haven't seen a down arrow yet, keep track of the coins because there might be a wrapped sideways path
					startSidewaysCoins++;
				}

				// We know that the row isn't a forced loop (all right arrows)
				rowInfo.forcedLoop = false;
				break;

			case 'v':
				// Flag that we have seen a down arrow
				aDownArrowExists = true;

				// Collect the current sideways coins collected (keep track of the max possible)
				if (collecting)
				{
					rowInfo.numCoinsSidewaysCollectable = std::max(rowInfo.numCoinsSidewaysCollectable, currentSidewaysCoins);
					currentSidewaysCoins = 0;
				}

				// Turn off our sideways coin collecting (until we see another right arrow)
				collecting = false;

				// We know that the row isn't a forced loop (all right arrows)
				rowInfo.forcedLoop = false;
				break;

			case '>':
				// Flag that we have seen a right arrow
				aRightArrowExists = true;

				// IF we've seen a down arrow
				if (aDownArrowExists)
				{
					// Turn on our sideways coin collecting (until we see another down arrow)
					collecting = true; // FYI: If we have't seen a down arrow, the coins will be captured as "startSidewaysCoins" to be dealt with at the end
				}
				break;

			default:
				// Invalid character... this should never get hit!
				break;
			}
		}

		// Check for loops and sideways paths
		if (aRightArrowExists && !aDownArrowExists)
		{
			// A loop is contained (could be forced or not)
			rowInfo.containsLoop = true;
		}
		else if (aRightArrowExists && aDownArrowExists)
		{
			// There is a sideways path, account for possible wrapped sideways coins (must end while collecting)
			if (collecting)
			{
				rowInfo.numCoinsSidewaysCollectable = std::max(rowInfo.numCoinsSidewaysCollectable, currentSidewaysCoins + startSidewaysCoins);
			}
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

			// Check for loops
			if (rowInfo.forcedLoop)
			{
				// If the row forces you into an infinite loop, break out immediately because we're now done
				break;
			}
			else if (rowInfo.containsLoop)
			{
				// If the row contains an optional loop, update the max looping coins if we were to choose to do so here
				maxCoinsIfLooping = std::max(maxCoinsIfLooping, coinsCollected + rowInfo.numCoins);
			}

			// Continue checking other scenarios...
			if (rowInfo.numCoinsSidewaysCollectable > 0)
			{
				// If the row contains a valid sideways path, collect the max number of those coins and move on to the next row
				coinsCollected += rowInfo.numCoinsSidewaysCollectable;
			}
			else if (rowInfo.numCoins > 0)
			{
				// With no valid sideways path, the max number of coins we can grab is 1 (assuming there are any coins in the row)
				coinsCollected += 1;
			}
			else
			{
				// The row has no coins, so no coins can be collected and we just move on to the next row...
			}
		}

		// Return either the coins collected if continuing to the end, OR the max found if chosen to stop in a row and loop forever (whichever is more)
		return std::max(coinsCollected, maxCoinsIfLooping);
	}
};