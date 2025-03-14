#pragma once

// Standard
#include <vector>
#include <iostream>
#include <unordered_set>
#include <set>
#include <stack>
#include <cstdint>
#include <map>
#include <mutex>

// Solving 20/33 test cases... I have no idea what's wrong yet...
class Solution_UniformIntegers
{
private:
	void chopUpNumber(long long number, int& mostSignificantDigit, int& maxDigit, int& numDigits, bool& isUniform)
	{
		// Initialize these values
		maxDigit = 0;
		numDigits = 1;
		isUniform = true;
		const int anyGivenDigit = number % 10;

		while (number > 9)
		{
			// Get the current least significant digit to update the max digit value
			int currentLeastSignificantDigit = number % 10;
			if (currentLeastSignificantDigit > maxDigit)
			{
				maxDigit = currentLeastSignificantDigit;
			}

			// If any digit is different from any other, this number is NOT uniform
			if (anyGivenDigit != currentLeastSignificantDigit)
			{
				isUniform = false;
			}

			// Chop off the least significant digit
			number /= 10;

			// Incriment the digits counter
			numDigits++;
		}

		// Return the most significant digit to the caller
		mostSignificantDigit = static_cast<int>(number);

		// Inlude the final digit in the max (this isn't necessary, but it makes the values less confusing)
		maxDigit = std::max(maxDigit, mostSignificantDigit);

		// Remember to include the final digit in the check for uniformity
		if (anyGivenDigit != mostSignificantDigit)
		{
			isUniform = false;
		}
	}

public:
	int getUniformIntegerCountInInterval(long long A, long long B)
	{
		// Get the most significant digit in A, the max digit in A, and the number of digits in A (also flagging if the number itself is uniform cause otherwise that screws up some of the math)
		int mostSignificantDigitInA = 0;
		int maxDigitInA = 0;
		int numDigitsInA = 1;
		bool isUniformA = false;
		chopUpNumber(A, mostSignificantDigitInA, maxDigitInA, numDigitsInA, isUniformA);

		// Do the same for B
		int mostSignificantDigitInB = 0;
		int maxDigitInB = 0;
		int numDigitsInB = 1;
		bool isUniformB = false;
		chopUpNumber(B, mostSignificantDigitInB, maxDigitInB, numDigitsInB, isUniformB);

		// Get the number of uniform ints above A for that many of digits
		int uniformsAboveA = 9 - mostSignificantDigitInA;
		if (maxDigitInA <= mostSignificantDigitInA)
		{
			uniformsAboveA += 1;
		}

		// Do the same for B (but them do 9 minus that value to get the number below B - factoring in if the number itself is uniform!)
		int uniformsBelowB = 0;
		int uniformsAboveB = 9 - mostSignificantDigitInB;
		if (maxDigitInB <= mostSignificantDigitInB)
		{
			uniformsAboveB += 1;
		}
		uniformsBelowB = 9 - uniformsAboveB;
		if (isUniformB)
		{
			// If B is uniform, than it will itself be included even when we flip the direction we're looking (doing the '9 - uniformsAboveB' for changing above to below)
			uniformsBelowB += 1;
		}

		// Add in the number of uniform ints for each order of magnitude between A & B
		int magnitudesBetween = std::abs(numDigitsInB - numDigitsInA); // Technically the abs is unnecessary because the constraints say B >= A
		magnitudesBetween = std::max(0, magnitudesBetween - 1);
		int uniformsBetween = 9 * magnitudesBetween; // Each full "magnitude" has 9 uniform ints

		// If the two numbers have the same "magnitude", you don't want to double count their uniform ints
		int uniformsInEdgeMagnitudes = uniformsAboveA + uniformsBelowB;
		if (numDigitsInA == numDigitsInB)
		{
			// Get the number of items NOT included in the 'above A' section (see below)
			int uniformsNotAboveA = 9 - uniformsAboveA;

			// Get the number of items NOT included in the 'below B' section (see below)
			int uniformsNotBelowB = 9 - uniformsBelowB;
			
			// Since there is an overlap, count up the items that AREN'T included in the 2 above sections (they'll never overlap), and then we can easily see the number of overlapping items to include by looking at its "inverse" (below)
			int uniformsNotIncluded = uniformsNotAboveA + uniformsNotBelowB;

			// Then just take the "inverse" of that to get all the overlapped items that ARE included
			uniformsInEdgeMagnitudes = 9 - uniformsNotIncluded;
		}

		// Return the sum of all the uniform section counts
		return uniformsInEdgeMagnitudes + uniformsBetween;
	}
};