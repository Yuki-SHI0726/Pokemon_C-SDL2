#pragma once

#include <random>
#include <iostream>

class RNG
{
	void note()
	{
		//------------------------------------------------------------------------------------------------------
		// Random
		//------------------------------------------------------------------------------------------------------
		std::mt19937 engine;

		// Seed
		std::random_device randomDevice;

		// Functor
		unsigned int seed = randomDevice();
		//engine.seed(seed);	// Random seed
		engine.seed(0);	// Same random number

		// This is slow. Just initial this in constructor 
		std::uniform_int_distribution<unsigned int> distribution(14000, 20000);

		// Testing
		for (int i = 0; i < 10; ++i)
		{
			float randomNumber = (float)distribution(engine) / 100.0f;
			std::cout << randomNumber << std::endl;
		}
		//------------------------------------------------------------------------------------------------------

	}
};

