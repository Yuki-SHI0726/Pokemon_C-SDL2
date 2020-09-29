// CollidableStaticObject.h
// Zixuan Shi
// Static Object with collision system base class

#include "CollidableStaticObject.h"
#include "SDL.h"

////////////////////////////////////////////
// Constructor.
////////////////////////////////////////////
CollidableStaticObject::CollidableStaticObject(SDL_Rect transform, CollisionReferee* pReferee)
	: m_renderTransform(transform)
	, m_collider(this, transform, pReferee)
{
	m_objectType = "Collidable Static Object";
}

////////////////////////////////////////////
// Destructor.
////////////////////////////////////////////
CollidableStaticObject::~CollidableStaticObject()
{
}

////////////////////////////////////////////
// Draws this object as a solid primitive.
////////////////////////////////////////////
void CollidableStaticObject::Render(SDL_Renderer * pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, 128, 64, 32, SDL_ALPHA_OPAQUE);
	//SDL_RenderFillRect(pRenderer, &m_renderTransform);
}
