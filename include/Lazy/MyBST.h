#pragma once

class BinarySearchTree
{
public:
	class Node
	{
	public:
		Node(int value) :
			m_value(value)
		{
			// Do nothing
		}

	public:
		int m_value = -1;
		Node* m_pParentNode = nullptr;
		Node* m_pLeftNode = nullptr;
		Node* m_pRightNode = nullptr;
	};

public:
	void Insert(int value);

	Node* Find(int value);

	Node* FindMax(Node* pStartingNode);
	
	Node* FindMin(Node* pStartingNode);

	void Delete(int value);

public:
	Node* m_pTopNode = nullptr;
};

void BinarySearchTree::Insert(int value)
{
	// If the tree is empty, this will simply be the top node
	if (m_pTopNode == nullptr)
	{
		m_pTopNode = new Node(value);
		return;
	}

	// Otherwise, we have to find the correct position to insert
	Node* pCurrentNode = m_pTopNode;
	Node* pPreviousNode = nullptr;
	while (pCurrentNode != nullptr)
	{
		// Save the previous node
		pPreviousNode = pCurrentNode;

		// Traverse and update the current node
		if (pCurrentNode->m_value > value)
		{
			// Go left
			pCurrentNode = pCurrentNode->m_pLeftNode;
		}
		else if (pCurrentNode->m_value < value)
		{
			// Go right
			pCurrentNode = pCurrentNode->m_pRightNode;
		}
		else // (pCurrentNode->m_value == value)
		{
			// The values already exists and we currently don't support duplicates, so just return immediately
			return;
		}
	}

	// We've found the insert position, so let's insert
	if (pPreviousNode->m_value > value)
	{
		pPreviousNode->m_pLeftNode = new Node(value);
		pPreviousNode->m_pLeftNode->m_pParentNode = pPreviousNode;
	}
	else // (pPreviousNode->m_value < value)
	{
		pPreviousNode->m_pRightNode = new Node(value);
		pPreviousNode->m_pRightNode->m_pParentNode = pPreviousNode;
	}
}

BinarySearchTree::Node* BinarySearchTree::Find(int value)
{
	Node* pTargetNode = nullptr;

	// Traverse
	Node* pCurrentNode = m_pTopNode;
	while (pCurrentNode != nullptr)
	{
		// Traverse and update the current node
		if (pCurrentNode->m_value > value)
		{
			// Go left
			pCurrentNode = pCurrentNode->m_pLeftNode;
		}
		else if (pCurrentNode->m_value < value)
		{
			// Go right
			pCurrentNode = pCurrentNode->m_pRightNode;
		}
		else // (pCurrentNode->m_value == value)
		{
			// Found!
			pTargetNode = pCurrentNode;
			break;
		}
	}

	// Not found, so return the nullptr
	return pTargetNode;
}

BinarySearchTree::Node* BinarySearchTree::FindMax(BinarySearchTree::Node* pStartingNode)
{
	// Traverse (only going right)
	Node* pCurrentNode = pStartingNode;
	while (pCurrentNode->m_pRightNode != nullptr)
	{
		pCurrentNode = pCurrentNode->m_pRightNode;
	}

	// The current node is the largest
	return pCurrentNode;
}

BinarySearchTree::Node* BinarySearchTree::FindMin(BinarySearchTree::Node* pStartingNode)
{
	// Traverse (only going left)
	Node* pCurrentNode = pStartingNode;
	while (pCurrentNode->m_pLeftNode != nullptr)
	{
		pCurrentNode = pCurrentNode->m_pLeftNode;
	}

	// The current node is the smallest
	return pCurrentNode;
}

void BinarySearchTree::Delete(int value)
{
	// Find the target node
	Node* pTargetNode = Find(value);

	// If not found, just return
	if (pTargetNode == nullptr)
	{
		return;
	}

	// Find the largest left value OR the smallest right node from the target node to use as the value to swap in
	Node* pSwapNode = FindMax(pTargetNode->m_pLeftNode);
	if (pSwapNode == nullptr)
	{
		// The deleted node has no left nodes, so let's find the smallest right node instead
		pSwapNode = FindMin(pTargetNode->m_pRightNode);
	}
	if (pSwapNode == nullptr)
	{
		// The deleted node has no right nodes either, so we just remove it
		if (pTargetNode->m_pParentNode->m_value > value)
		{
			pTargetNode->m_pParentNode->m_pLeftNode = nullptr;
		}
		else // (pTargetNode->m_pParentNode->m_value < value)
		{
			pTargetNode->m_pParentNode->m_pRightNode = nullptr;
		}
		return;
	}

	// Change the target node's value to that of the swap node
	pTargetNode->m_value = pSwapNode->m_value;

	// Prune the swap node from the tree
	if (pSwapNode->m_pParentNode->m_value > value)
	{
		pSwapNode->m_pParentNode->m_pLeftNode = nullptr;
	}
	else // (pSwapNode->m_pParentNode->m_value < value)
	{
		pSwapNode->m_pParentNode->m_pRightNode = nullptr;
	}
	pSwapNode->m_pParentNode = nullptr;

	// Re-insert every node under the swap node back into to the tree (deleting them as you go?)
	Node* pCurrentNode = pSwapNode;
	while (pCurrentNode != nullptr) // TODO
	{
		// If it has a left node
		if (pCurrentNode->m_pLeftNode)
		{
			// Go into that node and loop again
			pCurrentNode = pCurrentNode->m_pLeftNode;
			continue;
		}

		// If it has a right node
		if (pCurrentNode->m_pRightNode)
		{
			// Go into that node and loop again
			pCurrentNode = pCurrentNode->m_pRightNode;
			continue;
		}

		// Insert the node's value back into the tree
		Insert(pCurrentNode->m_value);
		
		// Delete the node and go back to the parent and loop again
		Node* pNodeToDelete = pCurrentNode;
		pCurrentNode = pCurrentNode->m_pParentNode;
		if (pCurrentNode && pCurrentNode->m_value > pNodeToDelete->m_value)
		{
			pCurrentNode->m_pLeftNode = nullptr;
		}
		else if (pCurrentNode) // (pCurrentNode->m_value < pNodeToDelete->m_value)
		{
			pCurrentNode->m_pRightNode = nullptr;
		}
		delete pNodeToDelete;
	}
}