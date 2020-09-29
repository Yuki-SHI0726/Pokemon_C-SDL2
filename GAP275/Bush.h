// Bush.h
// Zixuan Shi
// Bush object implementation

#pragma once
#include "CollidableStaticObject.h"
#include "RandomNumberGenerator.h"

class Player;
class StaticImageObject;

//////////////////////////////////////////////////////////
// Player needs to find pokemon to capture a pokemon
//////////////////////////////////////////////////////////
class Bush : public CollidableStaticObject
{
private:
	// Position and dimensions.
	SDL_Rect m_transform;

	// Dark Button
	StaticImageObject* m_pDarkImage;

	// Bright Button
	StaticImageObject* m_pBrightImage;

	// Whether this bush is currently highlighted.
	bool m_isOnEnter;

	Player* m_pPlayer;

	RandomNumberGenerator m_randomNumberGenerator;

	//static bool m_isFirstTimeEnter;
	bool m_isDirty;

public:
	Bush(Vector2D spawnPosition, CollisionReferee* pReferee, SDL_Renderer* pRenderer, Player* pPlayer);
	~Bush();

	virtual void Render(SDL_Renderer* pRenderer) override;
	virtual void Update(double deltaTime) override;
	bool CheckPlayerOnEnter();
};

