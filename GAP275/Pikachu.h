// Pikachu.h
// Zixuan Shi
// Pikachu class

#pragma once
#include "Pokemon.h"
#include "RandomNumberGenerator.h"

class SoundEffectReferee;
class SoundEffectComponent;
class AnimationComponent;
class CollidableMovingObject;

/////////////////////////////////////////////
// Player's pokemon
/////////////////////////////////////////////
class Pikachu :	public Pokemon
{
private:
	RandomNumberGenerator m_randomNumberGenerator;
	bool m_isThundering;

public:
	Pikachu(SDL_Renderer* pRenderer, CollisionReferee* pCollisionReferee, SoundEffectReferee* pSoundReferee, Vector2D spawnPosition);
	~Pikachu();

	// Inherited via GameObject
	virtual void Update(double deltaTime) override;
	virtual void Render(SDL_Renderer* pRenderer) override;

	// Pikachu moves
	void Thunder(CollidableMovingObject* pTarget);
	void TailWhip(CollidableMovingObject* pTarget);

	virtual void ChangeState(AIState* pNewState);

	bool GetIsThundering() const { return m_isThundering; }
	void SetIsThundering(bool boolean) { m_isThundering = boolean; }
};

