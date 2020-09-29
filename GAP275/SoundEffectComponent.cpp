// SoundEffectComponent.cpp
// Zixuan Shi
// This component handles Sound effect playing

#include "SoundEffectComponent.h"

#include "SoundEffectReferee.h"
#include <assert.h>

SoundEffectComponent::SoundEffectComponent(GameObject* pOwner, SoundEffectReferee* pReferee)
	: m_pOwner(pOwner)
	, m_pSoundReferee(pReferee)
{
	m_pSoundReferee->AddActiveSoundEffect(this);
}

SoundEffectComponent::~SoundEffectComponent()
{
	// Free chunk
	for (auto& chunk : m_soundEffects)
	{
		Mix_FreeChunk(chunk);
	}

	m_pSoundReferee->RemoveActiveSoundEffect(this);
}

///////////////////////////////////////
// Add a sound according file path
///////////////////////////////////////
void SoundEffectComponent::AddSoundEffect(const char* filePath, int soundVolume)
{
	// Load the file path
	Mix_Chunk* pNewSoundEffect = Mix_LoadWAV(filePath);

	// Set the sound effect to appropriate volume
	Mix_VolumeChunk(pNewSoundEffect, soundVolume);

	// Add the effect to vector
	m_soundEffects.emplace_back(pNewSoundEffect);
}

void SoundEffectComponent::PlaySoundEffect(int soundEffectIndex, int loops)
{
	// If the index is greater than sound vector's size. Means something went wrong
	assert(soundEffectIndex < m_soundEffects.size());

	// If not, play the sound
	Mix_PlayChannel(-1, m_soundEffects.at(soundEffectIndex), loops);
}
