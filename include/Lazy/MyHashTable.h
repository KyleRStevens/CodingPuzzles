#pragma once

// Standard
#include <vector>
#include <algorithm>

template <typename K, typename V>
class MyHashTable
{
public:
	class Bucket
	{
	public:
		std::vector<std::pair<K, V>> m_elements;
	};

public:
	MyHashTable(size_t numBuckets);

public:
	// Inserts a new key,value pair
	template <typename Uk, typename Uv>
	void Insert(Uk&& key, Uv&& value);

	// Gets the value given a key
	template <typename Uk>
	V GetValue(Uk&& key);

	// Inserts a key,value pair
	template <typename Uk>
	void Remove(Uk&& key);

private:
	Bucket& GetBucket(K key);

private:
	std::vector<Bucket> m_buckets;
	size_t m_numBuckets;
	std::hash<K> m_hash;
};

template<typename K, typename V>
inline MyHashTable<K, V>::MyHashTable(size_t numBuckets) :
	m_numBuckets(numBuckets)
{
	// Set up the table so we have desired number of buckets
	m_buckets.resize(numBuckets);
}

template<typename K, typename V>
template <typename Uk, typename Uv>
inline void MyHashTable<K, V>::Insert(Uk&& key, Uv&& value)
{
	// Retrieve the bucket
	Bucket& bucket = GetBucket(std::forward<Uk>(key));

	// Find the key in the bucket
	K keyToFind = std::forward<Uk>(key);
	auto it = std::find_if(bucket.m_elements.begin(), bucket.m_elements.end(), [keyToFind](const std::pair<K, V>& element) {
		return element.first == keyToFind;
	});
	
	// Determine if the key is already in the bucket
	if (it != bucket.m_elements.end())
	{
		// Key already exists, update the value
		(*it).second = std::forward<Uv>(value);
	}
	else
	{
		// Key doesn't exist, add a new pair
		std::pair<K, V> newPair(std::forward<Uk>(key), std::forward<Uv>(value));
		bucket.m_elements.push_back(newPair);
	}
}

template<typename K, typename V>
template<typename Uk>
inline V MyHashTable<K, V>::GetValue(Uk&& key)
{
	// Retrieve the bucket
	Bucket& bucket = GetBucket(std::forward<Uk>(key));

	// Find the key in the bucket
	K keyToFind = std::forward<Uk>(key);
	auto it = std::find_if(bucket.m_elements.begin(), bucket.m_elements.end(), [keyToFind](const std::pair<K, V>& element) {
		return element.first == keyToFind;
	});
	
	// Return the value of the key - assuming it exists
	if (it != bucket.m_elements.end())
	{
		return (*it).second;
	}

	// Should NOT occur...
	return V();
}

template<typename K, typename V>
template<typename Uk>
inline void MyHashTable<K, V>::Remove(Uk&& key)
{
	// Retrieve the bucket
	Bucket& bucket = GetBucket(std::forward<Uk>(key));

	// Find the key in the bucket
	K keyToFind = std::forward<Uk>(key);
	auto it = std::find_if(bucket.m_elements.begin(), bucket.m_elements.end(), [keyToFind](const std::pair<K, V>& element) {
		return element.first == keyToFind;
	});

	// Remove the element if it exists
	if (it != bucket.m_elements.end())
	{
		bucket.m_elements.erase(it);
	}
}

template<typename K, typename V>
inline MyHashTable<K, V>::Bucket& MyHashTable<K, V>::GetBucket(K key)
{
	// Hash the key
	auto hashValue = m_hash(key) % m_numBuckets;

	// Get the correct bucket & return
	return m_buckets[hashValue];
}