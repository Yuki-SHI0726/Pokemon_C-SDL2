// RandomNumberGenerator.cpp
// Zixuan Shi
// Generate true random number

#include "RandomNumberGenerator.h"

#include <iostream>

void RandomNumberGenerator::ClassNotes()
{
	std::mt19937 engine;

	// very slow, don't put in loop, maybe in constructor
	std::random_device randomDevice;

	unsigned int seed = randomDevice();
	engine.seed(seed);

	// this give the range of the random numebr generator, 1 and 6 inclusive
	// always assign range instead of use mod, it breaks the distribution
	// you can get negative random number from -10 to 10 by assign range (0, 20), and do: int randomNumebr = (int)distribution(engine) - 10;
	// same concept for generating randon float number
	std::uniform_int_distribution<unsigned int> distribution(1, 100);

	for (int i = 0; i < 15; ++i)
	{
		// getting random number of long length with no range assign
		/*std::cout << engine() << std::endl;*/

		// way to get random number after assign range
		unsigned int randomNumebr = distribution(engine);
		std::cout << randomNumebr << std::endl;
	}
}

///////////////////////////////////////
// Ctor without seed
///////////////////////////////////////
RandomNumberGenerator::RandomNumberGenerator()
	: m_engine{ }
{
	std::random_device randomDevice;
	unsigned int seed = randomDevice();
	m_engine.seed(seed);

#ifdef _DEBUG
	std::cout << "Random Seed:" << seed << std::endl;
#endif
}

///////////////////////////////////////
// Ctor with a seed
///////////////////////////////////////
RandomNumberGenerator::RandomNumberGenerator(unsigned int seed)
	: m_engine{}
{
	m_engine.seed(seed); 
}

////////////////////////////////////////////////////////////
// A function that returns an int within a specified range.
////////////////////////////////////////////////////////////
int RandomNumberGenerator::GenerateRandomInt(int lowerBound, int upperBound)
{
	std::uniform_int_distribution<unsigned int> distribution(lowerBound, upperBound);
	int randomNumber = distribution(m_engine);
	return randomNumber;
}

////////////////////////////////////////////////////////////
// A function that returns a float within a specified range.
////////////////////////////////////////////////////////////
float RandomNumberGenerator::GenerateRandomFloat(float lowerBound, float upperBound)
{
	std::uniform_real_distribution<float> distribution(lowerBound, upperBound);
	float randomNumber = distribution(m_engine);
	return randomNumber;
}