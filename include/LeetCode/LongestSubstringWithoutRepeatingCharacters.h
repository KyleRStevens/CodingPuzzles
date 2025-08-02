#pragma once

// Standard
#include <unordered_map>
#include <unordered_set>
#include <string>

// LeetCode #3: Longest Substring Without Repeating Characters
class Solution_LongestSubstringWithoutRepeatingCharacters
{
public:
    int lengthOfLongestSubstring(std::string& s)
    {
        int leftIndex = 0;
        int maxLength = 0;

        // Create a set for the unique characters in the current substring (reserving max possible size)
        std::unordered_set<char> tempUsedCharacters;
        tempUsedCharacters.reserve(s.length());

        // For each character in the input string...
        for (int i = 0; i < s.length(); ++i)
        {
            // Infinite loop (will escape from inside)
            while (true)
            {
                // Is the current caracter in our current char set?
                if (tempUsedCharacters.find(s[i]) != tempUsedCharacters.end()) // If YES...
                {
                    // Remove LEFT character
                    tempUsedCharacters.erase(s[leftIndex]);

                    // Update left character index
                    leftIndex++;

                    // Recheck the current character
                    continue;
                }
                else // If NO...
                {
                    // Add the current character to the char set
                    tempUsedCharacters.insert(s[i]);

                    // Adjust the max found size if necessary
                    if (tempUsedCharacters.size() > maxLength)
                    {
                        maxLength = tempUsedCharacters.size();
                    }

                    // Move on to the next character in the string
                    break;
                }
            }
        }

        // Return the max found substring length
        return maxLength;
    }

    void Test()
    {
        std::string testString = "pwwkew";
        auto result = lengthOfLongestSubstring(testString);
    }
};