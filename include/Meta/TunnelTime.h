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

class Solution_TunnelTime
{
private:
    struct Tunnel
    {
        long long length() { return trueEndPosition - trueStartPosition; }

        long long trueStartPosition = -1;
        long long trueEndPosition = -1;
        long long collapsedStartPosition = -1;
    };

private:
    Tunnel& findTunnel(long long remainderTime, std::vector<Tunnel>& tunnels)
    {
        int iLeft = 0;
        int iRight = tunnels.size() - 1;

        while (iLeft <= iRight)
        {
            int iMiddle = ((iRight - iLeft) / 2) + iLeft;
            Tunnel& tunnel = tunnels[iMiddle];
            long long tunnelCollapsedEndPosition = tunnel.collapsedStartPosition + tunnel.length();

            if (remainderTime > tunnel.collapsedStartPosition && remainderTime <= tunnelCollapsedEndPosition)
            {
                // Return the found tunnel
                return tunnels[iMiddle];
            }
            else if (remainderTime < tunnels[iMiddle].collapsedStartPosition)
            {
                iRight = iMiddle - 1;
            }
            else if (remainderTime == tunnel.collapsedStartPosition)
            {
                // Return the found tunnel
                return tunnels[iMiddle - 1];
            }
            else // (remainderTime > tunnelCollapsedEndPosition)
            {
                iLeft = iMiddle + 1;
            }
        }

        // This should not be hit as there should ALWAYS be a valid tunnel...
        return tunnels[0];
    }

public:
    long long getSecondsElapsed(long long C, std::vector<long long>& A, std::vector<long long>& B, long long K) // O(N*logN)
    {
        long long secondsElapsed = 0;

        // Create a container for the tunnel data
        std::vector<Tunnel> tunnels;
        tunnels.resize(A.size());

        // Put tunnel data into a container
        for (int i = 0; i < A.size(); ++i) // O(N)
        {
            Tunnel& tunnel = tunnels[i];

            tunnel.trueStartPosition = A[i];
            tunnel.trueEndPosition = B[i];
        }

        // Sort the tunnels by start position
        auto tunnelSort = [](Tunnel& A, Tunnel& B) { return A.trueStartPosition < B.trueStartPosition; };
        std::sort(tunnels.begin(), tunnels.end(), tunnelSort); // O(N*logN)

        // Get the collapsed start positions for each tunnel (start position without any gaps)
        long long currentStartPosition = 0;
        for (int i = 0; i < tunnels.size(); ++i) // O(N)
        {
            tunnels[i].collapsedStartPosition = currentStartPosition;
            currentStartPosition += tunnels[i].length();
        }

        // Determine the total tunnel time per track cycle
        long long tunnelTimePerCycle = currentStartPosition;

        // Determine number of cycles needed to reach K tunnel time (floor)
        long long numCycles = (K / tunnelTimePerCycle);
        if (K % tunnelTimePerCycle == 0)
        {
            // We have to subtract a cycle if the desired tunnel time is an even multiple of the tunnelTimePerCycle or else it will look like we need to finish the last full cycle instead of stopping at the end of the last tunnel
            numCycles--;
        }
        secondsElapsed += (numCycles * C);

        // Get the remaining desired tunnel time after the whole number of full cycles has been completed (if none, we already have our answer)
        long long remainingTunnelTime = K - (numCycles * tunnelTimePerCycle);
        if (remainingTunnelTime > 0)
        {
            // Search sorted/collapsed tunnel list for tunnel that reaches K
            Tunnel& tunnel = findTunnel(remainingTunnelTime, tunnels); // O(logN)

            // Determine the track position of that spot in the tunnel
            long long requiredExtraTravelTime = tunnel.trueStartPosition + (remainingTunnelTime - tunnel.collapsedStartPosition);

            // Add the extra time to our elapsed time
            secondsElapsed += requiredExtraTravelTime;
        }

        // Return the total driving time required to reach the desired tunnel time
        return secondsElapsed;
    }
};