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

// 1st Party - LeetCode Stuff
#include "TwoSum.h"
#include "AddTwoNumbers.h"

// 1st Party - Meta Puzzles Stuff
#include "RabbitHole2.h"
#include "RabbitHole2v2.h"

int main()
{
	// 1: Two Sum
	std::vector<int> twoSumTestCase{ 2,7,11,15 };
	int twoSumTarget = 9;
	Solution_TwoSum twoSumSolution;
	auto twoSumResult = twoSumSolution.twoSum(twoSumTestCase, twoSumTarget);

	// 2: Add Two Numbers
	std::vector<ListNode> addTwoNumbersNumber1{ 2, 4, 3 };
	std::vector<ListNode> addTwoNumbersNumber2{ 5, 6, 4 };
	for (int i = 0; i < 2; ++i)
	{
		addTwoNumbersNumber1[i].next = &addTwoNumbersNumber1[i + 1];
		addTwoNumbersNumber2[i].next = &addTwoNumbersNumber2[i + 1];
	}
	Solution_AddTwoNumbers addTwoNumbersSolution;
	auto addTwoNumbersResult = addTwoNumbersSolution.addTwoNumbers(&addTwoNumbersNumber1[0], &addTwoNumbersNumber2[0]);

	// Meta Puzzle: Rabbit Hole 2 (Currently passing 12/22 test cases...)
	//std::vector<int> rabbitHole2ListA{ 3, 2, 5, 9, 10, 3, 3, 9, 4 };
	//std::vector<int> rabbitHole2ListB{ 9, 5, 7, 8,  6, 4, 5, 3, 9 };
	std::vector<int> rabbitHole2ListA{ 3 };
	std::vector<int> rabbitHole2ListB{ 5 };
	Solution_RabbitHole2v2 rabbitHole2Solution;
	auto rabbitHole2Result = rabbitHole2Solution.getMaxVisitableWebpages(0, 1, rabbitHole2ListA, rabbitHole2ListB);

	return 0;
}