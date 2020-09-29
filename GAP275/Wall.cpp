// Wall.cpp
// Zixuan Shi
// Wall object, player cannot passing through

#include "Wall.h"

Wall::Wall(SDL_Rect wallRectangle, CollisionReferee* pReferee)
	: CollidableStaticObject{ wallRectangle, pReferee}
{
	m_objectType = "Wall";
	m_name = "Wall";
}

void Wall::Render(SDL_Renderer* pRenderer)
{
	SDL_RenderFillRect(pRenderer, &m_renderTransform);
}
