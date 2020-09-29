// Charmander.h
// Zixuan Shi
// Charmander class

#pragma once
#include "Pokemon.h"
#include "RandomNumberGenerator.h"
#include "CharmanderConstants.h"

class SoundEffectReferee;
class SoundEffectComponent;
class AnimationComponent;

//////////////////////////////////////////////
// The Enemy in Game, has two states
//////////////////////////////////////////////
class Charmander : public Pokemon
{
private:
	RandomNumberGenerator m_randomNumberGenerator;

public:
	Charmander(SDL_Renderer* pRenderer, CollisionReferee* pCollisionReferee, SoundEffectReferee* pSoundReferee, Vector2D spawnPosition);
	~Charmander();

	// Inherited via GameObject
	virtual void Update(double deltaTime) override;
	virtual void Render(SDL_Renderer* pRenderer) override;

	virtual void ChangeState(AIState* pNewState) override;

	virtual void MoveRandomly(double deltaTime) override;
};

