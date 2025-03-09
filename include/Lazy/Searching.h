#pragma once

// Standard
#include <vector>
#include <type_traits>

// Searches a smallest to largest sorted list for the target value (returns the index or -1 if not found)
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, int>::type
BinarySearch(std::vector<T>& sortedList, T target, int startingLeftIndex = 0, int startingRightIndex = -1)
{
    int targetIndex = -1;
    int iLeft = startingLeftIndex;
    int iRight = startingRightIndex;
    if (iRight == -1)
    {
        iRight = sortedList.size() - 1;
    }

    // Do the binary search
    while (iLeft <= iRight)
    {
		// Get middle index
        int iMiddle = ((iRight - iLeft) / 2) + iLeft;

		// Check value
        if (sortedList[iMiddle] == target)
        {
			// We found it; set the target index and break out of the search loop
            targetIndex = iMiddle;
            break;
        }
        else if (sortedList[iMiddle] < target)
        {
			// Target is to the right (higher value)
            iLeft = iMiddle + 1;
        }
		else // (sortedList[iMiddle] > target)
        {
			// Target is to the left (lower value)
            iRight = iMiddle - 1;
        }
    }

    return targetIndex;
}