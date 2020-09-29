// CollidableMovingObject.cpp
// Zixuan Shi
// Base class for colliableMovingObjects

#include "CollidableMovingObject.h"

#include "SDL.h"
#include <iostream>

//////////////////////////////////////////////////////////////
// Constructor.
//////////////////////////////////////////////////////////////
CollidableMovingObject::CollidableMovingObject(SDL_Rect transform, CollisionReferee* pReferee, double hp)
	: m_renderTransform(transform)
	, m_collider(this, transform, pReferee)
	, m_totalHp{ hp }
	, m_currentHp{ hp }
	, m_isDead{ false }
	, m_position{ Vector2D{(double)transform.x, (double)transform.y} }
	, m_directionVector{ 0,0 }
	, m_facingDirection{ FacingDirection::kSouth }
{
	m_objectType = "Collidable Moving Object";
}

//////////////////////////////////////////////////////////////
// Destructor.
//////////////////////////////////////////////////////////////
CollidableMovingObject::~CollidableMovingObject()
{
}

//////////////////////////////////////////////////////////////
// Renders this object as a blue primitive.
//////////////////////////////////////////////////////////////
void CollidableMovingObject::Render(SDL_Renderer * pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(pRenderer, &m_renderTransform);
}

//////////////////////////////////////////////////////////////
// Attempts to move this object in the given delta directions.
// Returns whether or not the move was successful.
//////////////////////////////////////////////////////////////
bool CollidableMovingObject::TryMove(Vector2D deltaPosition)
{
	bool didMove = m_collider.TryMove(deltaPosition);
	
	//// Get Position by Vector 2D
	//Vector2D GetPosition() const 
	if (didMove)
	{
		m_renderTransform.x += (int)deltaPosition.m_x;
		m_renderTransform.y += (int)deltaPosition.m_y;
	}

	return didMove;
}

//////////////////////////////////////////////////////////////
// Sets new position without any collision checking.
//////////////////////////////////////////////////////////////
void CollidableMovingObject::SetPosition(Vector2D newPosition)
{
	m_renderTransform.x = (int)newPosition.m_x;
	m_renderTransform.y = (int)newPosition.m_y;

	m_collider.SetPosition(newPosition);
	m_position = newPosition;
}

//////////////////////////////////////////////////////////////
// Example collision handler.
//////////////////////////////////////////////////////////////
void CollidableMovingObject::OnCollision(ColliderComponent * pOtherCollider)
{
	std::string colliderName = pOtherCollider->GetOwner()->GetObjectType();
	std::cout << "Collided with " << colliderName << std::endl;
}
