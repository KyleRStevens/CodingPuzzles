#pragma once

// Standard
#include <unordered_map>
#include <string>

class MyTrie
{
public:
	struct Node
	{
	public:
		Node(char character = '\0', bool isWord = false);

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