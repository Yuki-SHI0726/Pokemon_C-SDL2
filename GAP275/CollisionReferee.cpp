// CollisionReferee.cpp
// Zixuan Shi
// Control all the collision components

#include "CollisionReferee.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "SDL.h"

CollisionReferee::CollisionReferee()
{
}


CollisionReferee::~CollisionReferee()
{
}

///////////////////////////////////////////////////////////////////////
// Registers a collider as active, so it will be checked against.
///////////////////////////////////////////////////////////////////////
void CollisionReferee::AddActiveCollider(ColliderComponent * pCollider)
{
	// Make sure it's not already present.
	if (std::find(m_activeColliders.begin(), m_activeColliders.end(), pCollider) == m_activeColliders.end())
	{
		// If it's not, add it to the back.
		m_activeColliders.push_back(pCollider);
	}
}

///////////////////////////////////////////////////////////////////////
// Unregisters a collider as active, so it will no longer be checked.
///////////////////////////////////////////////////////////////////////
void CollisionReferee::RemoveActiveCollider(ColliderComponent * pCollider)
{
	// Find the collider.
	auto location = std::find(m_activeColliders.begin(), m_activeColliders.end(), pCollider);
	
	// If it's found, erase it from the vector.
	if (location != m_activeColliders.end())
	{
		m_activeColliders.erase(location);
	}
}

///////////////////////////////////////////////////////////////////////
// Finds all colliders that overlap and notifies them of a collision.
// Returns whether or not a collision occurred.
///////////////////////////////////////////////////////////////////////
bool CollisionReferee::CheckForCollisionsAndNotify(ColliderComponent* pColliderToCheck)
{
	// Track whether any collisions have occurred.
	bool didCollide = false;

	// Get collider transform.
	SDL_Rect colliderTransform = pColliderToCheck->GetTransform();

	// Calculate bounds.
	int left = colliderTransform.x;
	int right = colliderTransform.x + colliderTransform.w;
	int top = colliderTransform.y;
	int bottom = colliderTransform.y + colliderTransform.h;

	// Check against every active collider.
	for (ColliderComponent* pOtherCollider : m_activeColliders)
	{
		// Don't check a collider against itself.
		if (pColliderToCheck == pOtherCollider)
			continue;

		// Get other collider's transform.
		SDL_Rect otherTrans = pOtherCollider->GetTransform();

		// Calculate bounds.
		int otherLeft = otherTrans.x;
		int otherRight = otherTrans.x + otherTrans.w;
		int otherTop = otherTrans.y;
		int otherBottom = otherTrans.y + otherTrans.h;

		// Check if they overlap horizontally
		// by comparing right vs. left and left vs. right.
		bool xOverlap = left < otherRight && right > otherLeft;

		// Check if they also overlap vertically
		// by comparing top vs. bottom and bottom vs. top.
		bool yOverlap = top < otherBottom && bottom > otherTop;

		// If they overlap both horizontally and vertically,
		// then they truly overlap.
		if (xOverlap && yOverlap)
		{
			// Notify both colliders of the collision.
			pColliderToCheck->GetOwner()->OnCollision(pOtherCollider);
			pOtherCollider->GetOwner()->OnCollision(pColliderToCheck);

			// If the other collider is bush. Don't stop the player
			if (pOtherCollider->GetColliderType() == ColliderComponent::ColliderType::kTrigger)
			{
				didCollide = didCollide || false;
			}
			else
			{
				// A collision has occurred.
				didCollide = true;
			}
		}
	}

	return didCollide;
}
