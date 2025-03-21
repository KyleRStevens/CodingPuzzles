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
		double multiplier() { return health * damagePerSecond; }

		double health = 0;
		double damagePerSecond = 0;

		int originalIndex = -1; // Useful for identifying unique warriors after being sorted
	};

private:
	double bruteForceStrategy(std::vector<int>& H, std::vector<int>& D, int B) // O(N^2)
	{
		double maxDamageDealt = 0;

		for (int i = 0; i < H.size(); ++i) // O(N) => O(N^2)
		{
			for (int j = i + 1; j < H.size(); ++j) // O(N)
			{
				Warrior recruit1{ static_cast<double>(H[i]), static_cast<double>(D[i]) };
				Warrior recruit2{ static_cast<double>(H[j]), static_cast<double>(D[j]) };

				// Recruit 1 in back
				double option1 = ((recruit1.health + recruit2.health) * recruit1.damagePerSecond) + (recruit2.health * recruit2.damagePerSecond);

				// Recruit 2 in back
				double option2 = ((recruit1.health + recruit2.health) * recruit2.damagePerSecond) + (recruit1.health * recruit1.damagePerSecond);

				// Choose the better configuration option and update the best overall if necessary
				double betterOption = std::max(option1, option2);
				maxDamageDealt = std::max(maxDamageDealt, betterOption);
			}
		}

		return maxDamageDealt;
	}

	double bruteForceWithPruningStrategy(std::vector<int>& H, std::vector<int>& D, int B) // O(N^2)
	{
		double maxDamageDealt = 0;

		std::vector<Warrior> prunedList;
		std::vector<Warrior> prunedList2;

		Warrior bestOverall1{};
		Warrior bestOverall2{};

		// Save warriors to a container (however, if both stats are worse than 2 other warrior's stats, we know it is impossible for them to be a top candidate, so don't include them)
		for (int i = 0; i < H.size(); ++i) // O(N)
		{
			// Update top overall warriors if necessary
			if (H[i] >= bestOverall2.health && D[i] >= bestOverall2.damagePerSecond)
			{
				if (H[i] >= bestOverall1.health && D[i] >= bestOverall1.damagePerSecond)
				{
					bestOverall2 = bestOverall1;

					bestOverall1.health = H[i];
					bestOverall1.damagePerSecond = D[i];
					bestOverall1.originalIndex = i;
				}
				else
				{
					bestOverall2.health = H[i];
					bestOverall2.damagePerSecond = D[i];
					bestOverall2.originalIndex = i;
				}
			}

			// Add warrior to our pruned list if it is higher in at least 1 stat than our current second best overall warrior
			if (H[i] > bestOverall1.health || D[i] > bestOverall1.damagePerSecond || H[i] > bestOverall2.health || D[i] > bestOverall2.damagePerSecond)
			{
				prunedList.emplace_back(static_cast<double>(H[i]), static_cast<double>(D[i]), i);
			}
		}

		// Prune this list again now that we have the 2 best overall warriors right from the start
		for (int i = 0; i < prunedList.size(); ++i) // O(N)
		{
			// Add warrior to our new pruned list if it is higher in at least 1 stat than our current second best overall warrior
			if (prunedList[i].health > bestOverall1.health || prunedList[i].damagePerSecond > bestOverall1.damagePerSecond || prunedList[i].health > bestOverall2.health || prunedList[i].damagePerSecond > bestOverall2.damagePerSecond)
			{
				prunedList2.emplace_back(prunedList[i]);
			}
		}
		
		prunedList.clear();

		// Now do the brute force approach through the pruned list
		for (int i = 0; i < prunedList2.size(); ++i) // O(N) => O(N^2)
		{
			for (int j = i + 1; j < prunedList2.size(); ++j) // O(N)
			{
				Warrior& recruit1 = prunedList2[i];
				Warrior& recruit2 = prunedList2[j];

				// Recruit 1 in back
				double option1 = ((recruit1.health + recruit2.health) * recruit1.damagePerSecond) + (recruit2.health * recruit2.damagePerSecond);

				// Recruit 2 in back
				double option2 = ((recruit1.health + recruit2.health) * recruit2.damagePerSecond) + (recruit1.health * recruit1.damagePerSecond);

				// Choose the better configuration option and update the best overall if necessary
				double betterOption = std::max(option1, option2);
				maxDamageDealt = std::max(maxDamageDealt, betterOption);
			}
		}

		return maxDamageDealt;
	}

	double largestMultiplierStrategy(std::vector<int>& H, std::vector<int>& D, int B) // O(N)
	{
		double maxDamageDealt = 0;

		Warrior warrior1{};
		Warrior warrior2{};

		// Get the warriors with the 2 maximum multipliers
		for (int i = 0; i < H.size(); ++i) // O(N)
		{
			double multiplier = H[i] * D[i];
			if (multiplier > warrior2.multiplier())
			{
				if (multiplier > warrior1.multiplier())
				{
					warrior2 = warrior1;
					
					warrior1.health = H[i];
					warrior1.damagePerSecond = D[i];
				}
				else
				{
					warrior2.health = H[i];
					warrior2.damagePerSecond = D[i];
				}
			}
		}

		// Test which configuration they are better in
		double option1 = ((warrior1.health + warrior2.health) * warrior1.damagePerSecond) + (warrior2.health * warrior2.damagePerSecond);
		double option2 = ((warrior1.health + warrior2.health) * warrior2.damagePerSecond) + (warrior1.health * warrior1.damagePerSecond);

		// Choose the better configuration option
		maxDamageDealt = std::max(option1, option2);

		return maxDamageDealt;
	}

	double largestCrossMultiplierStrategy(std::vector<int>& H, std::vector<int>& D, int B) // O(N*logN)
	{
		double maxDamageDealt = 0;

		Warrior warrior1{};
		Warrior warrior2{};

		// Put all warriors into a container
		std::vector<Warrior> warriors;
		warriors.resize(H.size());
		for (int i = 0; i < H.size(); ++i) // O(N)
		{
			warriors[i].health = H[i];
			warriors[i].damagePerSecond = D[i];
			warriors[i].originalIndex = i;
		}

		// Sort the container by health
		auto sortByHealth = [](Warrior& A, Warrior& B) { return A.health > B.health; };
		std::sort(warriors.begin(), warriors.end(), sortByHealth); // O(N*logN)

		// Save the 2 warriors with the highest health
		Warrior topHealth1 = warriors[0];
		Warrior topHealth2 = warriors[1];

		// Sort the container by damage
		auto sortByDamage = [](Warrior& A, Warrior& B) { return A.damagePerSecond > B.damagePerSecond; };
		std::sort(warriors.begin(), warriors.end(), sortByDamage); // O(N*logN)

		// Save the 2 warriors with the highest health
		Warrior topDamage1 = warriors[0];
		Warrior topDamage2 = warriors[1];

		// Check if the top health and top damage warrior are the same warrior
		if (topHealth1.originalIndex == topDamage1.originalIndex)
		{
			Warrior& topWarrior = topHealth1;

			// If they're the same person, we have to figure out the better second (this is why we saved 2 of each), and their configuration
			double option1 = ((topWarrior.health + topHealth2.health) * topWarrior.damagePerSecond) + (topHealth2.health * topHealth2.damagePerSecond);
			double option2 = ((topWarrior.health + topHealth2.health) * topHealth2.damagePerSecond) + (topWarrior.health * topWarrior.damagePerSecond);
			double option3 = ((topWarrior.health + topDamage2.health) * topWarrior.damagePerSecond) + (topDamage2.health * topDamage2.damagePerSecond);
			double option4 = ((topWarrior.health + topDamage2.health) * topDamage2.damagePerSecond) + (topWarrior.health * topWarrior.damagePerSecond);

			maxDamageDealt = std::max(option1, option2);
			maxDamageDealt = std::max(option3, maxDamageDealt);
			maxDamageDealt = std::max(option4, maxDamageDealt);
		}
		else
		{
			// If they're different warriors, we have our answer
			maxDamageDealt = ((topHealth1.health + topDamage1.health) * topDamage1.damagePerSecond) + (topHealth1.health * topHealth1.damagePerSecond);
		}

		return maxDamageDealt;
	}

	double betterLargestCrossMultiplierStrategy(std::vector<int>& H, std::vector<int>& D, int B) // O(N)
	{
		double maxDamageDealt = 0;

		Warrior topHealth1{};
		Warrior topHealth2{};
		Warrior topDamage1{};
		Warrior topDamage2{};

		// Get the 2 maximum health warriors and the 2 maximum damage warriors
		for (int i = 0; i < H.size(); ++i) // O(N)
		{
			double health = H[i];
			double damage = D[i];

			// Update top health warriors if necessary
			if (health > topHealth2.health)
			{
				if (health > topHealth1.health)
				{
					topHealth2 = topHealth1;

					topHealth1.health = health;
					topHealth1.damagePerSecond = damage;
					topHealth1.originalIndex = i;
				}
				else
				{
					topHealth2.health = health;
					topHealth2.damagePerSecond = damage;
					topHealth2.originalIndex = i;
				}
			}

			// Update top damage warriors if necessary
			if (damage > topDamage2.damagePerSecond)
			{
				if (damage > topDamage1.damagePerSecond)
				{
					topDamage2 = topDamage1;

					topDamage1.health = health;
					topDamage1.damagePerSecond = damage;
					topDamage1.originalIndex = i;
				}
				else
				{
					topDamage2.health = health;
					topDamage2.damagePerSecond = damage;
					topDamage2.originalIndex = i;
				}
			}
		}

		// Check if the top health and top damage warrior are the same warrior
		if (topHealth1.originalIndex == topDamage1.originalIndex)
		{
			Warrior& topWarrior = topHealth1;

			// If they're the same person, we have to figure out the better second (this is why we saved 2 of each), and their configuration
			double option1 = ((topWarrior.health + topHealth2.health) * topWarrior.damagePerSecond) + (topHealth2.health * topHealth2.damagePerSecond);
			double option2 = ((topWarrior.health + topHealth2.health) * topHealth2.damagePerSecond) + (topWarrior.health * topWarrior.damagePerSecond);
			double option3 = ((topWarrior.health + topDamage2.health) * topWarrior.damagePerSecond) + (topDamage2.health * topDamage2.damagePerSecond);
			double option4 = ((topWarrior.health + topDamage2.health) * topDamage2.damagePerSecond) + (topWarrior.health * topWarrior.damagePerSecond);

			maxDamageDealt = std::max(option1, option2);
			maxDamageDealt = std::max(option3, maxDamageDealt);
			maxDamageDealt = std::max(option4, maxDamageDealt);
		}
		else
		{
			// If they're different warriors, we have our answer
			maxDamageDealt = ((topHealth1.health + topDamage1.health) * topDamage1.damagePerSecond) + (topHealth1.health * topHealth1.damagePerSecond);
		}

		return maxDamageDealt;
	}

public:
	double getMaxDamageDealt(std::vector<int>& H, std::vector<int>& D, int B)
	{
		double maxDamageDealt = 0;

		//Warrior warrior1{};
		//Warrior warrior2{};

		// Strategy 1: Test every combination of warriors (exhaustive, brute-force approach)
		//maxDamageDealt = bruteForceStrategy(H, D, B); // Passes 18/24 - 6 time limited

		// Strategy 2: Find the max multiplier (issue: you want a combo of damage and health - if the two warriors are both stacked with the same stat, it won't be as effective even if their multipliers are the highest)
		//maxDamageDealt = largestMultiplierStrategy(H, D, B);

		// Strategy 3: Find the max cross multiplier (instead of multiplying the warrior's own stats, multiply with the other warriors' opposite stats)
		//maxDamageDealt = largestCrossMultiplierStrategy(H, D, B);

		// Strategy 4: Same as above but done in O(N) time instead of O(N*logN)
		//maxDamageDealt = betterLargestCrossMultiplierStrategy(H, D, B); // Passes 10/24 - 14 wrong answers

		// Strategy 5: Same as brute-force approach except we prune out warrior candidates we KNOW won't be a good choice first before doing the O(N^2) brute-force operation
		maxDamageDealt = bruteForceWithPruningStrategy(H, D, B); // Not sure if this is really worth it...

		// Take into account the boss's DPS
		maxDamageDealt /= B;

		// Return the best possible outcome
		return maxDamageDealt;
	}
};