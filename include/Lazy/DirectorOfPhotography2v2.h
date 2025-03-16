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

class Solution_DirectorOfPhotography2v2
{
private:
    int countEmUp(std::string& C, int X, int Y, char leftType, char rightType)
    {
        int artisticPhotoCount = 0;

        // For each photographer in C
        for (int i = 0; i < C.size(); ++i)
        {
            if (C[i] == leftType)
            {
                // Photographer limits
                int backdropLimitMin = i + X + X;
                int backdropLimitMax = i + Y + Y;

                // For each Backdrop (in valid limits)
                for (int j = backdropLimitMin; j <= backdropLimitMax && j < C.size(); ++j)
                {
                    if (C[j] == rightType)
                    {
                        // Find valid overlapping area in between
                        int actorLimitMin = std::max(i + X, j - Y);
                        int actorLimitMax = std::min(i + Y, j - X);

                        // Count the number of artists in that overlapping area
                        for (int k = actorLimitMin; k <= actorLimitMax && k < C.size(); ++k)
                        {
                            if (C[k] == 'A')
                            {
                                artisticPhotoCount++;
                            }
                        }
                    }
                }
            }
        }

        // Return the number of artistic photos found
        return artisticPhotoCount;
    }

public:
    int getArtisticPhotographCount(int N, std::string& C, int X, int Y)
    {
        int artisticPhotoCount = 0;

        // Count the valid photos with the photographer on the left and the backdrop on the right
        artisticPhotoCount += countEmUp(C, X, Y, 'P', 'B');

        // Count the valid photos with the backdrop on the left and the photographer on the right
        artisticPhotoCount += countEmUp(C, X, Y, 'B', 'P');

        // Return the number of artistic photos found
        return artisticPhotoCount;
    }
};