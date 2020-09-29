// SoundEffectReferee.cpp
// Zixuan Shi
// Control all sound effects

#include "SoundEffectReferee.h"

SoundEffectReferee::SoundEffectReferee()
{
}

SoundEffectReferee::~SoundEffectReferee()
{
}

///////////////////////////////////////////////////////////////////////
// Registers a Sound Effect as active, so it will be checked against.
///////////////////////////////////////////////////////////////////////
void SoundEffectReferee::AddActiveSoundEffect(SoundEffectComponent* pSound)
{
	// Make sure it's not already present.
	if (std::find(m_activeSounds.begin(), m_activeSounds.end(), pSound) == m_activeSounds.end())
	{
		// If it's not, add it to the back.
		m_activeSounds.push_back(pSound);
	}
}

///////////////////////////////////////////////////////////////////////
// Unregisters a Sound Effect as active, so it will no longer be checked.
///////////////////////////////////////////////////////////////////////
void SoundEffectReferee::RemoveActiveSoundEffect(SoundEffectComponent* pSound)
{
	// Find the Sound Effect.
	auto location = std::find(m_activeSounds.begin(), m_activeSounds.end(), pSound);

	// If it's found, erase it from the vector.
	if (location != m_activeSounds.end())
	{
		m_activeSounds.erase(location);
	}
}
