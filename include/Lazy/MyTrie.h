#pragma once

// Standard
#include <unordered_map>
#include <string>

class MyTrie
{
public:
	class Node
	{
	public:
		Node(char character = '\0', bool isWord = false) :
			m_value(character),
			m_isWord(false)
		{
			// Do nothing
		}

	public:
		char m_value = '\0';
		bool m_isWord = false;
		std::unordered_map<char, Node*> m_children;
	};

public:
	void Insert(std::string& word);

	Node* Find(std::string& word);

public:
	Node m_rootNode;
};

void MyTrie::Insert(std::string& word)
{
	Node* pCurrentNode = &m_rootNode;

	// For each character in the word
	for (char& character : word)
	{
		// If the character is a child of the current node
		if (pCurrentNode->m_children.find(character) != pCurrentNode->m_children.end())
		{
			// Move the current node to it
			pCurrentNode = pCurrentNode->m_children[character];
		}
		else // If the character is NOT a child of the current node
		{
			// Add it as a child (and move the current node to it)
			Node* pNodeToInsert = new Node(character);
			pCurrentNode->m_children[character] = pNodeToInsert;
			pCurrentNode = pNodeToInsert;
		}
	}

	// Mark the last node as a full word
	if (pCurrentNode != nullptr)
	{
		pCurrentNode->m_isWord = true;
	}
}

MyTrie::Node* MyTrie::Find(std::string& word)
{
	Node* pCurrentNode = &m_rootNode;

	// For each character in the word
	for (char& character : word)
	{
		// If the character is a child of the current node
		if (pCurrentNode->m_children.find(character) != pCurrentNode->m_children.end())
		{
			// Move the current node to it
			pCurrentNode = pCurrentNode->m_children[character];
		}
		else // If the character is NOT a child of the current node
		{
			// The word is not in the Trie
			return nullptr;
		}
	}

	// Return the final character node of the word
	if (pCurrentNode != nullptr)
	{
		return pCurrentNode;
	}
	
	// This should never get hit
	return nullptr;
}