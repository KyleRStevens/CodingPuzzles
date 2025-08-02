#pragma once

// Standard
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <stack>
#include <unordered_set>
#include <vector>
#include <queue>

// Meta Puzzle: Portals
class Solution_Portals
{
private:
    struct Coordinates
    {
        int row;
        int col;
    };

    struct Node
    {
        void MakeConnection(Coordinates coordinate, std::vector<std::vector<char>>& G)
        {
            if (coordinate.row >= 0 && coordinate.row < G.size())
            {
                if (coordinate.col >= 0 && coordinate.col < G[0].size())
                {
                    connections.push_back(coordinate);
                }
            }
        }

        char type = '.';
        bool visited = false;
        int minDistance = std::numeric_limits<int>::max();
        std::vector<Coordinates> connections;
    };

public:
    int getSecondsRequired(std::vector<std::vector<char>>& G)
    {
        Coordinates startCoordinate{ -1, -1 };

        // Create the empty graph
        std::vector<std::vector<Node>> graph;
        graph.resize(G.size());
        for (auto& column : graph)
        {
            column.resize(G[0].size());
        }

        // Create 26 vectors - one for each portal ID (a-z)
        std::vector<std::vector<Coordinates>> portals;
        portals.resize(26);

        // Build the graph
        for (int row = 0; row < G.size(); ++row)
        {
            for (int col = 0; col < G[row].size(); ++col)
            {
                Node& cell = graph[row][col];

                // Give the cell its type
                cell.type = G[row][col];

                // Make coordinate connections to the adjacent cells (up, down, left, right) - if they are valid
                cell.MakeConnection({ row - 1, col }, G);
                cell.MakeConnection({ row + 1, col }, G);
                cell.MakeConnection({ row, col - 1 }, G);
                cell.MakeConnection({ row, col + 1 }, G);

                // If this cell is a letter a-z, list its coordinate in the corresponding portals container for that letter
                if (cell.type >= 'a' && cell.type <= 'z')
                {
                    portals[cell.type - 'a'].push_back({row, col});
                }
                else if (cell.type == 'S')
                {
                    startCoordinate = { row, col };
                    cell.minDistance = 0;
                }
            }
        }

        // Find shortest path using BFS (sufficient when all weights are 1)
        Node* pCurrentCell = &graph[startCoordinate.row][startCoordinate.col];
        std::queue<Node*> nodesToCheck;
        nodesToCheck.push(pCurrentCell);
        while (nodesToCheck.empty() == false)
        {
            // Visit the next cell in the queue
            pCurrentCell = nodesToCheck.front();

            // If this cell has not yet been visited
            if (pCurrentCell->visited == false)
            {
                // Check for destination
                if (pCurrentCell->type == 'E')
                {
                    // Exit found!
                    return pCurrentCell->minDistance;
                }

                // Mark the cell as visited
                pCurrentCell->visited = true;

                // This cell is only valid to continue with if it is not a wall
                if (pCurrentCell->type != '#')
                {
                    // Update all chilren's minDistance and add them to the queue
                    for (Coordinates& coordinate : pCurrentCell->connections)
                    {
                        Node& cell = graph[coordinate.row][coordinate.col];

                        // Update the min distance
                        cell.minDistance = std::min(cell.minDistance, (pCurrentCell->minDistance + 1));

                        // Add child to queue
                        nodesToCheck.push(&cell);
                    }

                    // If it is a portal, also add all portal children
                    if (pCurrentCell->type >= 'a' && pCurrentCell->type <= 'z')
                    {
                        for (auto& coordinate : portals[pCurrentCell->type - 'a'])
                        {
                            Node& cell = graph[coordinate.row][coordinate.col];

                            // Update the min distance
                            cell.minDistance = std::min(cell.minDistance, (pCurrentCell->minDistance + 1));

                            // Add child to queue
                            nodesToCheck.push(&cell);
                        }
                    }
                }
            }
            
            // Remove cell from queue
            nodesToCheck.pop();
        }

        // No exit found, return -1
        return -1;
    }

    void Test()
    {
        std::vector<std::vector<char>> portalsGrid3{
            {'a', 'S', '.', 'b'},
            {'#', '#', '#', '#'},
            {'E', 'b', '.', 'a'}
        };
        auto portalsResult = getSecondsRequired(portalsGrid3);
    }
};