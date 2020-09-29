// CollisionReferee.h
// Zixuan Shi
// Control all the collision components

#pragma once
#include <vector>

class ColliderComponent;

/////////////////////////////////////////////////////////////////////
// Maintains references to all colliders and checks them.
/////////////////////////////////////////////////////////////////////
class CollisionReferee
{
private:
	// All currently active colliders.
	std::vector<ColliderComponent*> m_activeColliders;

public:
	CollisionReferee();
	~CollisionReferee();

	// Registers a collider as active, so it will be checked against.
	void AddActiveCollider(ColliderComponent* pCollider);

	// Unregisters a collider as active, so it will no longer be checked.
	void RemoveActiveCollider(ColliderComponent* pCollider);

	// Finds all colliders that overlap and notifies them of a collision.
	// Returns whether or not a collision occurred.
	bool CheckForCollisionsAndNotify(ColliderComponent* pColliderToCheck);
};

