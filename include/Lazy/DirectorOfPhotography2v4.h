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
* Optimizations from v3:
    - Build as you go...
*/

class Solution_DirectorOfPhotography2v4
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
    int m_maxKnownIndex = -1;

private:
    void addKnown(char type, int index)
    {
        if (index > m_maxKnownIndex)
        {
            switch (type)
            {
            case 'P':
                m_photographerIndices.Add(index);
                break;

            case 'A':
                m_actorIndices.Add(index);
                break;

            case 'B':
                m_backdropIndices.Add(index);
                break;

            default:
                break;
            }

            m_maxKnownIndex++;
        }
    }

    int getNext(char type, std::string& C, int minIndex, int maxIndex)
    {
        KnownIndices* pKnownIndices;

        // Determine knowns type
        switch (type)
        {
        case 'P':
            pKnownIndices = &m_photographerIndices;
            break;

        case 'A':
            pKnownIndices = &m_actorIndices;
            break;

        case 'B':
            pKnownIndices = &m_backdropIndices;
            break;

        default:
            // Unknown type, no valid index exists
            return -1;
            break;
        }

        // If (at least part of) the search range is already known, search through the already known elements
        if (minIndex < m_maxKnownIndex) // Technically this should be '<=' but if its the last known index, it'll be found first thing below
        {
            // Find the first photographer in the known photographers that is within the desired range (TODO: Binary search for the min index)
            int indexOfMinKnownIndexOfThisType = pKnownIndices->GetMinIndexInRange(minIndex, maxIndex);

            if (indexOfMinKnownIndexOfThisType >= 0)
            {
                // There is a known index of this type - return it
                return indexOfMinKnownIndexOfThisType;
            }

            // No photographers were found in the known portion of the desired range, update the search range to cut out the portion already searched, then continue searching the unknown area
            minIndex = m_maxKnownIndex; // Would need to be 'maxKnownIndex + 1' if we used '<=' above...
        }

        // Make the unknown area known up to the current search point
        for (int i = m_maxKnownIndex + 1; i < minIndex; ++i)
        {
            // Save each item to our known indices lists
            addKnown(C[i], i);
        }

        // Continue searching the unknown area
        for (int i = minIndex; i < maxIndex; ++i)
        {
            // Save what we now know as we go
            addKnown(C[i], i);

            // Return the index of the first element matching the desired type
            if (C[i] == type)
            {
                return i;
            }
        }
    }

public:
    int countValidPhotos(char leftType, std::string& C, int X, int Y) // O(N^2 * logN)
    {
        int artisticPhotoCount = 0;
        KnownIndices* pLeftTypeIndices = nullptr;
        KnownIndices* pRightTypeIndices = nullptr;
        char rightType = '.';

        // Get left & right types
        switch (leftType)
        {
        case 'P':
            pLeftTypeIndices = &m_photographerIndices;
            pRightTypeIndices = &m_backdropIndices;
            rightType = 'B';
            break;

        case 'B':
            pLeftTypeIndices = &m_backdropIndices;
            pRightTypeIndices = &m_photographerIndices;
            rightType = 'P';
            break;

        default:
            // Invalid case - return 0 immediately
            return 0;
            break;
        }

        // For each "leftType" (while the next "leftType" index is in range)
        int leftTypeIndex = getNext(leftType, C, 0, C.size());
        while (leftTypeIndex > 0 && leftTypeIndex < C.size()) // O(max(P, B)) ==> O(N)
        {
            // Valid "rightType" range limits
            const int minValidRightTypeIndex = leftTypeIndex + X + X;
            const int maxValidRightTypeIndex = leftTypeIndex + Y + Y;

            // ??
            const int indexOfMinValidRightTypeIndex = pRightTypeIndices->GetMinIndexInRange(minValidRightTypeIndex, maxValidRightTypeIndex); // Yes, this is an index of an index (O(logN))
            const int indexOfMaxValidRightTypeIndex = pRightTypeIndices->GetMaxIndexInRange(minValidRightTypeIndex, maxValidRightTypeIndex); // Yes, this is an index of an index (O(logN))

            // For each valid "rightType" (while the next "rightType" index is in range)
            int rightTypeIndex = getNext(rightType, C, minValidRightTypeIndex, maxValidRightTypeIndex);
            while (rightTypeIndex > 0 && rightTypeIndex < C.size()) // O(min(P, B)) ==> O(N/2) ==> O(N)
            {
                // Find overlapping area of the photographer and backdrop valid actor ranges
                const int minValidActorIndex = std::max(leftTypeIndex + X, rightTypeIndex - Y);
                const int maxValidActorIndex = std::min(leftTypeIndex + Y, rightTypeIndex - X);

                // For each valid actor (get the number of actors in the calculated range)
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

        // Count up photos with the photographer on the left
        artisticPhotoCount += countValidPhotos('P', C, X, Y);

        // Count up photos with the photographer on the right (backdrop on the left)
        artisticPhotoCount += countValidPhotos('B', C, X, Y);

        // Return the number of artistic photos found
        return artisticPhotoCount;
    }
};