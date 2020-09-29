// SaveSystem.cpp
// Zixuan Shi
// Save and Load game system

#include "SaveSystem.h"

#include <direct.h>
#include <fstream>
#include <iostream>
#include <string>

// For time
#include <ctime>
#include <chrono>

SaveSystem::SaveSystem(size_t saveSlot)
	: m_isLoaded{ false }
	, m_data{}
	, m_saveGameTimes{0}
	, m_saveSlot{ saveSlot }
	, m_totalSaveGameCount{ 0 }
{
	m_totalSaveGameCount = ReturnSavesFileCount();
}

SaveSystem::~SaveSystem()
{
}

bool SaveSystem::Save(size_t gameSlot)
{
	// Make sure the directory exists
	int returnValue = _mkdir(s_kDirectory);
	++m_saveGameTimes;

	//------------------------------------------------------------------------------------------------------------------------------
	// Combine the directory and file name
	//------------------------------------------------------------------------------------------------------------------------------
	std::string path;
	// If it's a new game
	if (gameSlot != -1)
	{
		path = s_kDirectory + std::string(s_kFileName) + std::to_string(gameSlot);
	}
	else
	{
		path = s_kDirectory + std::string(s_kFileName) + std::to_string(m_saveSlot);
	}
	
	std::ofstream fileOutput;
	fileOutput.open(path, std::ios::out, std::ios::binary);
	if (!fileOutput.is_open())
	{
		std::cout << "Failed to open file " << path << std::endl;
		return false;
	}


	//------------------------------------------------------------------------------------------------------------------------------
	// Get Time
	//------------------------------------------------------------------------------------------------------------------------------
	time_t clock = time(nullptr);
	std::tm now;
	localtime_s(&now, &clock);	// Converts given time since epoch


	//------------------------------------------------------------------------------------------------------------------------------
	// Write the data
	//------------------------------------------------------------------------------------------------------------------------------
	// Level
	fileOutput.write(m_data.m_level.c_str(), m_data.m_level.size()) << std::endl;
	
	// Time
	std::string date = std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_year + 1900);
	std::string time = std::to_string(now.tm_hour) + ":" + std::to_string(now.tm_min) + ":" + std::to_string(now.tm_sec);

	fileOutput.write(date.c_str(), date.size()) << std::endl;	// Write in date
	fileOutput.write(time.c_str(), time.size()) << std::endl;	// Write in time

	// Save game times
	std::string saveTimes = std::to_string(m_saveGameTimes);
	fileOutput.write(saveTimes.c_str(), saveTimes.size()) << std::endl;

	// Whole data
	if (m_data.m_level == "Gameplay")
	{
		// Save player position
		fileOutput << m_data.m_playerPosition.m_x << std::endl;
		fileOutput << m_data.m_playerPosition.m_y << std::endl;

		// pokeball
		fileOutput << m_data.m_pokeballDepot << std::endl;

		// enemy position
		fileOutput << m_data.m_enemyPosition.m_x << std::endl;
		fileOutput << m_data.m_enemyPosition.m_y << std::endl;
	}
	else if (m_data.m_level == "Combat")
	{
		// #DG: if you ever want to expand on this game in the future, you would want to save this in a different way that doesn't depend on the state and opponent in combat
		// Is fighting charmander
		fileOutput << ((m_data.m_isFightingCharmander) ? ("Yes") : ("No")) << std::endl;

		// Player Hp
		fileOutput << m_data.m_playerHp << std::endl;

		// Enemy hp
		fileOutput << m_data.m_enemyHp << std::endl;
	}

	fileOutput.close();	// Close the file

	return true;
}

bool SaveSystem::Load()
{
	// Combine the directory and file name
	std::string path = s_kDirectory + std::string(s_kFileName) + std::to_string(m_saveSlot);

	std::ifstream fileInput;
	fileInput.open(path, std::ios::in);
	if (!fileInput.is_open())
	{
		std::cout << "Failed to open file " << path << std::endl;
		return false;
	}


	// Read data
	char line[256];
	std::string info;

	// Read level
	fileInput.getline(line, 256);
	m_data.m_level = std::string(line);


	// skip date
	fileInput.getline(line, 256);


	// skip time
	fileInput.getline(line, 256);


	// read time
	fileInput.getline(line, 256);
	info = std::string(line);
	m_saveGameTimes = std::atoi(info.c_str());

 
	// data data
	if (m_data.m_level == "Gameplay")
	{
		// Save player position
		fileInput.getline(line, 256);
		info = std::string(line);
		m_data.m_playerPosition.m_x = std::atoi(info.c_str());

		fileInput.getline(line, 256);
		info = std::string(line);
		m_data.m_playerPosition.m_y = std::atoi(info.c_str());

		// pokeball
		fileInput.getline(line, 256);
		info = std::string(line);
		m_data.m_pokeballDepot = std::atoi(info.c_str());

		// enemy position
		fileInput.getline(line, 256);
		info = std::string(line);
		m_data.m_enemyPosition.m_x = std::atoi(info.c_str());

		fileInput.getline(line, 256);
		info = std::string(line);
		m_data.m_enemyPosition.m_y = std::atoi(info.c_str());
	}
	else if (m_data.m_level == "Combat")
	{
		// Is fighting charmander
		fileInput.getline(line, 256);
		info = std::string(line);
		m_data.m_isFightingCharmander = (info == "Yes");

		// Player Hp
		fileInput.getline(line, 256);
		info = std::string(line);
		m_data.m_playerHp = std::atoi(info.c_str());

		// Enemy hp
		fileInput.getline(line, 256);
		info = std::string(line);
		m_data.m_enemyHp = std::atoi(info.c_str());
	}
	
	// File close
	fileInput.close();

	m_isLoaded = true;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////
// Return a string that contains the info I need to print on the Save slot button
////////////////////////////////////////////////////////////////////////////////////
std::string SaveSystem::GetSaveSlotString()
{
	// Combine directory and file name.
	std::string path = s_kDirectory + std::string(s_kFileName) + std::to_string(m_saveSlot);

	std::ifstream file;
	file.open(path, std::ios::in);	// Open file.
	if (!file.is_open())
	{
		return "Empty";
	}

	std::string fileInput;

	// Get each line
	for (int i = 0; i < 3; ++i)
	{
		char line[256];
		file.getline(line, 256);
		fileInput.append(line);
		fileInput.append("\n");
	}

	char line[256];
	file.getline(line, 256);
	std::string saveTimeString = std::string(line);
	m_saveGameTimes = std::atoi(saveTimeString.c_str());
	fileInput += std::to_string(m_saveGameTimes);
	fileInput += " times saved\n";

	file.close();
	return fileInput;
}

////////////////////////////////////////////////////////
// Returns how many files do we have in save directory
////////////////////////////////////////////////////////
size_t SaveSystem::ReturnSavesFileCount()
{
	size_t count = 1;
	while (true)
	{
		// Combine directory and file name.
		std::string path = s_kDirectory + std::string(s_kFileName) + std::to_string(count);

		std::ifstream file;
		file.open(path, std::ios::in, std::ios::binary);	// Open file.
		if (file.is_open())
		{
			++count;
			file.close();
		}
		else
		{
			file.close();
			return count;
		}
	}
}
