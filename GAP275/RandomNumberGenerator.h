// RandomNumberGenerator.h
// Zixuan Shi
// Generate true random number

#pragma once

#include <random>
#include <assert.h>

////////////////////////////////////
// Module 11, Random Generator
////////////////////////////////////
class RandomNumberGenerator
{
public:


private:
	std::mt19937 m_engine;

public:
	// Without a specified seed 
	RandomNumberGenerator();

	// With a specified seed
	RandomNumberGenerator(unsigned int seed);

	// A function that returns an int within a specified range.
	int GenerateRandomInt(int lowerBound, int upperBound);

	// A function that returns a float within a specified range.
	float GenerateRandomFloat(float lowerBound, float upperBound);

	/////////////////////////////////////////////////////
	// Advanced feature of my choice.
	// Randomly generates a 0 to parameter's number
	// It's template as well
	/////////////////////////////////////////////////////
	template<class Type>
	Type GenerateRandomNumber(Type upperBound);

	void ClassNotes();
};

///////////////////////////////////////////////////////////
// Randomly returns a number depends on parameter's type
///////////////////////////////////////////////////////////
template<class Type>
Type RandomNumberGenerator::GenerateRandomNumber(Type upperBound)
{
	// Assure parameter is float or int type
	static_assert(std::is_integral_v<Type> || std::is_floating_point_v<Type>, "\nError: Random parameter must be int or float type");
	
	if (std::is_integral_v<Type>)
	{
		// If input is a int
		return GenerateRandomInt(static_cast<int>(0), static_cast<int>(upperBound));
	}
	else
	{
		// If input is a float
		return (Type)GenerateRandomFloat(static_cast<float>(0), static_cast<float>(upperBound));
	}
}
