#pragma once

// Standard
#include <vector>
#include <iostream>
#include <unordered_set>
#include <set>
#include <stack>
#include <cstdint>
#include <map>
#include <mutex>

class Solution_Kaitenzushi
{
public:
	class MyQueue
	{
	public:
		MyQueue() = default;
		MyQueue(int initialCapacity) { m_data.resize(initialCapacity); }

	public:
		void Push(int value)
		{
			// Move the front index forward
			m_newestIndex++;
			m_newestIndex %= m_data.capacity();

			// Incriment the size
			m_size++;

			// Check if it needs to resize the queue
			if (m_newestIndex == m_oldestIndex && Size() != 1)
			{
				Resize(m_data.capacity() * 2);
			}

			// Add the element to the front of the queue
			m_data[m_newestIndex] = value;
		}

		int Pop()
		{
			int value = -1;

			// Make sure the queue is not empty
			if (Size() > 0)
			{
				// Capture the leaving value
				value = m_data[m_oldestIndex];

				// Move the back index forward
				m_oldestIndex++;
				m_oldestIndex %= m_data.capacity();

				// Decriment the size
				m_size--;

				// Return the popped value
				return value;
			}

			throw std::out_of_range("The queue is empty");
			return value;
		}

		int Size() { return m_size; }

	public:
		int& operator[](size_t index)
		{
			int realIndex = (m_newestIndex + index) % m_data.capacity();
			return m_data[realIndex];
		}

	private:
		void Resize(int newCapacity)
		{
			m_data.resize(newCapacity);
		}

	private:
		std::vector<int> m_data;
		int m_newestIndex = -1;
		int m_oldestIndex = 0;
		int m_size = 0;
	};

public:
	int getMaximumEatenDishCount(int N, std::vector<int>& D, int K) // O(N + K)
	{
		int numDishesEaten = 0;

		// A hash table of the previously eaten dishes, where the dish type "ID" is the index - allows checking the "previously eaten" state for a dish type in O(1)
		// Not very space efficient, but it seems speed is more important than memory efficiency in this problem statement
		std::vector<bool /*prevEatenFlag*/> previouslyEatenDishesHashTable(1'000'001, false); // O(1,000,001) which is effectively O(2*K) which is O(K)

		// A container to store the previous 'K' (# of) dishes eaten
		MyQueue previouslyEatenDishesQueue(K); // O(K)

		// For each dish in D
		for (int i = 0; i < D.size(); ++i) // Always going to be O(N)
		{
			// Check if it is in 'previouslyEatenDishes'
			if (previouslyEatenDishesHashTable[D[i]]) // O(1)
			{
				// Skip the dish
				continue;
			}
			else
			{
				// Eat the dish (keep count)
				numDishesEaten++;

				// Remove OLDEST dish from previouslyEatenDishes (if previouslyEatenDishes has reached capacity)
				if (previouslyEatenDishesQueue.Size() >= K) // O(1)
				{
					int oldDish = previouslyEatenDishesQueue.Pop(); // O(1)
					previouslyEatenDishesHashTable[oldDish] = false; // O(1)
				}

				// Add dish to previouslyEatenDishes
				int newDish = D[i];
				previouslyEatenDishesQueue.Push(newDish); // O(1)
				previouslyEatenDishesHashTable[D[i]] = true; // O(1)
			}
		}

		// Return how many dishes were eaten
		return numDishesEaten;
	}
};