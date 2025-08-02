#pragma once

// Standard
#include <vector>
#include <iostream>
#include <unordered_set>
#include <set>
#include <stack>
#include <cstdint>
#include <map>
#include <mutex>

// Meta Puzzle: Scoreboard Inference 2
class Solution_ScoreboardInference2
{
private:
	struct ScoresInfo
	{
		bool r0InLast = false;
		bool r1InLast = false;
		bool r2InLast = false;
		bool r0OutsideOfLast = false;
		bool r1OutsideOfLast = false;
		bool r2OutsideOfLast = false;
	};

private:
	std::vector<std::vector<int>> extrasTable{
		{0,	0,	0,	0,	0,	0,	0},
		{0,	0,	0,	0,	0,	1,	1},
		{0,	0,	0,	0,	1,	0,	1},
		{0,	0,	0,	0,	1,	1,	2},
		{0,	0,	0,	1,	0,	0,	0},
		{0,	0,	0,	1,	0,	1,	1},
		{0,	0,	0,	1,	1,	0,	1},
		{0,	0,	0,	1,	1,	1,	2},
		{0,	0,	1,	0,	0,	1,	1},
		{0,	0,	1,	0,	1,	0,	1},
		{0,	0,	1,	0,	1,	1,	2},
		{0,	0,	1,	1,	0,	0,	1},
		{0,	0,	1,	1,	0,	1,	1},
		{0,	0,	1,	1,	1,	0,	2},
		{0,	0,	1,	1,	1,	1,	2},
		{0,	1,	0,	0,	0,	1,	2},
		{0,	1,	0,	0,	1,	0,	1},
		{0,	1,	0,	0,	1,	1,	2},
		{0,	1,	0,	1,	0,	0,	1},
		{0,	1,	0,	1,	0,	1,	2},
		{0,	1,	0,	1,	1,	0,	1},
		{0,	1,	0,	1,	1,	1,	2},
		{0,	1,	1,	0,	0,	1,	2},
		{0,	1,	1,	0,	1,	0,	2},
		{0,	1,	1,	0,	1,	1,	2},
		{0,	1,	1,	1,	0,	0,	1},
		{0,	1,	1,	1,	0,	1,	2},
		{0,	1,	1,	1,	1,	0,	2},
		{0,	1,	1,	1,	1,	1,	2},
		{1,	0,	0,	0,	0,	1,	1},
		{1,	0,	0,	0,	1,	0,	1},
		{1,	0,	0,	0,	1,	1,	2},
		{1,	0,	0,	1,	0,	0,	0},
		{1,	0,	0,	1,	0,	1,	1},
		{1,	0,	0,	1,	1,	0,	1},
		{1,	0,	0,	1,	1,	1,	2},
		{1,	0,	1,	0,	0,	1,	1},
		{1,	0,	1,	0,	1,	0,	1},
		{1,	0,	1,	0,	1,	1,	2},
		{1,	0,	1,	1,	0,	0,	1},
		{1,	0,	1,	1,	0,	1,	1},
		{1,	0,	1,	1,	1,	0,	2},
		{1,	0,	1,	1,	1,	1,	2},
		{1,	1,	0,	0,	0,	1,	2},
		{1,	1,	0,	0,	1,	0,	1},
		{1,	1,	0,	0,	1,	1,	2},
		{1,	1,	0,	1,	0,	0,	1},
		{1,	1,	0,	1,	0,	1,	2},
		{1,	1,	0,	1,	1,	0,	1},
		{1,	1,	0,	1,	1,	1,	2},
		{1,	1,	1,	0,	0,	1,	0},
		{1,	1,	1,	0,	1,	0,	2},
		{1,	1,	1,	0,	1,	1,	2},
		{1,	1,	1,	1,	0,	0,	1},
		{1,	1,	1,	1,	0,	1,	2},
		{1,	1,	1,	1,	1,	0,	2},
		{1,	1,	1,	1,	1,	1,	2},
	};

private:
	ScoresInfo getScoresInfo(int remainder0Count, int remainder1Count, int remainder2Count, int highestScore, int secondHighestScore, int thirdHighestScore)
	{
		ScoresInfo scoresInfo;

		// Set the flags for the last group (the group of 3 susequent numbers starting from the largest multiple of 3 at or below the highest number)
		if (highestScore % 3 == 0)
		{
			scoresInfo.r0InLast = true;
		}
		else if (highestScore % 3 == 1)
		{
			scoresInfo.r1InLast = true;

			if (secondHighestScore == highestScore - 1)
			{
				scoresInfo.r0InLast = true;
			}
		}
		else if (highestScore % 3 == 2)
		{
			scoresInfo.r2InLast = true;

			if (secondHighestScore == highestScore - 2)
			{
				scoresInfo.r0InLast = true;
			}
			else if (secondHighestScore == highestScore - 1)
			{
				scoresInfo.r1InLast = true;

				if (thirdHighestScore == highestScore - 2)
				{
					scoresInfo.r0InLast = true;
				}
			}
		}

		// Set the flags for the rest of the table values
		if ((remainder0Count > 1) || (remainder0Count == 1 && scoresInfo.r0InLast == false))
		{
			scoresInfo.r0OutsideOfLast = true;
		}
		if ((remainder1Count > 1) || (remainder1Count == 1 && scoresInfo.r1InLast == false))
		{
			scoresInfo.r1OutsideOfLast = true;
		}
		if ((remainder2Count > 1) || (remainder2Count == 1 && scoresInfo.r2InLast == false))
		{
			scoresInfo.r2OutsideOfLast = true;
		}

		// Return the info
		return scoresInfo;
	}

	int getExtraRequiredProblemsV3(int remainder0Count, int remainder1Count, int remainder2Count, int highestScore, int secondHighestScore, int thirdHighestScore)
	{
		int extraProblemsRequired = 0;

		uint8_t truthTableRowFlags = 0b0000'0000;

		const uint8_t r1OutsideMask = 0b0001'0000;
		const uint8_t r2OutsideMask = 0b0000'1000;
		const uint8_t r0inLastMask  = 0b0000'0100;
		const uint8_t r1inLastMask  = 0b0000'0010;
		const uint8_t r2inLastMask  = 0b0000'0001;

		ScoresInfo scoresInfo = getScoresInfo(remainder0Count, remainder1Count, remainder2Count, highestScore, secondHighestScore, thirdHighestScore);

		// Count the extra problems already needed before this last grouping
		if (scoresInfo.r1OutsideOfLast)
		{
			extraProblemsRequired++;
		}
		if (scoresInfo.r2OutsideOfLast)
		{
			extraProblemsRequired++;
		}

		// Set bit flags to use for our truth table
		if (scoresInfo.r1OutsideOfLast == true)
		{
			truthTableRowFlags |= r1OutsideMask;
		}
		if (scoresInfo.r2OutsideOfLast == true)
		{
			truthTableRowFlags |= r2OutsideMask;
		}
		if (scoresInfo.r0InLast == true)
		{
			truthTableRowFlags |= r0inLastMask;
		}
		if (scoresInfo.r1InLast == true)
		{
			truthTableRowFlags |= r1inLastMask;
		}
		if (scoresInfo.r2InLast == true)
		{
			truthTableRowFlags |= r2inLastMask;
		}

		// Now implement the truth table
		switch (truthTableRowFlags)
		{
		case 0b0000'0001: // Row 1
			extraProblemsRequired += 2;
			break;

		case 0b0000'0010: // Row 2
			extraProblemsRequired += 2;
			break;

		case 0b0000'0011: // Row 3
			extraProblemsRequired += 3;
			break;

		case 0b0000'0100: // Row 4
			extraProblemsRequired += 1;
			break;

		case 0b0000'0101: // Row 5
			extraProblemsRequired += 2;
			break;

		case 0b0000'0110: // Row 6
			extraProblemsRequired += 2;
			break;

		case 0b0000'0111: // Row 7
			extraProblemsRequired += 3;
			break;

		case 0b0000'1001: // Row 8
			extraProblemsRequired += 1;
			break;

		case 0b0000'1010: // Row 9
			extraProblemsRequired += 1;
			break;

		case 0b0000'1011: // Row 10
			extraProblemsRequired += 2;
			break;

		case 0b0000'1100: // Row 11
			extraProblemsRequired += 1;
			break;

		case 0b0000'1101: // Row 12
			extraProblemsRequired += 1;
			break;

		case 0b0000'1110: // Row 13
			extraProblemsRequired += 2;
			break;

		case 0b0000'1111: // Row 14
			extraProblemsRequired += 2;
			break;

		case 0b0001'0001: // Row 15
			extraProblemsRequired += 2;
			break;

		case 0b0001'0010: // Row 16
			extraProblemsRequired += 1;
			break;

		case 0b0001'0011: // Row 17
			extraProblemsRequired += 2;
			break;

		case 0b0001'0100: // Row 18
			extraProblemsRequired += 1;
			break;

		case 0b0001'0101: // Row 19
			extraProblemsRequired += 2;
			break;

		case 0b0001'0110: // Row 20
			extraProblemsRequired += 1;
			break;

		case 0b0001'0111: // Row 21
			extraProblemsRequired += 2;
			break;

		case 0b0001'1001: // Row 22
			extraProblemsRequired += 1;
			break;

		case 0b0001'1010: // Row 23
			extraProblemsRequired += 1;
			break;

		case 0b0001'1011: // Row 24
			extraProblemsRequired += 1;
			break;

		case 0b0001'1100: // Row 25
			extraProblemsRequired += 0;
			break;

		case 0b0001'1101: // Row 26
			extraProblemsRequired += 1;
			break;

		case 0b0001'1110: // Row 27
			extraProblemsRequired += 1;
			break;

		case 0b0001'1111: // Row 28
			extraProblemsRequired += 1;
			break;

		case 0b0000'0000:
		case 0b0000'1000:
		case 0b0001'0000:
		case 0b0001'1000:
		default:
			// This should never get hit...
			break;
		}
		
		// Return
		return extraProblemsRequired;
	}
	
	int getExtraRequiredProblemsV2(int remainder0Count, int remainder1Count, int remainder2Count, int highestScore, int secondHighestScore, int thirdHighestScore)
	{
		int extraProblemsRequired = 0;

		bool r0InLast = false;
		bool r1InLast = false;
		bool r2InLast = false;

		// Set the flags for the last group (the group of 3 susequent numbers starting from the largest multiple of 3 at or below the highest number)
		if (highestScore % 3 == 0)
		{
			r0InLast = true;
		}
		else if (highestScore % 3 == 1)
		{
			r1InLast = true;

			if (secondHighestScore == highestScore - 1)
			{
				r0InLast = true;
			}
		}
		else if (highestScore % 3 == 2)
		{
			r2InLast = true;

			if (secondHighestScore == highestScore - 2)
			{
				r0InLast = true;
			}
			else if (secondHighestScore == highestScore - 1)
			{
				r1InLast = true;

				if (thirdHighestScore == highestScore - 2)
				{
					r0InLast = true;
				}
			}
		}

		if (remainder1Count > 0)
		{
			extraProblemsRequired++;
		}

		if (remainder2Count > 0)
		{
			extraProblemsRequired++;
		}

		if (!r1InLast && !r2InLast && remainder1Count > 0 && remainder2Count > 0)
		{
			extraProblemsRequired--;
		}

		if (!r0InLast && !r2InLast && remainder1Count > 1 && remainder2Count > 0)
		{
			extraProblemsRequired--;
		}

		return extraProblemsRequired;
	}

	int getExtraRequiredProblems(int remainder0Count, int remainder1Count, int remainder2Count, int highestScore, int secondHighestScore, int thirdHighestScore)
	{
		int extraProblemsRequired = 0;

		bool r0InLast = false;
		bool r1InLast = false;
		bool r2InLast = false;
		bool r0OutsideOfLast = false;
		bool r1OutsideOfLast = false;
		bool r2OutsideOfLast = false;

		// Set the flags for the last group (the group of 3 susequent numbers starting from the largest multiple of 3 at or below the highest number)
		if (highestScore % 3 == 0)
		{
			r0InLast = true;
		}
		else if (highestScore % 3 == 1)
		{
			r1InLast = true;

			if (secondHighestScore == highestScore - 1)
			{
				r0InLast = true;
			}
		}
		else if (highestScore % 3 == 2)
		{
			r2InLast = true;

			if (secondHighestScore == highestScore - 2)
			{
				r0InLast = true;
			}
			else if (secondHighestScore == highestScore - 1)
			{
				r1InLast = true;

				if (thirdHighestScore == highestScore - 2)
				{
					r0InLast = true;
				}
			}
		}

		// Set the flags for the rest of the table values
		if ((remainder0Count > 1) || (remainder0Count == 1 && r0InLast == false))
		{
			r0OutsideOfLast = true;
		}
		if ((remainder1Count > 1) || (remainder1Count == 1 && r1InLast == false))
		{
			r1OutsideOfLast = true;
		}
		if ((remainder2Count > 1) || (remainder2Count == 1 && r2InLast == false))
		{
			r2OutsideOfLast = true;
		}

		// Search the table for the correct output value number of extra problems (this will have to do for now)
		//for (auto& row : extrasTable)
		for (int row = 0; row < extrasTable.size(); ++row)
		{
			bool testPassed = true;
			int testRow[] = {r0OutsideOfLast, r1OutsideOfLast, r2OutsideOfLast, r0InLast, r1InLast, r2InLast};
			for (int col = 0; col < 6; ++col)
			{
				if (extrasTable[row][col] != testRow[col])
				{
					testPassed = false;
					break;
				}
			}

			if (testPassed)
			{
				//std::cout << "Table row: " << row << " used" << std::endl;
				extraProblemsRequired = extrasTable[row][6];
				break;
			}
		}

		return extraProblemsRequired;
	}

public:
	int getMinProblemCount(int N, std::vector<int>& S) // O(N)
	{
		int minProblemCount = 0;

		int remainder0Count = 0;
		int remainder1Count = 0;
		int remainder2Count = 0;

		int prevRemainder0Number = 0;
		int prevRemainder1Number = 0;
		int prevRemainder2Number = 0;

		// Go through each known score
		int highestScore = 0;
		int secondHighestScore = 0;
		int thirdHighestScore = 0;
		for (int i = 0; i < S.size(); ++i) // O(N)
		{
			// Keep track of the highest scores (excluding duplicates)
			if (S[i] > thirdHighestScore)
			{
				if (S[i] > secondHighestScore)
				{
					if (S[i] > highestScore)
					{
						thirdHighestScore = secondHighestScore;
						secondHighestScore = highestScore;
						highestScore = S[i];
					}
					else if (S[i] != highestScore)
					{
						thirdHighestScore = secondHighestScore;
						secondHighestScore = S[i];
					}
				}
				else if (S[i] != secondHighestScore)
				{
					thirdHighestScore = S[i];
				}
			}

			// Flag scenarios we're interested in
			switch (S[i] % 3)
			{
			case 0:
				if (S[i] != prevRemainder0Number)
				{
					// The counter doesn't actually need to be accurate - we just need to know if there are multiple DIFFERENT numbers with this remainder
					remainder0Count++;
					prevRemainder0Number = S[i];
				}
				break;

			case 1:
				if (S[i] != prevRemainder1Number)
				{
					// The counter doesn't actually need to be accurate - we just need to know if there are multiple DIFFERENT numbers with this remainder
					remainder1Count++;
					prevRemainder1Number = S[i];
				}
				break;

			case 2:
				if (S[i] != prevRemainder2Number)
				{
					// The counter doesn't actually need to be accurate - we just need to know if there are multiple DIFFERENT numbers with this remainder
					remainder2Count++;
					prevRemainder2Number = S[i];
				}
				break;

			default:
				// This should never occur
				break;
			}
		}

		// Get the base amount of problems required
		minProblemCount = (highestScore / 3) - 1;

		// Get the extra amount of required problems
		minProblemCount += getExtraRequiredProblemsV3(remainder0Count, remainder1Count, remainder2Count, highestScore, secondHighestScore, thirdHighestScore);

		// Return the inferred min problem count
		return minProblemCount;
	}

	void Test()
	{
		std::vector<int> scoreboardInference2Scores{};

		// Run all possible combinations of test values (up to a certain number), if you want
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
									auto scoreboardInference2Result = getMinProblemCount(scoreboardInference2Scores.size(), scoreboardInference2Scores);
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

		// A specific test case
		scoreboardInference2Scores = { 6, 7, 8, 7, 7, 7, 7 };
		auto scoreboardInference2Result = getMinProblemCount(scoreboardInference2Scores.size(), scoreboardInference2Scores);
	}
};