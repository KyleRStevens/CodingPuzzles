#pragma once

// Standard
#include <memory>

template <typename T>
class MyStack
{
public:
	MyStack(size_t initialCapacity);
	~MyStack();

public:
	template <typename U>
	void Push(U&& element);

	T Pop();

	void Resize(size_t newCapacity);

private:
	T* m_pMemory = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 1;
};

template<typename T>
inline MyStack<T>::MyStack(size_t initialCapacity) :
	m_capacity(initialCapacity)
{
	m_pMemory = new T[initialCapacity]();
}

template<typename T>
inline MyStack<T>::~MyStack()
{
	delete[] m_pMemory;
}

template<typename T>
template<typename U>
inline void MyStack<T>::Push(U&& element)
{
	// Make sure there's room to add a new element (if not, grow the container's capacity)
	if (m_capacity <= m_size)
	{
		Resize(m_capacity * 2);
	}

	// Add the element (now that we know it will fit)
	m_pMemory[m_size] = std::forward<U>(element);

	// Increase the container size
	m_size++;
}

template<typename T>
inline T MyStack<T>::Pop()
{
	// Make sure there is an element to pop
	if (m_size == 0)
	{
		throw std::out_of_range("Stack is empty!");
	}

	// Decrease the container size
	m_size--;

	// Return the element we just "removed"
	return m_pMemory[m_size];
}

template<typename T>
inline void MyStack<T>::Resize(size_t newCapacity)
{
	try
	{
		// Allocate the new memory
		T* newMemory = new T[newCapacity]();

		// Copy the data to the new memory location (using std::move since we're copying elements that may have move semantics)
		// Instead of: memcpy_s(newMemory, newCapacity * sizeof(T), m_pMemory, m_capacity * sizeof(T));
		for (size_t i = 0; i < m_size; ++i)
		{
			newMemory[i] = std::move(m_pMemory[i]);
		}

		// Delete the old memory
		delete[] m_pMemory;

		// Update the members to reflect the new memory
		m_pMemory = newMemory;
		m_capacity = newCapacity;
		if (m_size > m_capacity)
		{
			m_size = m_capacity;
		}
	}
	catch (...)
	{
		// TODO: Any specific error handling we want to do
		throw;
	}
}
