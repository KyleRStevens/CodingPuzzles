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

// Does a merge sort: O(nlogn)
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type
MergeSort(std::vector<T>& list)
{
	int subListSize = 1;
	std::vector<T> mergedList;
	mergedList.reserve(list.size());

	// Do the merge sorting so long as there are multiple sub-lists to merge
	while (subListSize < list.size())
	{
		// Process each sub-list pair
		for (int LEFT_OFFSET = 0; LEFT_OFFSET < list.size(); LEFT_OFFSET += 2 * subListSize)
		{
			// Calculate the starting indices of the left and right sub-lists
			const int RIGHT_OFFSET = LEFT_OFFSET + subListSize;
			int iLeft = LEFT_OFFSET;
			int iRight = RIGHT_OFFSET;

			// Get the bounds index to not go beyond our current sort space (whether it is the end of the sub-list OR the actual bounds of the original list)
			const int LEFT_OUT_OF_BOUNDS_INDEX = std::min(RIGHT_OFFSET, static_cast<int>(list.size()));
			const int RIGHT_OUT_OF_BOUNDS_INDEX = std::min(RIGHT_OFFSET + subListSize, static_cast<int>(list.size()));
			
			// Merge the two sub-lists
			while (iLeft < LEFT_OUT_OF_BOUNDS_INDEX && iRight < RIGHT_OUT_OF_BOUNDS_INDEX)
			{
				// Merge in the smaller of the items being compared
				if (list[iLeft] <= list[iRight])
				{
					// The left side is smaller, merge it and advance iLeft
					mergedList.push_back(list[iLeft]);
					iLeft++;
				}
				else
				{
					// The right side is smaller, merge it and advance iRight
					mergedList.push_back(list[iRight]);
					iRight++;
				}
			}

			// Copy any remaining elements from the left sub-list
			if (iLeft < LEFT_OUT_OF_BOUNDS_INDEX)
			{
				std::copy(list.begin() + iLeft, list.begin() + LEFT_OUT_OF_BOUNDS_INDEX, std::back_inserter(mergedList));
			}

			// Copy any remaining elements from the right sub-list
			if (iRight < RIGHT_OUT_OF_BOUNDS_INDEX)
			{
				std::copy(list.begin() + iRight, list.begin() + RIGHT_OUT_OF_BOUNDS_INDEX, std::back_inserter(mergedList));
			}

			// Copy the merged list back into the original list
			std::copy(mergedList.begin(), mergedList.end(), list.begin() + LEFT_OFFSET);

			// Clear the merged list for reuse
			mergedList.clear();
		}

		// Double the sub-list size for the next iteration
		subListSize *= 2;
	}
}

// Does an insertion sort: O(n^2)
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type
InsertionSort(std::vector<T>& list)
{
	// For each element in the list, shift it down until it is sorted with the already sorted elements in the list
	for (int i = 1; i < list.size(); ++i)
	{
		// Starting at our current index and decrementing until we've found the spot in the sorted section to insert the current element
		int indexToInsert = i - 1;
		while (indexToInsert >= 0 && list[i] < list[indexToInsert])
		{
			--indexToInsert;
		}
		indexToInsert++; // We insert *after* the smaller item is found

		// Save the current item to be inserted (since it will be overwritten)
		T itemToInsert = list[i];

		// Shift all the sorted elements to make room for the insert
		std::copy(list.begin() + indexToInsert, list.begin() + i, list.begin() + indexToInsert + 1);

		// Insert the item
		list[indexToInsert] = itemToInsert;
	}
}

// Does a selection sort: O(n^2)
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type
SelectionSort(std::vector<T>& list)
{
	// For each index position, bubble-up the larget value
	for (int iSorted = list.size() - 1; iSorted >= 0; --iSorted)
	{
		// Find the larget value in the unsorted section
		int maxSeenIndex = 0;
		T maxSeen = list[maxSeenIndex];
		for (int j = 1; j <= iSorted; ++j)
		{
			if (list[j] > maxSeen)
			{
				maxSeen = list[j];
				maxSeenIndex = j;
			}
		}

		// Swap with the end of the unsorted section
		std::swap(list[maxSeenIndex], list[iSorted]);
	}
}