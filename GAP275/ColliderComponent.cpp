// ColliderComponent.cpp
// Zixuan Shi
// ColliderComponent

#include "ColliderComponent.h"
#include "CollisionReferee.h"
#include "GameObject.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// Constructor.
///////////////////////////////////////////////////////////////////////////////
ColliderComponent::ColliderComponent(GameObject* pOwner, SDL_Rect transform, CollisionReferee* pReferee)
	: m_pOwner(pOwner)
	, m_transform(transform)
	, m_pReferee(pReferee)
	, m_collisionType{ ColliderType::kSolid }
{
	m_pReferee->AddActiveCollider(this);
}

///////////////////////////////////////////////////////////////////////////////
// Destructor.
///////////////////////////////////////////////////////////////////////////////
ColliderComponent::~ColliderComponent()
{
	m_pReferee->RemoveActiveCollider(this);
}

///////////////////////////////////////////////////////////////////////////////
// Sets x,y coordinates.
///////////////////////////////////////////////////////////////////////////////
void ColliderComponent::SetPosition(Vector2D newPosition)
{
	m_transform.x = (int)newPosition.m_x;
	m_transform.y = (int)newPosition.m_y;
}

///////////////////////////////////////////////////////////////////////////////
// Attempts to move the collider by the given amounts.
// If the move causes collisions, objects will be notified.
// Returns whether or not the move was successful without collisions.
///////////////////////////////////////////////////////////////////////////////
bool ColliderComponent::TryMove(Vector2D deltaPosition)
{
	// Check if a referee has been assigned.
	if (m_pReferee == nullptr)
	{
		std::cout << "Warning: collider is not assigned a referee." << std::endl;
		return true;
	}

	// Temporarily update position, then perform the check.
	m_transform.x += (int)deltaPosition.m_x;
	m_transform.y += (int)deltaPosition.m_y;
	bool didCollide = m_pReferee->CheckForCollisionsAndNotify(this);

	// If the move was invalid, undo it.
	if (didCollide == true)
	{
		m_transform.x -= (int)deltaPosition.m_x;
		m_transform.y -= (int)deltaPosition.m_y;
	}
	return !didCollide;
}