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
    - When searching for connections, choose the smaller search space between the valid distance cells and the total number of things you're searching for (search the smaller space)
    - Save indices instead of pointers
*/

class Solution_DirectorOfPhotography2
{
public:
    struct Node
    {
    public:
        Node(uint32_t initIndex) : index(initIndex) { /* Do nothing */ }

    public:
        uint32_t index;
        bool hasConnectorFromAhead = false;  // We don't care who, just if it has a connection or not
        bool hasConnectorFromBehind = false; // We don't care who, just if it has a connection or not
        std::vector<uint32_t> forwardChildren;
        std::vector<uint32_t> backwardChildren;
    };

private:
    void createBackwardsConnection(std::vector<Node>& allNodes, uint32_t fromIndex, uint32_t toIndex)
    {
        // Create the backwards connection
        allNodes[fromIndex].backwardChildren.push_back(toIndex);

        // Flag the 'to' node as connected to from ahead
        allNodes[toIndex].hasConnectorFromAhead = true;
    }

    void createForwardsConnection(std::vector<Node>& allNodes, uint32_t fromIndex, uint32_t toIndex)
    {
        // Create the forward connection
        allNodes[fromIndex].forwardChildren.push_back(toIndex);

        // Flag the 'to' node as connected to from behind
        allNodes[toIndex].hasConnectorFromBehind = true;
    }

public:
    int getArtisticPhotographCount(int N, std::string& C, int X, int Y) // O(N + P*(Y-X) + A*(Y-X) + P*A) where 'Y-X' cound be up to N, so O(N + P*N + A*N + P*A) ==> O(P*N + A*N) i.e. O(N^2) since P or A could be ~N
    {
        int artisticPhotoCount = 0;
        std::vector<Node> allNodes;
        std::vector<uint32_t> photographerIndices;
        std::vector<uint32_t> actorIndices;
        std::vector<uint32_t> backdropIndices;

        // Reserve space for efficiency (with memory limitations, we will guess at a lower amount of space)
        allNodes.reserve(C.size());
        //photographerIndices.reserve(C.size() / 4);
        //actorIndices.reserve(C.size() / 4);
        //backdropIndices.reserve(C.size() / 4);

        // Create graph nodes for each P|A|B cell type (capturing their indices too)
        for (int i = 0; i < C.size(); ++i) // O(N)
        {
            // Initialize each node (including empty nodes) with its index in C
            allNodes.emplace_back(i);

            // Keep a list of all P|A|B types (keep pointers to those nodes)
            switch (C[i])
            {
            case 'P':
                photographerIndices.emplace_back(i);
                break;

            case 'A':
                actorIndices.emplace_back(i);
                break;

            case 'B':
                backdropIndices.emplace_back(i);
                break;

            default:
                break;
            }
        }

        // Determine the number of cells/nodes within the valid distance of a given node being checked (we'll see if this is more or less than the number of nodes of the type we're looking for, and search through whichever is less)
        int numValidDistanceNodes = ((Y - X) + 1) * 2;

        // Build valid photographer to actor connections
        for (uint32_t photographerIndex : photographerIndices) // O(P)
        {
            // Determine the search strategy (for searching for valid actors)
            if (numValidDistanceNodes < actorIndices.size()) // There are more actors to search through than valid cells to search through
            {
                // Find any actors within the valid distance BEHIND the photographer
                int minCheckIndex = std::max(static_cast<int>(photographerIndex) - Y, 0);
                int maxCheckIndex = static_cast<int>(photographerIndex) - X;
                for (int i = minCheckIndex; i <= maxCheckIndex; ++i) // O(Y-X)
                {
                    // If the cell/node is an actor
                    if (C[i] == 'A')
                    {
                        // Create the backwards connection
                        createBackwardsConnection(allNodes, photographerIndex, i);
                    }
                }

                // Find any actors within the valid distance AHEAD OF the photographer
                minCheckIndex = photographerIndex + X;
                maxCheckIndex = std::min(static_cast<int>(photographerIndex) + Y, static_cast<int>(C.size() - 1));
                for (int i = minCheckIndex; i <= maxCheckIndex; ++i) // O(Y-X)
                {
                    // If the cell/node is an actor
                    if (C[i] == 'A')
                    {
                        // Create the forwards connection
                        createForwardsConnection(allNodes, photographerIndex, i);
                    }
                }
            }
            else // (numValidDistanceNodes >= numActors) i.e. there are more cells to search through than total actors (so just search through the actors)
            {
                // For each actor
                for (uint32_t actorIndex : actorIndices)
                {
                    // Get the distance(s)
                    int distance = static_cast<int>(photographerIndex) - static_cast<int>(actorIndex);
                    int absDistance = std::abs(distance);

                    // If it is a valid distance away
                    if (absDistance >= X && absDistance <= Y)
                    {
                        // Check the direction
                        if (distance > 0)
                        {
                            // Create the backwards connection
                            createBackwardsConnection(allNodes, photographerIndex, actorIndex);
                        }
                        else // (distance < 0)
                        {
                            // Create the forwards connection
                            createForwardsConnection(allNodes, photographerIndex, actorIndex);
                        }
                    }
                }
            }
        }

        // Build valid actor to backdrop connections
        for (uint32_t actorIndex : actorIndices) // O(A)
        {
            // Determine the search strategy (for searching for valid backdrops)
            if (numValidDistanceNodes < backdropIndices.size())
            {
                // If the actor has no valid photographer ahead of them, no point in looking for backdrops behind it
                if (allNodes[actorIndex].hasConnectorFromAhead)
                {
                    // Find any backdrops within the valid distance BEHIND the actor
                    int minCheckIndex = std::max(static_cast<int>(actorIndex) - Y, 0);
                    int maxCheckIndex = static_cast<int>(actorIndex) - X;
                    for (int i = minCheckIndex; i <= maxCheckIndex; ++i) // O(Y-X)
                    {
                        // If the cell/node is a backdrop
                        if (C[i] == 'B')
                        {
                            // Create the backwards connection
                            createBackwardsConnection(allNodes, actorIndex, i);
                        }
                    }
                }

                // If the actor has no valid photographer behind them, no point in looking for backdrops ahead of them
                if (allNodes[actorIndex].hasConnectorFromBehind)
                {
                    // Find any backdrops within the valid distance AHEAD OF the actor
                    int minCheckIndex = actorIndex + X;
                    int maxCheckIndex = std::min(static_cast<int>(actorIndex) + Y, static_cast<int>(C.size() - 1));
                    for (int i = minCheckIndex; i <= maxCheckIndex; ++i) // O(Y-X)
                    {
                        // If the cell/node is a backdrop
                        if (C[i] == 'B')
                        {
                            // Create the forwards connection
                            createForwardsConnection(allNodes, actorIndex, i);
                        }
                    }
                }
            }
            else // (numValidDistanceNodes >= backdropIndices.size())
            {
                // For each backdrop
                for (uint32_t backdropIndex : backdropIndices)
                {
                    // Get the distance(s)
                    int distance = static_cast<int>(actorIndex) - static_cast<int>(backdropIndex);
                    int absDistance = std::abs(distance);

                    // If it is a valid distance away
                    if (absDistance >= X && absDistance <= Y)
                    {
                        // Check which direction
                        if (distance > 0)
                        {
                            // Create the backwards connection
                            createBackwardsConnection(allNodes, actorIndex, backdropIndex);
                        }
                        else // (distance < 0)
                        {
                            // Create the forwards connection
                            createForwardsConnection(allNodes, actorIndex, backdropIndex);
                        }
                    }
                }
            }
        }

        // Traverse the graph counting up how many valid paths there are
        for (uint32_t photographerIndex : photographerIndices) // O(P)
        {
            // Count the valid backward-facing photos
            for (uint32_t actorIndex : allNodes[photographerIndex].backwardChildren) // O(A)
            {
                artisticPhotoCount += allNodes[actorIndex].backwardChildren.size();
            }

            // Count the valid forward-facing photos
            for (uint32_t actorIndex : allNodes[photographerIndex].forwardChildren) // O(A)
            {
                artisticPhotoCount += allNodes[actorIndex].forwardChildren.size();
            }
        }

        // Return the number of artistic photos found
        return artisticPhotoCount;
    }
};