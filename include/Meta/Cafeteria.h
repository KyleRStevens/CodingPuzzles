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

// Meta Puzzle: Cafeteria
class Solution_Cafeteria
{
public:
    long long getMaxAdditionalDinersCount(long long N, long long K, int M, std::vector<long long>& S) // O(N)
    {
        long long maxAdditionalSitters = 0;
        const long long spaceRequiredForEachSitter = (K + 1); // When considering overlapping areas, you only count the area on one side
        long long leftBounds = 1;
        long long rightBounds = N;
        long long numAvailableSeatsInArea = (rightBounds - leftBounds) + 1;
        long long maxSittersForArea = 0;

        // Sort the seatNumber array
        std::sort(S.begin(), S.end());

        // For each current sitter (each seatNumber in the vector 'S'), calculate how many new sitters can fit in the space to their left
        long long prevSeatNumber = 0;
        for (long long i = 0; i < S.size(); ++i) // O(N)
        {
            long long seatNumber = S[i];

            // Get the bounds of the entire area left of the current sitter (left of seatNumber)
            leftBounds = prevSeatNumber + 1;
            rightBounds = seatNumber - 1;

            // Trim off the area blocked by the previous sitter (Note: You do NOT need to trim the "right" side blocked by the current sitter as it is mathemtically accounted for by the space required for each sitter!)
            // In other words, only trim the "buffer" seats from one side of the empty seating section, or else you'll double count the required buffer area
            if (i == 0)
            {
                // The left bounds of the area left of the first sitter is always going to be 1 (no need to compensate for K)
                leftBounds = 1;
            }
            else
            {
                leftBounds += K;
            }

            // With the new available area, determine the max new sitters for that area
            numAvailableSeatsInArea = (rightBounds - leftBounds) + 1;
            maxSittersForArea = numAvailableSeatsInArea / spaceRequiredForEachSitter; // Floor by truncation

            // Add to counter
            maxAdditionalSitters += maxSittersForArea;

            // Update previous seat number
            prevSeatNumber = seatNumber;
        }

        // We've now added up all possible new sitters for the available spaces except the far right space, so we'll include that now
        {
            // Get the bounds of the entire area (no need to compensate for K here!)
            leftBounds = prevSeatNumber + 1;
            rightBounds = N;

            // With the new available area, determine the max new sitters for that area
            numAvailableSeatsInArea = (rightBounds - leftBounds) + 1;
            maxSittersForArea = numAvailableSeatsInArea / spaceRequiredForEachSitter; // Floor by truncation

            // Add to counter
            maxAdditionalSitters += maxSittersForArea;
        }

        // Return the calculated amount
        return maxAdditionalSitters;
    }

    void Test()
    {
        std::vector<long long> cafeteriaOccupiedSeats{ 2, 6 };
        auto cafeteriaResult = getMaxAdditionalDinersCount(10, 1, cafeteriaOccupiedSeats.size(), cafeteriaOccupiedSeats);
    }
};