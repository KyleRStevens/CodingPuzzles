#pragma once

// Standard
#include <vector>
#include <type_traits>
#include <math.h>

// Does a bubble sort: O(n^2)
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type
BubbleSort(std::vector<T>& list)
{
	// For each index position, bubble-up the larget value
	for (int iSorted = list.size() - 1; iSorted >= 0; --iSorted)
	{
		// One bubble-up
		for (int j = 0; j < iSorted; ++j)
		{
			if (list[j] > list[j + 1])
			{
				std::swap(list[j], list[j + 1]);
			}
		}
	}
}

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type
MergeSortRecursiveHelper(std::vector<T>& list, int iStart, int iEnd)
{
	// If the sub-list is of length 1 or empty, it's already sorted
	if (iStart >= iEnd)
	{
		return;
	}

	// Find the middle of the current range
	int iMiddle = ((iEnd - iStart) / 2) + iStart;

	// Recursively sort the left half
	MergeSortRecursiveHelper(list, iStart, iMiddle);

	// Recursively sort the right half
	MergeSortRecursiveHelper(list, iMiddle + 1, iEnd);

	// Merge the two sorted halves
	std::vector<T> mergedList;
	int leftIndex = iStart;
	int rightIndex = iMiddle + 1;

	// Merge until we get to the end of one of the sub-lists
	while (leftIndex <= iMiddle && rightIndex <= iEnd)
	{
		// Compare and push the smaller element into the merged list
		if (list[leftIndex] <= list[rightIndex])
		{
			mergedList.push_back(list[leftIndex]);
			leftIndex++;
		}
		else
		{
			mergedList.push_back(list[rightIndex]);
			rightIndex++;
		}
	}

	// Copy any remaining elements from the left sub-list
	if (leftIndex <= iMiddle)
	{
		std::copy(list.begin() + leftIndex, list.begin() + iMiddle + 1, std::back_inserter(mergedList));
	}

	// Copy any remaining elements from the right sub-list
	if (rightIndex <= iEnd)
	{
		std::copy(list.begin() + rightIndex, list.begin() + iEnd + 1, std::back_inserter(mergedList));
	}

	// Copy the merged list back into the original list
	std::copy(mergedList.begin(), mergedList.end(), list.begin() + iStart);
}

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type
MergeSortRecursive(std::vector<T>& list)
{
	// Initial call to the recursive helper function, sorting the entire list
	if (!list.empty())
	{
		MergeSortRecursiveHelper(list, 0, list.size() - 1);
	}
}

// Does a merge sort
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type
MergeSort(std::vector<T>& list)
{
	int iteration = 0;
	int subListSize = 1;
	std::vector<T> mergedList;
	mergedList.reserve(list.size());

	// Do the merge sorting
	while (subListSize < list.size())
	{
		// For each sub-list pair (half the number of sub-lists that can fit into the whole list - then the ceiling of that in case there is an odd number)...
		int numSubLists = std::ceil(static_cast<float>(list.size()) / static_cast<float>(subListSize));
		int numSubListPairs = std::ceil(static_cast<float>(numSubLists) / 2.0f);
		for (int i = 0; i < numSubListPairs; ++i)
		{
			// Sort/merge the sub-list pair
			const int leftOffset = subListSize * 2 * i; // The size of a *pair* of sub-lists (hence the 2), multiplied by how many sub-lists we've already gone through (i)
			const int rightOffset = leftOffset + subListSize;
			int iLeft = leftOffset;
			int iRight = rightOffset;
			while (true) // We break out of this from the inside based on a few different conditions
			{
				// Make sure we're still in bounds of the list (if not, copy anything remaining and break out)
				if (iRight >= list.size())
				{
					// Right side is done due to reaching the end of the original list, copy the remaining left side (keeping it in bounds of the original list)
					if (iLeft < list.size())
					{
						int leftEndIndex = std::min(leftOffset + subListSize, static_cast<int>(list.size() - 1));
						std::copy(list.begin() + iLeft, list.begin() + leftEndIndex, std::back_inserter(mergedList));
					}
					else
					{
						// Does this ever get hit??
						int x = 5;
					}
					break;
				}
				else if (iLeft >= list.size())
				{
					// Does THIS ever get hit???
					break;
				}

				// Merge in the smaller of the items being compared
				if (list[iLeft] < list[iRight])
				{
					// The left side is smaller, merge it and advance iLeft
					mergedList.push_back(list[iLeft]);
					iLeft++;
				}
				else if (list[iLeft] > list[iRight])
				{
					// The right side is smaller, merge it and advance iRight
					mergedList.push_back(list[iRight]);
					iRight++;
				}
				else // (list[iLeft] == list[iRight])
				{
					// The values are equal, merge them both in and advance both indices
					mergedList.push_back(list[iLeft]);
					mergedList.push_back(list[iRight]);
					iLeft++;
					iRight++;
				}

				// Check if one of the sub-lists just finished (if so, merge in the rest of the other sub-list, then break out of the loop)
				if (iRight - rightOffset >= subListSize)
				{
					// Right side has finished, merge the left, then break
					int endIndex = std::min(leftOffset + subListSize, static_cast<int>(list.size() - 1));
					std::copy(list.begin() + iLeft, list.begin() + endIndex, std::back_inserter(mergedList));
					break;
				}
				else if (iLeft - leftOffset >= subListSize)
				{
					// Left side has finished, merge the right, then break
					int endIndex = std::min(rightOffset + subListSize, static_cast<int>(list.size() - 1));
					std::copy(list.begin() + iRight, list.begin() + endIndex, std::back_inserter(mergedList));
					break;
				}
			}

			// We're done sorting this sort space pair, so we can copy the sorted list back into the original list
			if (list.size() - leftOffset >= mergedList.size())
			{
				std::copy(mergedList.begin(), mergedList.end(), list.begin() + leftOffset);
			}

			// Clear the merged list for reuse
			mergedList.clear();
		}

		// Go to the next iteration
		iteration++;
		subListSize = std::pow(2, iteration);
	}
}