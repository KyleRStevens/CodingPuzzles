#pragma once

// Standard
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

// LeetCode #18: Four Sum
class Solution_FourSum
{
public:
    bool BinarySearch(std::vector<int>& sortedList, long long int target, int startIndex, int endIndex)
    {
        int LEFT = startIndex;
        int RIGHT = endIndex;

        while (LEFT <= RIGHT)
        {
            int MIDDLE = ((RIGHT - LEFT) / 2) + LEFT;

            if (sortedList[MIDDLE] == target)
            {
                // Target found - return true
                return true;
            }
            else if (sortedList[MIDDLE] < target)
            {
                LEFT = MIDDLE + 1;
            }
            else // if (sortedList[MIDDLE] > target)
            {
                RIGHT = MIDDLE - 1;
            }
        }

        // No target could be found - return false
        return false;
    }

    void AdvanceIndexToNextValue(std::vector<int>& sortedList, int& index)
    {
        // For now assuming the given index is in range...
        int startingValue = sortedList[index];

        while (index < sortedList.size() && sortedList[index] == startingValue)
        {
            index++;
        }
    }

    // Intuitive approach
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target)
    {
        std::vector<std::vector<int>> quadruplets;

        // Sort the list as it will be easier to work with
        std::sort(nums.begin(), nums.end());

        for (int i1 = 0; i1 < nums.size(); AdvanceIndexToNextValue(nums, i1))
        {
            for (int i2 = i1 + 1; i2 < nums.size(); AdvanceIndexToNextValue(nums, i2))
            {
                // Get the sum of the first 2 elements of the current check
                long long int twoSum = nums[i1] + nums[i2];

                // Check for impossible scenario condition(s) to break out of the current loop early
                if (nums[i2] >= 0 && twoSum > target)
                {
                    // The sum is only going to grow but we're already too large - we can be done for this iteration of i2
                    break;
                }

                // A solution is still possible - continue searching
                for (int i3 = i2 + 1; i3 < nums.size(); AdvanceIndexToNextValue(nums, i3))
                {
                    // Get the sum of the first 3 elements of the current check
                    long long int threeSum = twoSum + nums[i3];

                    // Check for impossible scenario condition(s) to break out of the current loop early
                    if (nums[i3] >= 0 && threeSum > target)
                    {
                        // The sum is only going to grow but we're already too large - we can be done for this iteration of i3
                        break;
                    }

                    // Search for a valid forth element
                    long long int requiredFourthNumber = target - threeSum;
                    if (BinarySearch(nums, requiredFourthNumber, i3 + 1, nums.size() - 1))
                    {
                        // We found a valid four sum - add it to the quadruplets list
                        quadruplets.push_back({ nums[i1], nums[i2], nums[i3], static_cast<int>(requiredFourthNumber) });
                    }
                    else
                    {
                        // Go on to the next loop iteration
                        continue;
                    }
                }
            }
        }

        return quadruplets;
    }

    void Test()
    {
        std::vector<int> nums{ -1000000000,-1000000000,1000000000,-1000000000,-1000000000 };
        //std::vector<int> nums{ 2, 2, 2, 2, 2 };
        int target = 294967296;
        auto result = fourSum(nums, target);
    }
};