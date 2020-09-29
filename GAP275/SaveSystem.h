// SaveSystem.h
// Zixuan Shi
// Save and Load game system

#pragma once
#include "Vector2D.h"
#include <string>

////////////////////////////////
// Save and Load game
////////////////////////////////
class SaveSystem
{
public:
	struct SaveData
	{
		std::string m_level;		// Gameplay scene, Combat scene	// Change to char[]

		// Game play scene
		Vector2D m_playerPosition;
		int m_pokeballDepot;	
		Vector2D m_enemyPosition;

		// Combat scene
		bool m_isFightingCharmander;
		double m_playerHp;		
		double m_enemyHp;
	};

private:
	size_t m_saveGameTimes;
	SaveData m_data;
	bool m_isLoaded;
	size_t m_saveSlot;	
	size_t m_totalSaveGameCount;	// the total number how many save files do we have currently

	static constexpr char s_kDirectory[] = "saves\\";
	static constexpr char s_kFileName[] = "FileSave.save";

public:
	SaveSystem(size_t saveSlot);
	~SaveSystem();

	// Save the file. Returns true if successful
	bool Save(size_t gameSlot = -1);

	// Load the file. Returns true if successful
	bool Load();

	std::string GetSaveSlotString();

	size_t ReturnSavesFileCount();

	bool GetIsLoaded() const { return m_isLoaded; }
	SaveData& GetData() { return m_data; }
	size_t GetSaveSlot() const { return m_saveSlot; }
	size_t GetTotalSaveSlotAmount() const { return m_totalSaveGameCount; }

	void SetClosed() { m_isLoaded = false; }
};