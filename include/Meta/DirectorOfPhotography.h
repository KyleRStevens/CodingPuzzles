#pragma once

// Standard
#include <cstdint>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

// Meta Puzzle: Director of Photography
class Solution_DirectorOfPhotography
{
public:
    struct Node
    {
    public:
        Node(int index) : m_index(index) { /* Do nothing */ }

    public:
        int m_index;
        std::vector<Node*> m_children;
    };

public:
    int getArtisticPhotographCount(int N, std::string C, int X, int Y) // O(N + P*A*B) i.e. not quite O(N^3) but still pretty bad
    {
        int artisticPhotoCount = 0;
        std::vector<Node> photographerNodes;
        std::vector<Node> actorNodes;
        std::vector<Node> backdropNodes;

        // Reserve space for efficiency
        photographerNodes.reserve(C.size());
        actorNodes.reserve(C.size());
        backdropNodes.reserve(C.size());

        // Create graph nodes for each P|A|B cell type (capturing their indices too)
        for (int i = 0; i < C.size(); ++i) // O(N)
        {
            if (C[i] == 'P')
            {
                photographerNodes.emplace_back(i);
            }
            else if (C[i] == 'A')
            {
                actorNodes.emplace_back(i);
            }
            else if (C[i] == 'B')
            {
                backdropNodes.emplace_back(i);
            }
        }

        // Build valid photographer to actor connections
        for (Node& photographerNode : photographerNodes) // O(P)
        {
            // Get distance to each actor & build connections for the valid ones
            for (Node& actorNode : actorNodes) // O(A)
            {
                int distance = std::abs(photographerNode.m_index - actorNode.m_index);
                if (distance >= X && distance <= Y)
                {
                    // The actor has a valid distance from the phographer, so add it as a child of the photographer
                    photographerNode.m_children.push_back(&actorNode);
                }
            }
        }

        // Build valid actor to backdrop connections
        for (Node& actorNode : actorNodes) // O(A)
        {
            for (Node& backdropNode : backdropNodes) // O(B)
            {
                int distance = std::abs(actorNode.m_index - backdropNode.m_index);
                if (distance >= X && distance <= Y)
                {
                    // The backdrop has a valid distance from the actor, so add it as a child of the actor
                    actorNode.m_children.push_back(&backdropNode);
                }
            }
        }

        // Traverse the graph counting up how many valid paths there are
        for (Node& photographerNode : photographerNodes) // O(P)
        {
            // We already know the distances are valid, so we just need to make sure the directions are the same (i.e. d_PA * d_AB > 0)
            for (Node* pActorNode : photographerNode.m_children) // O(A)
            {
                int distance_PA = photographerNode.m_index - pActorNode->m_index;
                for (Node* pBackdropNode : pActorNode->m_children) // O(B)
                {
                    int distance_AB = pActorNode->m_index - pBackdropNode->m_index;
                    if (distance_PA * distance_AB > 0)
                    {
                        artisticPhotoCount++;
                    }
                }
            }
        }

        // Return the number of artistic photos found
        return artisticPhotoCount;
    }

    void Test()
    {
        std::string directorOfPhotographyCells = ".PBAAP.B";
        auto directorOfPhotographyResult = getArtisticPhotographCount(directorOfPhotographyCells.size(), directorOfPhotographyCells, 1, 3);
    }
};