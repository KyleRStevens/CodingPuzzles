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

// Meta Puzzle: Uniform Integers
class Solution_UniformIntegers
{
public:
	enum class Direction
	{
		ABOVE,
		BELOW
	};

private:
	void chopUpNumber(long long number, int& mostSignificantDigit, int& maxDigit, int& numDigits, bool& isUniform)
	{
		// Initialize these values
		maxDigit = 0;
		numDigits = 1;
		isUniform = true;
		const int anyGivenDigit = number % 10;

		// While there are still multiple digits...
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

	int countUniformsAboveOrBelow(const long long number, const int numDigits, const Direction direction)
	{
		int numUniforms = 0;
		long long currentUniform = 0;

		// Get the lowest (all 1s) uniform for the current number of digits
		for (int i = 0; i < numDigits; ++i)
		{
			currentUniform *= 10;
			currentUniform += 1;
		}

		// For each uniform with this many digits, count up how many are in the desired direction of (or equal to) the input number
		for (int i = 1; i < 10; ++i)
		{
			if (direction == Direction::ABOVE)
			{
				// For each uniform with this many digits, count up how many are >= the input number
				if ((currentUniform * i) >= number)
				{
					numUniforms++;
				}
			}
			else // (direction == Direction::BELOW)
			{
				// For each uniform with this many digits, count up how many are <= the input number
				if ((currentUniform * i) <= number)
				{
					numUniforms++;
				}
			}
		}

		// Return how many uniforms we counted to be in the desired direction of (or equal to) the input number
		return numUniforms;
	}

	int countUniformsBetween(const long long A, const long long B, const int numDigits)
	{
		int numUniforms = 0;
		long long currentUniform = 0;

		// Get the lowest (all 1s) uniform for the current number of digits
		for (int i = 0; i < numDigits; ++i)
		{
			currentUniform *= 10;
			currentUniform += 1;
		}

		// For each uniform with this many digits, count up how many are between (or equal to) the input numbers
		for (int i = 1; i < 10; ++i)
		{
			// For each uniform with this many digits, count up how many are >= the input number
			if ((currentUniform * i) >= A && (currentUniform * i) <= B)
			{
				numUniforms++;
			}
		}

		// Return how many uniforms we counted to be in the desired direction of (or equal to) the input number
		return numUniforms;
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

		// Add in the number of uniform ints for each order of magnitude between A & B
		int magnitudesBetween = std::abs(numDigitsInB - numDigitsInA); // Technically the abs is unnecessary because the constraints say B >= A
		magnitudesBetween = std::max(0, magnitudesBetween - 1);
		int uniformsBetween = 9 * magnitudesBetween; // Each full "magnitude" has 9 uniform ints

		// New strategy for counting the above and belows of the edge magnitudes
		int uniformsInEdgeMagnitudes = 0;
		if (numDigitsInA == numDigitsInB)
		{
			uniformsInEdgeMagnitudes += countUniformsBetween(A, B, numDigitsInA);
		}
		else
		{
			uniformsInEdgeMagnitudes += countUniformsAboveOrBelow(A, numDigitsInA, Direction::ABOVE);
			uniformsInEdgeMagnitudes += countUniformsAboveOrBelow(B, numDigitsInB, Direction::BELOW);
		}

		// Return the sum of all the uniform section counts
		return uniformsInEdgeMagnitudes + uniformsBetween;
	}

	void Test()
	{
		auto uniformIntegersResult = getUniformIntegerCountInInterval(1, 888'888'888'887); // Max: 1'000'000'000'000
	}
};