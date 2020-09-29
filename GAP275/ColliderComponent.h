// ColliderComponent.h
// Zixuan Shi
// ColliderComponent header

#pragma once
#include "SDL.h"
#include "Vector2D.h"
#include <functional>

class CollisionReferee;
class GameObject;

//////////////////////////////////////////////////
// An axis-aligned bounding box (AABB) collider.
//////////////////////////////////////////////////
class ColliderComponent
{
public:
	enum class ColliderType
	{
		kTrigger,	// Collides, but doesn't stops the player
		kSolid		// Stop the player when the play collides with this
	};

private:
	// The object that owns this collider.
	GameObject* m_pOwner;

	// Position and dimensions.
	SDL_Rect m_transform;

	// Pointer to referee where this collider is registered.
	CollisionReferee* m_pReferee;

	// Function callbacks on collision
	std::function<void()> m_callback;

	// Collider type
	ColliderType m_collisionType;

public:
	ColliderComponent(GameObject* pOwner, SDL_Rect transform, CollisionReferee* pReferee);
	~ColliderComponent();

	// Gets the collider's owning GameObject.
	GameObject* GetOwner() { return m_pOwner; }

	// Gets the collider's current transforms.
	SDL_Rect GetTransform() { return m_transform; }

	// Gets the collider's type
	ColliderType GetColliderType() const { return m_collisionType; }

	// Set collision type
	void SetCollisionType(ColliderType type) { m_collisionType = type; }

	// Sets x,y coordinates.
	void SetPosition(Vector2D newPosition);

	// Sets this Collision's callback function.
	void SetCallback(std::function<void()> callback) { m_callback = callback; }
	std::function<void()> GetCallback() { return m_callback; }

	// Attempts to move the collider by the given amounts.
	// If the move causes collisions, objects will be notified.
	// Returns whether or not the move was successful without collisions.
	bool TryMove(Vector2D deltaPosition);
};

