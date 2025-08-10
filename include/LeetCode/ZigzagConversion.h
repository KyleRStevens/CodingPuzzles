#pragma once

// Standard
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

// LeetCode #6: Zigzag Conversion
class Solution_ZigzagConversion
{
public:
    std::string convert(std::string s, int numRows)
    {
        std::string convertedString;
        convertedString.reserve(s.size());

        // Early return for single row scenarios
        if (numRows == 1)
        {
            return s;
        }

        // Save each row in the zigzag
        for (int row = 0; row < numRows; ++row)
        {
            // Save each character in the current row
            for (int i = 0; i < s.size() + row; i += (2 * (numRows - 1))) // We're going to s.size() + row because we need to check the (i - row) character, so I needs to go slight beyond the bounds
            {
                // The first & final row in a given test case will get double-added if we don't do this check...
                if (row > 0 && row < numRows - 1)
                {
                    // Add "left side" character
                    int leftCharIndex = i - row;
                    if (leftCharIndex >= 0) // Protect for out of bounds
                    {
                        convertedString.push_back(s[leftCharIndex]);
                    }
                }

                // Add "right side" character
                int rightCharIndex = i + row;
                if (rightCharIndex < s.size()) // Protect for out of bounds
                {
                    convertedString.push_back(s[rightCharIndex]);
                }
            }
        }

        // Return the converted string
        return convertedString;
    }

    void Test()
    {
        std::string test = "PAYPALISHIRING";
        int numRows = 3;
        auto result = convert(test, numRows);
    }
};