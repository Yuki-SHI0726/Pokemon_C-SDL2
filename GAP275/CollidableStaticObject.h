// CollidableStaticObject.h
// Zixuan Shi
// Static Object with collision system base class

#pragma once
#include "GameObject.h"

#include "ColliderComponent.h"
#include "SoundEffectComponent.h"

////////////////////////////////////////////
// An unmoving object with a collider.
////////////////////////////////////////////
class CollidableStaticObject :
	public GameObject
{
protected:
	// Position and dimensions.
	SDL_Rect m_renderTransform;

	// Collider component.
	ColliderComponent m_collider;

public:
	CollidableStaticObject(SDL_Rect transform, CollisionReferee* pCollisionReferee);
	~CollidableStaticObject();

	// Gets this object's name.
	virtual const char* GetName() override { return m_objectType; }

	// Draws this object as a solid primitive.
	virtual void Render(SDL_Renderer * pRenderer) override;
};

