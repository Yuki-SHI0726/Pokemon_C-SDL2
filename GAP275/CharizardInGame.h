// Charizard.h
// Zixuan Shi
// Charizard class

#pragma once
#include "Pokemon.h"

class SoundEffectReferee;
class SoundEffectComponent;
class AnimationComponent;

// #DG: this name breaks the convention you have for the other pokemon. The 'InGame' part seems unnecessary.
class CharizardInGame : public Pokemon
{
private:

public:
	CharizardInGame(SDL_Renderer* pRenderer, CollisionReferee* pCollisionReferee, SoundEffectReferee* pSoundReferee, Vector2D spawnPosition);
	~CharizardInGame();

	// Inherited via GameObject
	virtual void Update(double deltaTime) override;
	virtual void Render(SDL_Renderer* pRenderer) override;

	virtual void ChangeState(AIState* pNewState) override;
};

