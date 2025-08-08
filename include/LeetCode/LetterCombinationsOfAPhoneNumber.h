#pragma once

// Standard
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

// LeetCode #17: Letter Combinations Of A Phone Number
class Solution_LetterCombinationsOfAPhoneNumber
{
public:
    void GetPossibleLetters(char digit, std::string& possibleLetters)
    {
        switch (digit)
        {
        case '2':
            possibleLetters = "abc";
            break;

        case '3':
            possibleLetters = "def";
            break;

        case '4':
            possibleLetters = "ghi";
            break;

        case '5':
            possibleLetters = "jkl";
            break;

        case '6':
            possibleLetters = "mno";
            break;

        case '7':
            possibleLetters = "pqrs";
            break;

        case '8':
            possibleLetters = "tuv";
            break;

        case '9':
            possibleLetters = "wxyz";
            break;

        default:
            std::cerr << "Uh oh..." << std::endl;
            break;
        }
    }

    std::vector<std::string> letterCombinations(std::string& digits)
    {
        std::vector<std::string> allLetterCombinations;
        allLetterCombinations.reserve(std::pow(4, digits.size()));

        // Initialize the vector with an empty string so it doesn't appear empty (useful for the first pass below)
        allLetterCombinations.emplace_back("");

        // For each digit in input number
        for (char& digit : digits)
        {
            // Retrieve the possible letters for the current digit
            std::string possibleLetters;
            GetPossibleLetters(digit, possibleLetters);

            // Get that many copies of the current letter combinations
            int savedSize = allLetterCombinations.size();
            for (int j = 0; j < possibleLetters.size() - 1; ++j)
            {
                allLetterCombinations.insert(allLetterCombinations.end(), allLetterCombinations.begin(), allLetterCombinations.begin() + savedSize);
            }

            // For each possible letter for the current digit
            for (int k = 0; k < possibleLetters.size(); ++k)
            {
                // Get the offset to the current sublist (copy of the current letter combinations list)
                int offset = savedSize * k;

                // Append the current possible letter to each string in the sublist
                for (int i = 0; i < savedSize; ++i)
                {
                    allLetterCombinations[i + offset] = allLetterCombinations[i + offset] + possibleLetters[k];
                }
            }
        }

        // Check if the list is just the empty string (if so, remove it so the list is actually empty)
        if (allLetterCombinations.size() == 1 && allLetterCombinations[0] == "")
        {
            allLetterCombinations.clear();
        }

        // Return
        return allLetterCombinations;
    }

    void Test()
    {
        std::string testCase = "";
        auto result = letterCombinations(testCase);
    }
};