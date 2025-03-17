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

	// Meta Puzzle: Missing Mail
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

	// Meta Puzzle: Rabbit Hole
	std::vector<int> rabbitHoleLinks{ 2, 4, 2, 2, 3 };
	Solution_RabbitHole rabbitHoleSolution;
	auto rabbitHoleResult = rabbitHoleSolution.getMaxVisitableWebpages(5, rabbitHoleLinks);


	// Meta Puzzle: Rabbit Hole 2 (passing 10/22 - 7 wrong answers, 5 time limited)
	//std::vector<int> rabbitHole2ListA{ 3, 2, 5, 9, 10, 3, 3, 9, 4 };
	//std::vector<int> rabbitHole2ListB{ 9, 5, 7, 8,  6, 4, 5, 3, 9 };
	//std::vector<int> rabbitHole2ListA{ 1, 2, 2, 4 }; // Bug 1 (fixed)
	//std::vector<int> rabbitHole2ListB{ 2, 1, 3, 2 }; // Bug 1 (fixed)
	std::vector<int> rabbitHole2ListA{ 1, 2, 3, 3, 4 }; // Bug #2 (expected: 5, Result: 4, Reason: Must use same link twice...)
	std::vector<int> rabbitHole2ListB{ 2, 3, 4, 5, 2 };	// Bug #2 (expected: 5, Result: 4, Reason: Must use same link twice...)
	Solution_RabbitHole2v2 rabbitHole2Solution;
	auto rabbitHole2Result = rabbitHole2Solution.getMaxVisitableWebpages(5, rabbitHole2ListA.size(), rabbitHole2ListA, rabbitHole2ListB);

	return 0;
}