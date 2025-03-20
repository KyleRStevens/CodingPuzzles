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

class Solution_BossFight
{
private:
	struct Warrior
	{
		int health = 0;
		int damagePerSecond = 0;
	};

public:
	double getMaxDamageDealt(std::vector<int>& H, std::vector<int>& D, int B)
	{
		double maxDamageDealt = 0;

		//Warrior warrior1{};
		//Warrior warrior2{};

		// Test every combination of warriors (exhaustive, brute-force approach)
		for (int i = 0; i < H.size(); ++i)
		{
			for (int j = i + 1; j < H.size(); ++j)
			{
				Warrior recruit1{ H[i], D[i] };
				Warrior recruit2{ H[j], D[j] };
				
				double option1 = ((recruit1.health + recruit2.health) * recruit1.damagePerSecond) + (recruit2.health * recruit2.damagePerSecond);
				double option2 = ((recruit1.health + recruit2.health) * recruit2.damagePerSecond) + (recruit1.health * recruit1.damagePerSecond);

				double betterOption = std::max(option1, option2);
				maxDamageDealt = std::max(maxDamageDealt, betterOption);
			}
		}

		// Take into account the boss's DPS
		maxDamageDealt /= B;

		// Return the best possible outcome
		return maxDamageDealt;
	}
};