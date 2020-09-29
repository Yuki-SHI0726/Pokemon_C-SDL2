// MusicReferee.h
// Zixuan Shi
// Control all mix_music 

#pragma once

#include <SDL_mixer.h>
#include <vector>

/////////////////////////////////////////
// Music Referee for sound tracks
/////////////////////////////////////////
class MusicReferee
{
private:
	// All currently music
	std::vector<Mix_Music*> m_musicTracks;

	// Index of the current Music.
	int m_currentMusicNumber;

public:
	MusicReferee();

	// Adds a new Music
	void AddMusicSequence(const char* filePath);

	// Play a music
	void PlayMusic();

	// Update the music
	void Update(double deltaTime);

	// Alternates tracks (track A plays, then track B, then repeat)
	void UpdateMusicIndex();

	// Clean up
	void CleanUp();
};

