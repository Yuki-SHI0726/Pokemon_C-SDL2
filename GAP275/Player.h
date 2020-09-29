// Player.h
// Zixuan Shi
// Player in game class

#pragma once
#include "CollidableMovingObject.h"
#include "Vector2D.h"

class SoundEffectReferee;
class SoundEffectComponent;
class AnimationComponent;

////////////////////////////////////////////////////////
// An example GameObject that uses AnimationComponent.
////////////////////////////////////////////////////////
class Player :	public CollidableMovingObject
{
private:
	// A component for handling animation.
	AnimationComponent *m_pAnimation;

	// A component for handling sound effects
	SoundEffectComponent* m_pSoundEffect;

	double m_speed;

	bool m_isSprinting;

	int m_pokeballDepot;	// the pokeball count that the player collected

	bool m_readyToCapturePokemon;	// if true, combat with the pokemon

public:
	Player(SDL_Renderer* pRenderer, CollisionReferee* pReferee, SoundEffectReferee* pSoundReferee, Vector2D spawnPosition);
	~Player();

	// Inherited via GameObject
	virtual void Update(double deltaTime) override;
	virtual void Render(SDL_Renderer * pRenderer) override;

	virtual void OnCollision(ColliderComponent* pOtherCollider) override;

	// Getter
	AnimationComponent* GetAnimationComponent() const { return m_pAnimation; }	// Gets a pointer to this object's animation component.
	SoundEffectComponent* GetSoundEffectComponent() { return m_pSoundEffect; }	// Gets a pointer to this object's Sound Effect component.
	bool GetReadyToCapturePokemon() const { return m_readyToCapturePokemon; }
	int GetPokeballCount() const { return m_pokeballDepot; }

	// Setter
	void SetSprinting(bool boolean) { m_isSprinting = boolean; }
	void SetReadyCapturePokemon(bool boolean) { m_readyToCapturePokemon = true; }
	void ReducePokeballAmount() { --m_pokeballDepot; }
	void SetPokeballDepot(int amount) { m_pokeballDepot = amount; }

private:
	void UpdatePosition(double deltaPosition);
	void UpdateAnimation(double deltaTime);
	bool CheckCollision(double deltaPosition);
};

