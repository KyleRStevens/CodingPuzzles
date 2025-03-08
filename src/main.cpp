// Standard
#include <iostream>

// 1st Party - My Data Structures
#include "MyStack.h"
#include "MyHashSet.h"
#include "MyHashTable.h"

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

	// MyHashSet test
	MyHashSet<int> numbersHash(100);
	numbersHash.Insert(14);
	numbersHash.Insert(12);
	numbersHash.Insert(29);
	numbersHash.Insert(86);
	numbersHash.Insert(14);
	numbersHash.Remove(29);
	numbersHash.Remove(14);
	numbersHash.Remove(99);

	// MyHashTable test
	enum class Color
	{
		UNINITIALIZED,
		RED,
		ORANGE,
		YELLOW,
		GREEN,
		BLUE
	};
	MyHashTable<int, Color> colorsHash(20);
	colorsHash.Insert(1, Color::BLUE);
	colorsHash.Insert(2, Color::RED);
	colorsHash.Insert(3, Color::YELLOW);
	colorsHash.GetValue(2);
	colorsHash.Remove(2);
	colorsHash.GetValue(2);

	return 0;
}