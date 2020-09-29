// Pokeball.h
// Zixuan Shi
// Pokeball class

#pragma once
#include "CollidableStaticObject.h"

class AnimationComponent;

//////////////////////////////////////////////////////////
// Player needs to collect pokeball for capture a pokemon
//////////////////////////////////////////////////////////
class Pokeball : public CollidableStaticObject
{
private:
	AnimationComponent* m_pAnimation;

	bool m_isCollected; // If false, means the player hasn't picked this pokeball up. Vice versa

public:
	Pokeball(SDL_Renderer* pRenderer, CollisionReferee* pReferee, Vector2D spawnPosition);
	~Pokeball();

	// Inherited via GameObject
	virtual void Update(double deltaTime) override;
	virtual void Render(SDL_Renderer* pRenderer) override;

	// Gets a pointer to this object's animation component.
	AnimationComponent* GetAnimationComponent() { return m_pAnimation; }

	void SetIsCollected(bool boolean) { m_isCollected = boolean; }
	bool GetIsCollected() const { return m_isCollected; }
};

