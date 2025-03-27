// Standard
#include <iostream>

// 1st Party - My Algorithms
#include "Searching.h"
#include "Sorting.h"

// 1st Party - My Data Structures
#include "MyStack.h"
#include "MyHashSet.h"
#include "MyHashTable.h"
#include "MyBST.h"
#include "MyTrie.h"
#include "MyMinHeap.h"

// 1st Party - My random stuff
#include "AllEnglishWords.h"

// 1st Party - LeetCode Stuff
#include "TwoSum.h"
#include "AddTwoNumbers.h"

// 1st Party - Meta Puzzles Stuff
#include "Cafeteria.h"
#include "DirectorOfPhotography.h"
#include "DirectorOfPhotography2v5.h"
#include "Kaitenzushi.h"
#include "RotaryLock.h"
#include "ScoreboardInference.h"
#include "StackStabilization.h"
#include "UniformIntegers.h"
#include "Hops.h"
#include "MissingMail.h"
#include "Portals.h"
#include "RabbitHole.h"
#include "RabbitHole2v2.h"
#include "RotaryLock2.h"
#include "ScoreboardInference2.h"
#include "TunnelTime.h"
#include "BossFight.h"
#include "SlipperyTrip.h"
#include "StackStabilization2.h"

int main()
{
	/********************
	*  LeetCode Tests  *
	********************/

	// LeetCode #1: Two Sum
	std::vector<int> twoSumTestCase{ 2,7,11,15 };
	int twoSumTarget = 9;
	Solution_TwoSum twoSumSolution;
	auto twoSumResult = twoSumSolution.twoSum(twoSumTestCase, twoSumTarget);

	// LeetCode #2: Add Two Numbers
	std::vector<ListNode> addTwoNumbersNumber1{ 2, 4, 3 };
	std::vector<ListNode> addTwoNumbersNumber2{ 5, 6, 4 };
	for (int i = 0; i < 2; ++i)
	{
		addTwoNumbersNumber1[i].next = &addTwoNumbersNumber1[i + 1];
		addTwoNumbersNumber2[i].next = &addTwoNumbersNumber2[i + 1];
	}
	Solution_AddTwoNumbers addTwoNumbersSolution;
	auto addTwoNumbersResult = addTwoNumbersSolution.addTwoNumbers(&addTwoNumbersNumber1[0], &addTwoNumbersNumber2[0]);


	/***********************
	*  Meta Puzzles Tests  *
	***********************/

	// Meta Puzzle: Cafeteria
	std::vector<long long> cafeteriaOccupiedSeats{ 2, 6 };
	Solution_Cafeteria cafeteriaSolution;
	auto cafeteriaResult = cafeteriaSolution.getMaxAdditionalDinersCount(10, 1, cafeteriaOccupiedSeats.size(), cafeteriaOccupiedSeats);

	// Meta Puzzle: Director of Photography
	std::string directorOfPhotographyCells = ".PBAAP.B";
	Solution_DirectorOfPhotography directorOfPhotographySolution;
	auto directorOfPhotographyResult = directorOfPhotographySolution.getArtisticPhotographCount(directorOfPhotographyCells.size(), directorOfPhotographyCells, 1, 3);

	// Meta Puzzle: Kaitenzushi
	std::vector<int> kaitenzushiDishes{ 1, 2, 3, 3, 2, 1 };
	Solution_Kaitenzushi kaitenzushiSolution;
	auto kaitenzushiResult = kaitenzushiSolution.getMaximumEatenDishCount(kaitenzushiDishes.size(), kaitenzushiDishes, 2);

	// Meta Puzzle: Rotary Lock
	std::vector<int> rotaryLockCode{ 9, 4, 4, 8 };
	Solution_RotaryLock rotaryLockSolution;
	auto rotaryLockResult = rotaryLockSolution.getMinCodeEntryTime(10, rotaryLockCode.size(), rotaryLockCode);

	// Meta Puzzle: Scoreboard Inference
	std::vector<int> scoreboardInferenceScores{ 2, 4, 6, 8 };
	Solution_ScoreboardInference scoreboardInferenceSolution;
	auto scoreboardInferenceResult = scoreboardInferenceSolution.getMinProblemCount(scoreboardInferenceScores.size(), scoreboardInferenceScores);

	// Meta Puzzle: Stack Stabilization
	std::vector<int> stackStabilizationDiscs{ 6, 5, 4, 3 };
	Solution_StackStabilization stackStabilizationSolution;
	auto stackStabilizationResult = stackStabilizationSolution.getMinimumDeflatedDiscCount(stackStabilizationDiscs.size(), stackStabilizationDiscs);

	// Meta Puzzle: Uniform Integers
	Solution_UniformIntegers uniformIntegersSolution;
	auto uniformIntegersResult = uniformIntegersSolution.getUniformIntegerCountInInterval(1, 888'888'888'887); // Max: 1'000'000'000'000

	// Meta Puzzle: Director of Photography 2
	std::string directorOfPhotography2Cells = "B...A...P.....P";
	Solution_DirectorOfPhotography2v5 directorOfPhotography2Solution;
	auto directorOfPhotography2Result = directorOfPhotography2Solution.getArtisticPhotographCount(directorOfPhotography2Cells.size(), directorOfPhotography2Cells, 1, 300'000);

	// Meta Puzzle: Hops
	std::vector<long long> hopsFrogs{ 5, 2, 4 };
	Solution_Hops hopsSolution;
	auto hopsResult = hopsSolution.getSecondsRequired(6, hopsFrogs.size(), hopsFrogs);

	// Meta Puzzle: Missing Mail (passing 13/24 - 6 wrong answers, 5 time limited)
	std::vector<int> missingMailValues{ 10, 2, 8, 6, 4 };
	Solution_MissingMail missingMailSolution;
	auto missingMailResult = missingMailSolution.getMaxExpectedProfit(missingMailValues, 3, 0.15);

	// Meta Puzzle: Portals
	std::vector<std::vector<char>> portalsGrid3{
		{'a', 'S', '.', 'b'},
		{'#', '#', '#', '#'},
		{'E', 'b', '.', 'a'}
	};
	Solution_Portals portalsSolution;
	auto portalsResult = portalsSolution.getSecondsRequired(portalsGrid3);

	// Meta Puzzle: Rabbit Hole (passing 4/18 - 14 memory limited)
	std::vector<int> rabbitHoleLinks{ 2, 4, 2, 2, 3 };
	Solution_RabbitHole rabbitHoleSolution;
	auto rabbitHoleResult = rabbitHoleSolution.getMaxVisitableWebpages(5, rabbitHoleLinks);

	// Meta Puzzle: Rotary Lock 2 (passing 3/22 - not sure how this is not NP-Hard as it is essentially an even more complex version of TSP..?)
	std::vector<int> rotaryLock2Code{ 5, 4, 5, 4, 5, 4, 2 };
	Solution_RotaryLock2 rotaryLock2Solution;
	auto rotaryLock2Result = rotaryLock2Solution.getMinCodeEntryTime(10, rotaryLock2Code.size(), rotaryLock2Code);

	// Meta Puzzle: Scoreboard Inference 2 (passing 30/35 - 5 wrong answers)
	Solution_ScoreboardInference2 scoreboardInference2Solution;
	std::vector<int> scoreboardInference2Scores{};
	bool generateAllTestsUpToSix = true;
	if (generateAllTestsUpToSix)
	{
		for (int num6s = 0; num6s < 2; ++num6s)
		{
			for (int num5s = 0; num5s < 2; ++num5s)
			{
				for (int num4s = 0; num4s < 2; ++num4s)
				{
					for (int num3s = 0; num3s < 2; ++num3s)
					{
						for (int num2s = 0; num2s < 2; ++num2s)
						{
							for (int num1s = 0; num1s < 2; ++num1s)
							{
								// Add 1s
								for (int i = 0; i < num1s; ++i)
								{
									scoreboardInference2Scores.push_back(1);
								}

								// Add 2s
								for (int i = 0; i < num2s; ++i)
								{
									scoreboardInference2Scores.push_back(2);
								}

								// Add 3s
								for (int i = 0; i < num3s; ++i)
								{
									scoreboardInference2Scores.push_back(3);
								}

								// Add 4s
								for (int i = 0; i < num4s; ++i)
								{
									scoreboardInference2Scores.push_back(4);
								}

								// Add 5s
								for (int i = 0; i < num5s; ++i)
								{
									scoreboardInference2Scores.push_back(5);
								}

								// Add 6s
								for (int i = 0; i < num6s; ++i)
								{
									scoreboardInference2Scores.push_back(6);
								}

								// Run test
								auto scoreboardInference2Result = scoreboardInference2Solution.getMinProblemCount(scoreboardInference2Scores.size(), scoreboardInference2Scores);
								std::cout << scoreboardInference2Result << ": ";
								for (auto& score : scoreboardInference2Scores)
								{
									std::cout << score << " ";
								}
								std::cout << std::endl;

								// Clear vector
								scoreboardInference2Scores.clear();
							}
						}
					}
				}
			}
		}
	}
	scoreboardInference2Scores = { 6, 7, 8, 7, 7, 7, 7 };
	auto scoreboardInference2Result = scoreboardInference2Solution.getMinProblemCount(scoreboardInference2Scores.size(), scoreboardInference2Scores);

	// Meta Puzzle: Tunnel Time
	Solution_TunnelTime tunnelTimeSolution;
	std::vector<long long> tunnelTimeTunnelsA{ 1 };
	std::vector<long long> tunnelTimeTunnelsB{ 2 };
	auto tunnelTimeResult = tunnelTimeSolution.getSecondsElapsed(3, tunnelTimeTunnelsA, tunnelTimeTunnelsB, 1);

	// Meta Puzzle: Boss Fight (brute force approach passes 18/24 - 6 time limited)
	Solution_BossFight bossFightSolution;
	std::vector<int> bossFightWarriorHealth{ 1, 1, 2, 100 };
	std::vector<int> bossFightWarriorDamage{ 1, 2, 1,   3 };
	auto bossFightResult = bossFightSolution.getMaxDamageDealt(bossFightWarriorHealth, bossFightWarriorDamage, 8);

	// Meta Puzzle: Rabbit Hole 2 (passing 10/22 - 7 wrong answers, 5 time limited)
	//std::vector<int> rabbitHole2ListA{ 3, 2, 5, 9, 10, 3, 3, 9, 4 };
	//std::vector<int> rabbitHole2ListB{ 9, 5, 7, 8,  6, 4, 5, 3, 9 };
	//std::vector<int> rabbitHole2ListA{ 1, 2, 2, 4 }; // Bug 1 (fixed)
	//std::vector<int> rabbitHole2ListB{ 2, 1, 3, 2 }; // Bug 1 (fixed)
	std::vector<int> rabbitHole2ListA{ 1, 2, 3, 3, 4 }; // Bug #2 (expected: 5, Result: 4, Reason: Must use same link twice...)
	std::vector<int> rabbitHole2ListB{ 2, 3, 4, 5, 2 };	// Bug #2 (expected: 5, Result: 4, Reason: Must use same link twice...)
	Solution_RabbitHole2v2 rabbitHole2Solution;
	auto rabbitHole2Result = rabbitHole2Solution.getMaxVisitableWebpages(5, rabbitHole2ListA.size(), rabbitHole2ListA, rabbitHole2ListB);

	// Meta Puzzle: Slippery Trip (passing 34/35 - 1 wrong answer...)
	//std::vector<std::vector<char>> slipperyTripGrid{
	//	{'>', '*', 'v', '*', '>', '*'},
	//	{'*', 'v', '*', 'v', '>', '*'},
	//	{'.', '*', '>', '.', '.', '*'},
	//	{'.', '*', '.', '.', '*', 'v'}
	//};
	std::vector<std::vector<char>> slipperyTripGrid{
		{'*', 'v', '*', '>'},
		{'*', '*', '>', 'v'},
		{'*', '*', '>', '.'},
	};
	Solution_SlipperyTrip slipperyTripSolution;
	auto slipperyTripResult = slipperyTripSolution.getMaxCollectableCoins(slipperyTripGrid);

	// Meta Puzzle: Stack Stabilization 2
	std::vector<int> stackStabilization2Discs{ 2, 5, 3, 6, 5 };
	Solution_StackStabilization2 stackStabilization2Solution;
	auto stackStabilization2Result = stackStabilization2Solution.getMinimumSecondsRequired(stackStabilization2Discs, 1, 1);

	return 0;
}