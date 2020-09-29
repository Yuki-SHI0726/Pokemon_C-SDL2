// Pokemon.h
// Zixuan Shi
// Base class of Pokemon

#pragma once
#include "CollidableMovingObject.h"

class AIState;
class GameObject;
union SDL_Event;

class SoundEffectReferee;
class SoundEffectComponent;
class AnimationComponent;

/////////////////////////////////////////////////////
// An interface for handling GameObject states.
// This pokemon class is a state machine as well.
/////////////////////////////////////////////////////
class Pokemon : public CollidableMovingObject
{
protected:
	AIState* m_pPreviousState;
	AIState* m_pCurrentState;

	AnimationComponent* m_pAnimation;

	// A component for handling sound effects
	SoundEffectComponent* m_pSoundEffect;

	int m_attackDamage;

public:
	// #DG: just pass a pointer to the SDL_game rather than all the pointers in it (the renderer, collision, sound, etc.). This constructor is really bloated
	Pokemon(SDL_Renderer* pRenderer, CollisionReferee* pCollisionReferee, SoundEffectReferee* pSoundReferee, SDL_Rect pokemonRectangle, double pokemonHp, const char* kPokemonSpriteSheet, int frameCount, int frameRate, int damage);
	virtual ~Pokemon();

	// Exits current state and enters new state.
	virtual void ChangeState(AIState* pNewState) = 0;

	// Gets a pointer to this object's animation component.
	AnimationComponent* GetAnimationComponent() { return m_pAnimation; }

	// Gets a pointer to this object's Sound Effect component.
	SoundEffectComponent* GetSoundEffectComponent() { return m_pSoundEffect; }

	int GetAttackDamage()const { return m_attackDamage; }
};

