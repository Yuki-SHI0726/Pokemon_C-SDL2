// MusicReferee.cpp
// Zixuan Shi
// Control all mix_music 

#include "MusicReferee.h"
#include "MusicConstants.h"

#include <iostream>

MusicReferee::MusicReferee()
	: m_currentMusicNumber{0}
{
}

//////////////////////////////////////////////
// Load a music, then add the music to vector
//////////////////////////////////////////////
void MusicReferee::AddMusicSequence(const char* filePath)
{
	Mix_Music* pNewMusic = Mix_LoadMUS(filePath);
	if (pNewMusic == nullptr)
	{
		std::cout << "Failed to load music. Error: " << Mix_GetError() << std::endl;
	}
	else
	{
		Mix_PlayMusic(pNewMusic, -1);
	}

	m_musicTracks.emplace_back(pNewMusic);
}

/////////////////////////////////////////////
// Play the music
/////////////////////////////////////////////
void MusicReferee::PlayMusic()
{
	Mix_VolumeMusic(kRoarVolume);
	UpdateMusicIndex();
	Mix_FadeInMusic(m_musicTracks.at(m_currentMusicNumber), kLoops, kFadeMS);
}

void MusicReferee::Update(double deltaTime)
{
	if (!Mix_PlayingMusic() && !Mix_PausedMusic())
	{
		Mix_HaltMusic();
		UpdateMusicIndex();
		Mix_FadeInMusic(m_musicTracks.at(m_currentMusicNumber), kLoops, kFadeMS);
	}
}

///////////////////////////////////////////////////////////////////////
// If the index is the end of the vector. Set it back to the beginning
///////////////////////////////////////////////////////////////////////
void MusicReferee::UpdateMusicIndex()
{
	++m_currentMusicNumber;

	// If current Playing music is the last element in music track 
	if (m_currentMusicNumber == m_musicTracks.size())
	{
		m_currentMusicNumber = 0;
	}

	Mix_PlayMusic(m_musicTracks.at(m_currentMusicNumber), -1);
}

//////////////////////////////////////////////
// Free the music in vector
//////////////////////////////////////////////
void MusicReferee::CleanUp()
{
	for (auto& music : m_musicTracks)
	{
		Mix_FreeMusic(music);
	}
}
