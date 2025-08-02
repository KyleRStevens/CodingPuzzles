#pragma once

// Standard
#include <algorithm>
#include <vector>

// LeetCode #4: Median Of Two Sorted Arrays
class Solution_MedianOfTwoSortedArrays
{
public:
    // Straightforward solution
    double findMedianSortedArraysIntuitive(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        double median = 0.0;
        int leftIndex1 = 0;
        int leftIndex2 = 0;
        std::vector<int> mergedArray;
        mergedArray.reserve(nums1.size() + nums2.size());

        // Merge the two arrays into one
        mergedArray.insert(mergedArray.end(), nums1.begin(), nums1.end());
        mergedArray.insert(mergedArray.end(), nums2.begin(), nums2.end());
        std::sort(mergedArray.begin(), mergedArray.end());

        // Get mediam
        if (mergedArray.size() % 2 == 0) // Even
        {
            median = mergedArray[(mergedArray.size() / 2) - 1];
            median += mergedArray[(mergedArray.size() / 2)];
            median /= 2.0;
        }
        else // Odd
        {
            median = mergedArray[mergedArray.size() / 2];
        }

        return median;
    }

    // More efficient solution
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        double median = 0.0;
        int i1 = 0;
        int i2 = 0;

        // Find the target index of the combined sorted list
        int totalElements = nums1.size() + nums2.size();
        int medianIndex = (totalElements - 1) / 2;

        // Flag if the total size is odd or even
        bool isOdd = (totalElements % 2 != 0);

        // Move the indices enough times to reach the median index
        int i = 0;
        for (; i < medianIndex; ++i)
        {
            // First, make sure the indecies are still in bounds (if not, we can break out early)
            if (i1 >= nums1.size())
            {
                // In this case, we can skip the i2 index directly to where we now know the median element will be (skip ahead the remaining distance)
                i2 += medianIndex - i;
                break;
            }
            else if (i2 >= nums2.size())
            {
                // In this case, we can skip the i1 index directly to where we now know the median element will be (skip ahead the remaining distance)
                i1 += medianIndex - i;
                break;
            }

            // Otherwise, keep skipping ahead the appropriate index
            if (nums1[i1] <= nums2[i2])
            {
                i1++;
            }
            else // (nums1[i1] > nums2[i2])
            {
                i2++;
            }
        }

        // We can now retrieve the median from where we ended up
        if (isOdd)
        {
            if (i1 >= nums1.size())
            {
                // If only i2 is in bounds, the median is just the element at i2
                median = nums2[i2];
            }
            else if (i2 >= nums2.size())
            {
                // If only i1 is in bounds, the median is just the element at i1
                median = nums1[i1];
            }
            else
            {
                // If both indices are in bounds, the median is the min of the two valid elements
                median = std::min(nums1[i1], nums2[i2]);
            }
        }
        else
        {
            if (i1 >= nums1.size() && i2 >= nums2.size())
            {
                std::cerr << "-w- Unable to get a median" << std::endl;
            }
            else if (i1 >= nums1.size())
            {
                // If only i2 is in bounds, the median is the average of the element at i2 and the following element in that list (garunteed to be in bounds)
                median = (nums2[i2] + nums2[i2 + 1]) / 2.0;
            }
            else if (i2 >= nums2.size())
            {
                // If only i1 is in bounds, the median is the average of the element at i1 and the following element in that list (garunteed to be in bounds)
                median = (nums1[i1] + nums1[i1 + 1]) / 2.0;
            }
            else
            {
                // If both indices are in bounds, the median is the average of (the min of two valid elements) and (the min of the next element in that element's list and the other element)
                if (nums1[i1] < nums2[i2])
                {
                    double leftMedian = nums1[i1];
                    double rightMedian = nums2[i2];
                    if (i1 + 1 < nums1.size())
                    {
                        rightMedian = std::min(nums2[i2], nums1[i1 + 1]);
                    }
                    median = (leftMedian + rightMedian) / 2.0;
                }
                else if (nums1[i1] > nums2[i2])
                {
                    double leftMedian = nums2[i2];
                    double rightMedian = nums1[i1];
                    if (i2 + 1 < nums2.size())
                    {
                        rightMedian = std::min(nums1[i1], nums2[i2 + 1]);
                    }
                    median = (leftMedian + rightMedian) / 2.0;
                }
                else // (nums1[i1] == nums2[i2])
                {
                    median = nums1[i1];
                }
            }
        }

        // Return
        return median;
    }

    void Test()
    {
        std::vector<int> nums1{ 100001 };
        std::vector<int> nums2{ 100000 };
        auto result = findMedianSortedArrays(nums1, nums2);
    }
};