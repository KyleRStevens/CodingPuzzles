#pragma once

// Standard
#include <vector>

template <typename T>
class MyMinHeap
{
public:
	void Insert(T value);

	T PopMin();

private:
	int GetParentIndex(int currentIndex) { return (currentIndex - 1) / 2; }
	
	int GetLeftIndex(int currentIndex) { return (2 * currentIndex) + 1; }

	int GetRightIndex(int currentIndex) { return (2 * currentIndex) + 2; }

private:
	std::vector<T> m_data;
};

template<typename T>
inline void MyMinHeap<T>::Insert(T value)
{
	int currentIndex = m_data.size();

	// First, insert at the end of the data array
	m_data.push_back(value);

	// Then, swap with the parent if it is smaller than it (recursively until you are done or you reach the root node)
	int parentIndex = GetParentIndex(currentIndex);
	while (value < m_data[parentIndex])
	{
		// Do the swap
		std::swap(m_data[currentIndex], m_data[parentIndex]);

		// Update indices (breaking out of the loop if we've reached the root node)
		currentIndex = parentIndex;
		if (currentIndex == 0)
		{
			break;
		}
		parentIndex = GetParentIndex(parentIndex);
	}
}

template<typename T>
inline T MyMinHeap<T>::PopMin()
{
	// Ensure the heap is not empty
	if (m_data.empty() != true)
	{
		int currentIndex = 0;

		// Save the min element (root node value)
		const T minValue = m_data[currentIndex];

		// Swap the last element with the root
		std::swap(m_data[m_data.size() - 1], m_data[currentIndex]);

		// Remove the last element from the data array
		m_data.pop_back();

		while (currentIndex < m_data.size())
		{
			// Get the left child of the current index (if possible)
			int leftIndex = GetLeftIndex(currentIndex);
			int leftValue = m_data[currentIndex];
			if (leftIndex < m_data.size())
			{
				leftValue = m_data[leftIndex];
			}

			// Get the right child of the current index (if possible)
			int rightIndex = GetRightIndex(currentIndex);
			int rightValue = m_data[currentIndex];
			if (rightIndex < m_data.size())
			{
				rightValue = m_data[rightIndex];
			}

			// If either of the children are smaller, swap the current node and that smaller child (repeatedly until done)
			if (leftValue < rightValue && leftValue < m_data[currentIndex])
			{
				std::swap(m_data[leftIndex], m_data[currentIndex]);
				currentIndex = leftIndex;
			}
			else if (rightValue < leftValue && rightValue < m_data[currentIndex])
			{
				std::swap(m_data[rightIndex], m_data[currentIndex]);
				currentIndex = rightIndex;
			}
			else
			{
				break;
			}
		}

		// Return the (previously) minimum value
		return minValue;
	}

	return 0;
}
