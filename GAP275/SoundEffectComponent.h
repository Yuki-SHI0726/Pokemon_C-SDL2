// SoundEffectComponent.h
// Zixuan Shi
// This component handles Sound effect playing

#pragma once

#include "SDL_mixer.h"

#include <vector>

class GameObject;
class SoundEffectReferee;

////////////////////////////////////////////
// Sound Effect Components
// Basically copied from collisionComponent
////////////////////////////////////////////
class SoundEffectComponent
{
private:
	// The object that owns this SoundEffect.
	GameObject* m_pOwner;

	// The sound effect
	std::vector<Mix_Chunk*> m_soundEffects;

	// Pointer to referee where this Sound Effect is registered.
	SoundEffectReferee* m_pSoundReferee;

public:
	SoundEffectComponent(GameObject* pOwner, SoundEffectReferee* pReferee);
	~SoundEffectComponent();

	// Gets the collider's owning GameObject.
	GameObject* GetOwner() { return m_pOwner; }

	// Get the sound Effects
	const std::vector<Mix_Chunk*>& GetSoundEffects() { return m_soundEffects; }

	// Add a sound effect
	void AddSoundEffect(const char* filePath, int soundVolume);

	// Play a sound effect
	void PlaySoundEffect(int soundEffectIndex, int loops);
};

