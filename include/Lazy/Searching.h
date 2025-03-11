#pragma once

// Standard
#include <vector>
#include <type_traits>
#include <set>
#include <queue>

// Searches a smallest to largest sorted list for the target value (returns the index or -1 if not found)
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, int>::type
BinarySearch(std::vector<T>& sortedList, T target, int startingLeftIndex = 0, int startingRightIndex = -1)
{
    int targetIndex = -1;
    int iLeft = startingLeftIndex;
    int iRight = startingRightIndex;
    if (iRight == -1)
    {
        iRight = sortedList.size() - 1;
    }

    // Do the binary search
    while (iLeft <= iRight)
    {
		// Get middle index
        int iMiddle = ((iRight - iLeft) / 2) + iLeft;

		// Check value
        if (sortedList[iMiddle] == target)
        {
			// We found it; set the target index and break out of the search loop
            targetIndex = iMiddle;
            break;
        }
        else if (sortedList[iMiddle] < target)
        {
			// Target is to the right (higher value)
            iLeft = iMiddle + 1;
        }
		else // (sortedList[iMiddle] > target)
        {
			// Target is to the left (lower value)
            iRight = iMiddle - 1;
        }
    }

    return targetIndex;
}

template <typename T>
struct Node
{
    T value;
    std::set<Node*> connections;
};

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, Node<T>*>::type
DepthFirstSearchHelper(Node<T>* pNode, const T& target, std::set<Node<T>*>& visitedNodes)
{
    Node<T>* result = nullptr;

    // If this node has already been visited, just return immediately
    if (visitedNodes.find(pNode) == visitedNodes.end())
    {
        // Check if this node is the target (is so, return pNode)
        if (pNode->value == target)
        {
            return pNode;
        }

        // Mark as visited
        visitedNodes.insert(pNode);

        // For each connection from this node, recurse
        for (Node<T>* pConnection : pNode->connections)
        {
            result = DepthFirstSearchHelper(pConnection, target, visitedNodes);
            if (result != nullptr)
            {
                // Return the find!
                return result;
            }
        }
    }

    return result;
}

// Given a pointer to a start node and a target value, returns a pointer to the node with the target value (or nullptr of not found)
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, Node<T>*>::type
DepthFirstSearch(Node<T>* pNode, const T target)
{
    std::set<Node<T>*> visitedNodes;
    Node<T>* result = nullptr;
    
    result = DepthFirstSearchHelper(pNode, target, visitedNodes);

    return result;
}

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, Node<T>*>::type
BreadthFirstSearchHelper(Node<T>* pNode, const T& target, std::set<Node<T>*>& visitedNodes, std::queue<Node<T>*>& searchQueue)
{
    Node<T>* result = nullptr;

    // If this node has already been visited, just return immediately
    if (visitedNodes.find(pNode) == visitedNodes.end())
    {
        // Check if this node is the target (is so, return pNode)
        if (pNode->value == target)
        {
            return pNode;
        }

        // Mark as visited
        visitedNodes.insert(pNode);

        // For each connection from this node, add to the queue to be searched
        for (Node<T>* pConnection : pNode->connections)
        {
            if (visitedNodes.find(pConnection) == visitedNodes.end())
            {
                searchQueue.push(pConnection);
            }
        }
    }
    else
    {
        // Should not get hit...
        int x = 5;
    }

    return result;
}

// Given a pointer to a start node and a target value, returns a pointer to the node with the target value (or nullptr of not found)
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, Node<T>*>::type
BreadthFirstSearch(Node<T>* pNode, const T target)
{
    std::set<Node<T>*> visitedNodes;
    Node<T>* result = nullptr;

    std::queue<Node<T>*> searchQueue;
    searchQueue.push(pNode);

    while (result == nullptr && searchQueue.empty() == false)
    {
        result = BreadthFirstSearchHelper(searchQueue.front(), target, visitedNodes, searchQueue);
        searchQueue.pop();
    }

    return result;
}