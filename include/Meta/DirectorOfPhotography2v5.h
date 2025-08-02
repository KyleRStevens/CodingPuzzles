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

// Meta Puzzle: Director of Photography 2
class Solution_DirectorOfPhotography2v5
{
public:
    long long getArtisticPhotographCount(int N, std::string& C, int X, int Y) // O(N)
    {
        long long artisticPhotoCount = 0;

        // Rolling counters
        int photographtersLeftOfActor = 0;
        int photographtersRightOfActor = 0;
        int backdropsLeftOfActor = 0;
        int backdropsRightOfActor = 0;

        // For each char (cell) in the string
        for (int actorCheckIndex = 0 - Y; actorCheckIndex < static_cast<int>(C.size()); ++actorCheckIndex) // O(2N) ==> O(N)
        {
            // Check items ENTERING the RIGHT window area
            int enterRightIndex = actorCheckIndex + Y;
            if (enterRightIndex >= 0 && enterRightIndex < C.size())
            {
                if (C[enterRightIndex] == 'P')
                {
                    photographtersRightOfActor++;
                }
                else if (C[enterRightIndex] == 'B')
                {
                    backdropsRightOfActor++;
                }
            }

            // Check items ENTERING the LEFT window area
            int enterLeftIndex = actorCheckIndex - X;
            if (enterLeftIndex >= 0 && enterLeftIndex < C.size())
            {
                if (C[enterLeftIndex] == 'P')
                {
                    photographtersLeftOfActor++;
                }
                else if (C[enterLeftIndex] == 'B')
                {
                    backdropsLeftOfActor++;
                }
            }

            // Check items LEAVING the RIGHT window area
            int leaveRightIndex = actorCheckIndex + X - 1;
            if (leaveRightIndex >= 0 && leaveRightIndex < C.size())
            {
                if (C[leaveRightIndex] == 'P')
                {
                    photographtersRightOfActor--;
                }
                else if (C[leaveRightIndex] == 'B')
                {
                    backdropsRightOfActor--;
                }
            }

            // Check items LEAVING the LEFT window area
            int leaveLeftIndex = actorCheckIndex - Y - 1;
            if (leaveLeftIndex >= 0 && leaveLeftIndex < C.size())
            {
                if (C[leaveLeftIndex] == 'P')
                {
                    photographtersLeftOfActor--;
                }
                else if (C[leaveLeftIndex] == 'B')
                {
                    backdropsLeftOfActor--;
                }
            }

            // Look at the check index (center of sliding window)
            if (actorCheckIndex >= 0 && actorCheckIndex < C.size())
            {
                if (C[actorCheckIndex] == 'A')
                {
                    // Add the number of valid photos
                    artisticPhotoCount += (photographtersLeftOfActor * backdropsRightOfActor);
                    artisticPhotoCount += (photographtersRightOfActor * backdropsLeftOfActor);
                }
            }
        }

        // Return the number of artistic photos found
        return artisticPhotoCount;
    }

    void Test()
    {
        std::string directorOfPhotography2Cells = "B...A...P.....P";
        auto directorOfPhotography2Result = getArtisticPhotographCount(directorOfPhotography2Cells.size(), directorOfPhotography2Cells, 1, 300'000);
    }
};