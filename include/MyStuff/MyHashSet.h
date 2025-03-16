#pragma once

// Standard
#include <vector>
#include <algorithm>

template <typename T>
class MyHashSet
{
public:
	class Bucket
	{
	public:
		std::vector<T> m_elements;
	};

public:
	MyHashSet(size_t numBuckets);

public:
	// Inserts an element, disallowing duplicates
	template <typename U>
	void Insert(U&& element);

	// Removes the element if it exists in the set
	template <typename U>
	void Remove(U&& element);

private:
	Bucket& GetBucket(T element);

private:
	std::vector<Bucket> m_buckets;
	size_t m_numBuckets;
	std::hash<T> m_hash;
};

template<typename T>
inline MyHashSet<T>::MyHashSet(size_t numBuckets) :
	m_numBuckets(numBuckets)
{
	// Set up the table so we have desired number of buckets
	m_buckets.resize(numBuckets);
}

template<typename T>
template<typename U>
inline void MyHashSet<T>::Insert(U&& element)
{
	// Retreive the correct bucket
	Bucket& bucket = GetBucket(std::forward<U>(element));

	// Find the element in the bucket
	auto it = std::find(bucket.m_elements.begin(), bucket.m_elements.end(), std::forward<U>(element));

	// Insert the element if it doesn't already exist
	if (it == bucket.m_elements.end())
	{
		bucket.m_elements.push_back(std::forward<U>(element));
	}
}

template<typename T>
template<typename U>
inline void MyHashSet<T>::Remove(U&& element)
{
	// Retreive the correct bucket
	Bucket& bucket = GetBucket(std::forward<U>(element));

	// Find the element in the bucket
	auto it = std::find(bucket.m_elements.begin(), bucket.m_elements.end(), std::forward<U>(element));

	// Erase the element if it exists
	if (it != bucket.m_elements.end())
	{
		bucket.m_elements.erase(it);
	}
}

template<typename T>
inline MyHashSet<T>::Bucket& MyHashSet<T>::GetBucket(T element)
{
	// Hash the key
	auto hashValue = m_hash(element) % m_numBuckets;

	// Get the correct bucket & return
	return m_buckets[hashValue];
}