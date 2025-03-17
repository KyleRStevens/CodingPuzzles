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
    - 
*/

class Solution_DirectorOfPhotography2v3
{
public:
    class KnownIndices
    {
    private:
        enum class Direction
        {
            ABOVE,
            BELOW
        };

    private:
        int BinarySearch(int value, Direction rangeDirection)
        {
            int iLeft = 0;
            int iRight = m_indices.size() - 1;
            int checkIndex = -1;

            // Find the index of the closest value to the minValue
            while (iLeft <= iRight)
            {
                // Update the check index
                checkIndex = ((iRight - iLeft) / 2) + iLeft;

                // Update the search space
                if (value < m_indices[checkIndex])
                {
                    iRight = checkIndex - 1;
                }
                else if (value > m_indices[checkIndex])
                {
                    iLeft = checkIndex + 1;
                }
                else
                {
                    // If we hit the value exactly, return the current check index immediately
                    return checkIndex;
                }
            }

            // If we did NOT find the value exactly, return either the previous or next index (depending on which the caller desires)
            if (checkIndex >= 0 && m_indices[checkIndex] < value && rangeDirection == Direction::ABOVE)
            {
                checkIndex++;
            
                if (checkIndex >= m_indices.size())
                {
                    checkIndex = -1;
                }
            }
            else if (checkIndex >= 0 && m_indices[checkIndex] > value && rangeDirection == Direction::BELOW)
            {
                checkIndex--;
            }

            // Return the closest valid value (or -1 if no valid value exists)
            return checkIndex;
        }

    public:
        void Add(int index) { m_indices.push_back(index); }

        int GetMinIndexInRange(int minValue, int maxValue)
        {
            int index = BinarySearch(minValue, Direction::ABOVE);

            // If the index is not even valid, return -1
            if (index < 0 || index >= m_indices.size())
            {
                return -1;
            }

            // If the index is valid, but the corresponding value is outside the desired range, return -1
            if (m_indices[index] < minValue || m_indices[index] > maxValue)
            {
                index = -1;
            }
            return index;
        }

        int GetMaxIndexInRange(int minValue, int maxValue)
        {
            int index = BinarySearch(maxValue, Direction::BELOW);

            // If the index is not even valid, return -1
            if (index < 0 || index >= m_indices.size())
            {
                return -1;
            }

            // If the index is valid, but the corresponding value is outside the desired range, return -1
            if (m_indices[index] < minValue || m_indices[index] > maxValue)
            {
                index = -1;
            }
            return index;
        }

        size_t Size() { return m_indices.size(); }

    public:
        int operator[] (int index) { return m_indices[index]; }

    private:
        std::vector<int> m_indices;
    };

private:
    KnownIndices m_photographerIndices;
    KnownIndices m_actorIndices;
    KnownIndices m_backdropIndices;

public:
    int countValidPhotos(char leftType, std::string& C, int X, int Y) // O(N^2 * logN)
    {
        int artisticPhotoCount = 0;
        KnownIndices* pLeftTypeIndices = nullptr;
        KnownIndices* pRightTypeIndices = nullptr;

        // Get left & right types
        switch (leftType)
        {
        case 'P':
            pLeftTypeIndices = &m_photographerIndices;
            pRightTypeIndices = &m_backdropIndices;
            break;

        case 'B':
            pLeftTypeIndices = &m_backdropIndices;
            pRightTypeIndices = &m_photographerIndices;
            break;

        default:
            // Invalid case - return 0 immediately
            return 0;
            break;
        }

        // For each "leftType"
        for (int i = 0; i < pLeftTypeIndices->Size(); ++i) // O(max(P, B)) ==> O(N)
        {
            const int leftTypeIndex = (*pLeftTypeIndices)[i];

            // Valid "rightType" range limits
            const int minValidRightTypeIndex = leftTypeIndex + X + X;
            const int maxValidRightTypeIndex = leftTypeIndex + Y + Y;

            // For each valid "rightType"
            const int indexOfMinValidRightTypeIndex = pRightTypeIndices->GetMinIndexInRange(minValidRightTypeIndex, maxValidRightTypeIndex); // Yes, this is an index of an index (O(logN))
            const int indexOfMaxValidRightTypeIndex = pRightTypeIndices->GetMaxIndexInRange(minValidRightTypeIndex, maxValidRightTypeIndex); // Yes, this is an index of an index (O(logN))
            for (int j = indexOfMinValidRightTypeIndex; j <= indexOfMaxValidRightTypeIndex && j >= 0; ++j) // O(min(P, B)) ==> O(N/2) ==> O(N)
            {
                const int rightTypeIndex = (*pRightTypeIndices)[j];

                // Find overlapping area of the photographer and backdrop valid actor ranges
                const int minValidActorIndex = std::max(leftTypeIndex + X, rightTypeIndex - Y);
                const int maxValidActorIndex = std::min(leftTypeIndex + Y, rightTypeIndex - X);

                // For each valid actor
                const int indexOfMinValidActorIndex = m_actorIndices.GetMinIndexInRange(minValidActorIndex, maxValidActorIndex); // Yes, this is also an index of an index (O(logN))
                const int indexOfMaxValidActorIndex = m_actorIndices.GetMaxIndexInRange(minValidActorIndex, maxValidActorIndex); // Yes, this is also an index of an index (O(logN))
                if (indexOfMinValidActorIndex >= 0)
                {
                    // Add the number of valid actors to the count
                    const int numValidActors = indexOfMaxValidActorIndex - indexOfMinValidActorIndex + 1;
                    artisticPhotoCount += numValidActors;
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

        // Build adjacency list
        for (int i = 0; i < C.size(); ++i) // O(N)
        {
            switch (C[i])
            {
            case 'P':
                m_photographerIndices.Add(i);
                break;

            case 'A':
                m_actorIndices.Add(i);
                break;

            case 'B':
                m_backdropIndices.Add(i);
                break;

            default:
                break;
            }
        }

        // Count up photos with the photographer on the left
        artisticPhotoCount += countValidPhotos('P', C, X, Y);

        // Count up photos with the photographer on the right (backdrop on the left)
        artisticPhotoCount += countValidPhotos('B', C, X, Y);

        // Return the number of artistic photos found
        return artisticPhotoCount;
    }
};