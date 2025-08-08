#pragma once

// Standard
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

// LeetCode #5: Longest Palindromic Substring
class Solution_LongestPalindromicSubstring
{
public:
    std::string longestPalindrome(std::string& s)
    {
        int maxFoundLength = 0;
        int maxFoundLeftIndex = 0;
        int currentLengthBeingChecked = 0;
        int currentLeftIndexBeingChecked = 0;

        //For each character of s
        for (int i = 0; i < s.size(); ++i)
        {
            // Each time we start at a new character from s, the max length palindrome will be the substring length up to the current character (index i + 1)
            currentLengthBeingChecked = i + 1;

            // Set left and right pointers
            int left = 0; // Moves while checking the current, (so-far) valid palindrome
            int right = i; // Moves while checking the current, (so-far) valid palindrome
            currentLeftIndexBeingChecked = 0; // Stays at the leftmost character of the current, (so-far) valid palindrome being checked

            // Check for a palindrome with the current substring
            while (true)
            {
                // Exit the loop once the left/right pointers cross
                if (left > right)
                {
                    break;
                }
                else
                {
                    // If the left/right characters are equal, move inward to check the next (more inner) left/right characters
                    if (s[left] == s[right])
                    {
                        left++;
                        right--;
                    }
                    // Otherwise, move ONLY the left pointer over & decrese "current palindrome length" being checked
                    else
                    {
                        // Update trackers (with early return for skipping unnecessary checks)
                        currentLengthBeingChecked--;
                        if (currentLengthBeingChecked <= maxFoundLength)
                        {
                            // There's no point in continuing to search if what we're checking won't even be longer than what we've found so far
                            break;
                        }
                        currentLeftIndexBeingChecked++;

                        // Reset left/right because they may have moved from partial sucesses
                        right = i;
                        left = currentLeftIndexBeingChecked;
                    }
                }
            }

            // If a new palindrome was found, update the max length found (if necessary)
            if (currentLengthBeingChecked > maxFoundLength)
            {
                // Update max length
                maxFoundLength = currentLengthBeingChecked;

                // Set the left/right indices for the current max length palindromic substring
                maxFoundLeftIndex = currentLeftIndexBeingChecked;
            }
        }

        // We've scanned the whole input string, and saved the indices from whatever max length palindrome we found
        // Now, return a substring from those indices
        return s.substr(maxFoundLeftIndex, maxFoundLength);
    }

    void Test()
    {
        std::string testCase = "babad";
        auto result = longestPalindrome(testCase);
    }
};