// Standard
#include <iostream>

// 1st Party - My Data Structures
#include "MyStack.h"

// 1st Party - LeetCode Stuff
#include "TwoSum.h"
#include "AddTwoNumbers.h"

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

	// MyStack test
	MyStack<int> numberStack(5);
	numberStack.Push(1);
	numberStack.Push(2);
	numberStack.Push(3);
	numberStack.Push(4);
	numberStack.Push(5);
	numberStack.Push(6);
	std::cout << numberStack.Pop() << std::endl;

	return 0;
}