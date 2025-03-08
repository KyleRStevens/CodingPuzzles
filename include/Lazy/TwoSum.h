#pragma once

// Standard
#include <algorithm>
#include <map>
#include <vector>

class Solution_TwoSum
{
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        // Create a vector of size 2 to return with the answers
        std::vector<int> answerIndices(2);

        // Create a copy of nums that we can sort (as well as map to their original indexes)
        std::vector<std::pair</*value*/int, /*original index*/int>> sortedNums;
        sortedNums.reserve(nums.size());
        for (int i = 0; i < nums.size(); ++i)
        {
            sortedNums.emplace_back(nums[i], i);
        }

        // Sort the copied nums list
        std::sort(sortedNums.begin(), sortedNums.end());

        // Search by collapsing the search space until the solution is found: O(n)
        int iLeft = 0;
        int iRight = sortedNums.size() - 1;
        while (iLeft < iRight)
        {
            int currentSum = sortedNums[iLeft].first + sortedNums[iRight].first;
            if (currentSum < target)
            {
                iLeft++;
            }
            else if (currentSum > target)
            {
                iRight--;
            }
            else // (currentSum == target)
            {
                answerIndices[0] = sortedNums[iLeft].second;
                answerIndices[1] = sortedNums[iRight].second;
                return answerIndices;
            }
        }

        // Should not get here when there is a valid solution... TODO: Error handling
        return answerIndices;
    }

    std::vector<int> twoSumOld(std::vector<int>& nums, int target)
    {
        // Create a vector of size 2 to return with the answers
        std::vector<int> answerIndices(2);

        // Create a copy of nums that we can sort (as well as map to their original indexes)
        std::vector<std::pair</*value*/int, /*original index*/int>> sortedNums;
        sortedNums.reserve(nums.size());
        for (int i = 0; i < nums.size(); ++i)
        {
            //sortedNums.emplace_back(std::make_pair(nums[i], i));
            sortedNums.emplace_back(nums[i], i);
        }

        // Sort the copied nums list if you want < O(n^2) time
        std::sort(sortedNums.begin(), sortedNums.end());

        // For each number 'i', binary search the remaining larger numbers to see if they sum to the target. O(nlogn)
        for (int i = 0; i < sortedNums.size(); ++i)
        {
            int leftIndex = i + 1;
            int rightIndex = (sortedNums.size() - 1);
            int middleIndex = (leftIndex + 1);
            while (i < middleIndex && middleIndex < sortedNums.size() && leftIndex <= rightIndex)
            {
                // Set current check (middle) index
                middleIndex = ((rightIndex - leftIndex) / 2) + leftIndex;

                // Compare & reset
                if (sortedNums[i].first + sortedNums[middleIndex].first == target)
                {
                    // Answer found
                    answerIndices[0] = sortedNums[i].second;
                    answerIndices[1] = sortedNums[middleIndex].second;
                    return answerIndices;
                }

                // More to search. Update the search space and continue
                if (sortedNums[i].first + sortedNums[middleIndex].first < target)
                {
                    // Answer would be to the right (of middleIndex)
                    leftIndex = middleIndex + 1;
                    continue;
                }
                else if (sortedNums[i].first + sortedNums[middleIndex].first > target)
                {
                    // Answer would be to the left (of middleIndex)
                    rightIndex = middleIndex - 1;
                    continue;
                }
            }
        }

        // Should not get here with a valid solution... TODO: Error handling
        return answerIndices;
    }

    std::vector<int> twoSumSimple(std::vector<int>& nums, int target)
    {
        std::map</*value*/int, /*original index*/int> sortedNums;
        for (int i = 0; i < nums.size(); ++i)
        {
            // If the current index's number is part of the solution, what other number are we looking for?:
            int possibleTarget = (target - nums[i]);

            // Look for the possible target in the sorted list
            if (sortedNums.find(possibleTarget) != sortedNums.end())
            {
                return { sortedNums[possibleTarget], i };
            }

            // Add the current item to our sorted list
            sortedNums[nums[i]] = i;
        }

        // Should not occur...
        return { 0, 0 };
    }
};