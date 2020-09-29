// SoundEffectReferee.h
// Zixuan Shi
// Control all sound effects

#pragma once

#include <vector>

class SoundEffectComponent;

/////////////////////////////////////////////////////////////////////
// Maintains references to all Sound Effect and Plays them.
/////////////////////////////////////////////////////////////////////
class SoundEffectReferee
{
private:
	// All currently active Sound Effect.
	std::vector<SoundEffectComponent*> m_activeSounds;

public:
	SoundEffectReferee();
	~SoundEffectReferee();

	// Registers a Sound Effect as active, so it will be checked against.
	void AddActiveSoundEffect(SoundEffectComponent* pSound);

	// Unregisters a Sound Effect as active, so it will no longer be checked.
	void RemoveActiveSoundEffect(SoundEffectComponent* pSound);
};

