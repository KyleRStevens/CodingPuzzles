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

/*
* Optimizations from v1:
    - When looking for valid connections, don't even check the indices closer than X or farther than Y
    - Give directionality to connections so traversing the graph doesn't go through invalid paths before it checks if the "directions match" (it will be inherent)
    - No point in building A->B connections if A isn't connected to a P
*/

class Solution_DirectorOfPhotography2
{
public:
    struct Node
    {
    public:
        Node(char initType, int initIndex) : type(initType), index(initIndex) { /* Do nothing */ }

    public:
        char type;
        int index;
        bool hasConnectorFromAhead = false;  // We don't care who, just if it has a connection or not
        bool hasConnectorFromBehind = false; // We don't care who, just if it has a connection or not
        std::vector<Node*> forwardChildren;
        std::vector<Node*> backwardChildren;
    };

public:
    int getArtisticPhotographCount(int N, std::string& C, int X, int Y) // O(N + P*(Y-X) + A*(Y-X) + P*A) where 'Y-X' cound be up to N, so O(N + P*N + A*N + P*A) ==> O(P*N + A*N) i.e. O(N^2) since P or A could be ~N
    {
        int artisticPhotoCount = 0;
        std::vector<Node> allNodes;
        std::vector<Node*> photographerNodes;
        std::vector<Node*> actorNodes;
        std::vector<Node*> backdropNodes;

        // Reserve space for efficiency (with memory limitations, we will guess at a lower amount of space)
        allNodes.reserve(C.size());
        photographerNodes.reserve(C.size() / 3);
        actorNodes.reserve(C.size() / 3);
        backdropNodes.reserve(C.size() / 3);

        // Create graph nodes for each P|A|B cell type (capturing their indices too)
        for (int i = 0; i < C.size(); ++i) // O(N)
        {
            // Initialize each node (including empty nodes) with its type and index in C
            allNodes.emplace_back(C[i], i);

            // Keep a list of all P|A|B types (keep pointers to those nodes)
            if (C[i] == 'P')
            {
                photographerNodes.emplace_back(&allNodes[i]);
            }
            else if (C[i] == 'A')
            {
                actorNodes.emplace_back(&allNodes[i]);
            }
            else if (C[i] == 'B')
            {
                backdropNodes.emplace_back(&allNodes[i]);
            }
        }

        // Build valid photographer to actor connections
        for (Node* pPhotographer : photographerNodes) // O(P)
        {
            const int photographerIndex = pPhotographer->index;

            // Find any actors within the valid distance BEHIND the photographer
            int minCheckIndex = std::max(photographerIndex - Y, 0);
            int maxCheckIndex = photographerIndex - X;
            for (int i = minCheckIndex; i <= maxCheckIndex; ++i) // O(Y-X)
            {
                // If the cell/node is an actor
                if (allNodes[i].type == 'A')
                {
                    // Create the backwards connection
                    pPhotographer->backwardChildren.push_back(&allNodes[i]);

                    // Flag the actor as connected to from ahead
                    allNodes[i].hasConnectorFromAhead = true;
                }
            }

            // Find any actors within the valid distance AHEAD OF the photographer
            minCheckIndex = photographerIndex + X;
            maxCheckIndex = std::min(photographerIndex + Y, static_cast<int>(allNodes.size() - 1));
            for (int i = minCheckIndex; i <= maxCheckIndex; ++i) // O(Y-X)
            {
                // If the cell/node is an actor
                if (allNodes[i].type == 'A')
                {
                    // Create the forwards connection
                    pPhotographer->forwardChildren.push_back(&allNodes[i]);

                    // Flag the actor as connected to from behind
                    allNodes[i].hasConnectorFromBehind = true;
                }
            }
        }

        // Build valid actor to backdrop connections
        for (Node* pActor : actorNodes) // O(A)
        {
            const int actorIndex = pActor->index;

            // If the actor has no valid photographer ahead of them, no point in looking for backdrops behind it
            if (pActor->hasConnectorFromAhead)
            {
                // Find any backdrops within the valid distance BEHIND the actor
                int minCheckIndex = std::max(actorIndex - Y, 0);
                int maxCheckIndex = actorIndex - X;
                for (int i = minCheckIndex; i <= maxCheckIndex; ++i) // O(Y-X)
                {
                    // If the cell/node is a backdrop
                    if (allNodes[i].type == 'B')
                    {
                        // Create the backwards connection
                        pActor->backwardChildren.push_back(&allNodes[i]);

                        // Flag the backdrop as connected to from ahead
                        allNodes[i].hasConnectorFromAhead = true;
                    }
                }
            }

            // If the actor has no valid photographer behind them, no point in looking for backdrops ahead of them
            if (pActor->hasConnectorFromBehind)
            {
                // Find any backdrops within the valid distance AHEAD OF the actor
                int minCheckIndex = actorIndex + X;
                int maxCheckIndex = std::min(actorIndex + Y, static_cast<int>(allNodes.size() - 1));
                for (int i = minCheckIndex; i <= maxCheckIndex; ++i) // O(Y-X)
                {
                    // If the cell/node is a backdrop
                    if (allNodes[i].type == 'B')
                    {
                        // Create the backwards connection
                        pActor->forwardChildren.push_back(&allNodes[i]);

                        // Flag the backdrop as connected to from behind
                        allNodes[i].hasConnectorFromBehind = true;
                    }
                }
            }
        }

        // Traverse the graph counting up how many valid paths there are
        for (Node* pPhotographer : photographerNodes) // O(P)
        {
            // Count the valid backward-facing photos
            for (Node* pActorNode : pPhotographer->backwardChildren) // O(A)
            {
                artisticPhotoCount += pActorNode->backwardChildren.size();
            }

            // Count the valid forward-facing photos
            for (Node* pActorNode : pPhotographer->forwardChildren) // O(A)
            {
                artisticPhotoCount += pActorNode->forwardChildren.size();
            }
        }

        // Return the number of artistic photos found
        return artisticPhotoCount;
    }
};