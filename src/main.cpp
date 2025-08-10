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
#include "LongestSubstringWithoutRepeatingCharacters.h"
#include "MedianOfTwoSortedArrays.h"
#include "LongestPalindromicSubstring.h"
#include "ZigzagConversion.h"
#include "LetterCombinationsOfAPhoneNumber.h"
#include "FourSum.h"

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
	std::cout << "Begin tests" << std::endl;

	/***********************
	*  Random Other Tests  *
	***********************/

	// Creates a Trie with all English words and uses that to do some word searching (disabled because it takes a while)
	//AllEnglishWords test;
	//test.Test();


	/********************
	*   LeetCode Tests  *
	********************/

	// LeetCode #1: Two Sum
	Solution_TwoSum twoSumSolution;
	twoSumSolution.Test();

	// LeetCode #2: Add Two Numbers
	Solution_AddTwoNumbers addTwoNumbersSolution;
	addTwoNumbersSolution.Test();

	// LeetCode #3: Longest Substring Without Repeating Characters
	Solution_LongestSubstringWithoutRepeatingCharacters longestSubstringWithoutRepeatingCharactersSolution;
	longestSubstringWithoutRepeatingCharactersSolution.Test();

	// LeetCode #4: Median Of Two Sorted Arrays
	Solution_MedianOfTwoSortedArrays medianOfTwoSortedArraysSolution;
	medianOfTwoSortedArraysSolution.Test();

	// LeetCode #5: Longest Palindromic Substring
	Solution_LongestPalindromicSubstring longestPalindromicSubstringSolution;
	longestPalindromicSubstringSolution.Test();

	// LeetCode #6: Zigzag Conversion
	Solution_ZigzagConversion zigzagConversionSolution;
	zigzagConversionSolution.Test();

	// LeetCode #17: Letter Combinations Of A Phone Number
	Solution_LetterCombinationsOfAPhoneNumber letterCombinationsOfAPhoneNumberSolution;
	letterCombinationsOfAPhoneNumberSolution.Test();

	// LeetCode #18: Four Sum
	Solution_FourSum fourSumSolution;
	fourSumSolution.Test();


	/***********************
	*  Meta Puzzles Tests  *
	***********************/

	// Meta Puzzle: Cafeteria
	Solution_Cafeteria cafeteriaSolution;
	cafeteriaSolution.Test();

	// Meta Puzzle: Director of Photography
	Solution_DirectorOfPhotography directorOfPhotographySolution;
	directorOfPhotographySolution.Test();

	// Meta Puzzle: Kaitenzushi
	Solution_Kaitenzushi kaitenzushiSolution;
	kaitenzushiSolution.Test();

	// Meta Puzzle: Rotary Lock
	Solution_RotaryLock rotaryLockSolution;
	rotaryLockSolution.Test();

	// Meta Puzzle: Scoreboard Inference
	Solution_ScoreboardInference scoreboardInferenceSolution;
	scoreboardInferenceSolution.Test();

	// Meta Puzzle: Stack Stabilization
	Solution_StackStabilization stackStabilizationSolution;
	stackStabilizationSolution.Test();

	// Meta Puzzle: Uniform Integers
	Solution_UniformIntegers uniformIntegersSolution;
	uniformIntegersSolution.Test();

	// Meta Puzzle: Director of Photography 2
	Solution_DirectorOfPhotography2v5 directorOfPhotography2Solution;
	directorOfPhotography2Solution.Test();

	// Meta Puzzle: Hops
	Solution_Hops hopsSolution;
	hopsSolution.Test();

	// Meta Puzzle: Missing Mail (passing 13/24 - 6 wrong answers, 5 time limited)
	Solution_MissingMail missingMailSolution;
	missingMailSolution.Test();

	// Meta Puzzle: Portals
	Solution_Portals portalsSolution;
	portalsSolution.Test();

	// Meta Puzzle: Rabbit Hole (passing 5/18 - 10 time limited, 3 memory limited)
	Solution_RabbitHole rabbitHoleSolution;
	rabbitHoleSolution.Test();

	// Meta Puzzle: Rotary Lock 2 (passing 3/22 - not sure how this is not NP-Hard as it is essentially an even more complex version of the traveling salesman problem..?)
	Solution_RotaryLock2 rotaryLock2Solution;
	rotaryLock2Solution.Test();

	// Meta Puzzle: Scoreboard Inference 2 (passing 30/35 - 5 wrong answers)
	Solution_ScoreboardInference2 scoreboardInference2Solution;
	scoreboardInference2Solution.Test();

	// Meta Puzzle: Tunnel Time
	Solution_TunnelTime tunnelTimeSolution;
	tunnelTimeSolution.Test();

	// Meta Puzzle: Boss Fight (brute force approach passes 18/24 - 6 time limited)
	Solution_BossFight bossFightSolution;
	bossFightSolution.Test();

	// Meta Puzzle: Rabbit Hole 2 (passing 10/22 - 7 wrong answers, 5 time limited)
	Solution_RabbitHole2v2 rabbitHole2Solution;
	rabbitHole2Solution.Test();

	// Meta Puzzle: Slippery Trip (passing 34/35 - 1 wrong answer...)
	Solution_SlipperyTrip slipperyTripSolution;
	slipperyTripSolution.Test();

	// Meta Puzzle: Stack Stabilization 2
	Solution_StackStabilization2 stackStabilization2Solution;
	stackStabilization2Solution.Test();

	return 0;
}