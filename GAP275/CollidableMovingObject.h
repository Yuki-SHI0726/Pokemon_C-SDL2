// CollidableMovingObject.h
// Zixuan Shi
// Base class for colliableMovingObjects

#pragma once
#include "GameObject.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "Vector2D.h"

class CollisionReferee;

//////////////////////////////////////////////////////////////
// A moving object with a collider.
//////////////////////////////////////////////////////////////
class CollidableMovingObject : public GameObject
{
public:
	enum class FacingDirection
	{
		kNorth,
		kSouth,
		kWest,
		kEast
	};

protected:
	// This object's position.
	SDL_Rect m_renderTransform;

	// Collider component.
	ColliderComponent m_collider;

	double m_totalHp;
	double m_currentHp;
	bool m_isDead;

	// Moving
	Vector2D m_directionVector;		// The moving destination of player
	Vector2D m_position;		// The current position of player
	FacingDirection m_facingDirection;

public:
	CollidableMovingObject(SDL_Rect transform, CollisionReferee* pReferee, double hp);
	~CollidableMovingObject();

	// Renders this object as a blue primitive.
	virtual void Render(SDL_Renderer * pRenderer) override;

	// Attempts to move this object in the given delta directions.
	// Returns whether or not the move was successful.
	bool TryMove(Vector2D deltaPosition);

	// Sets new position without any collision checking.
	void SetPosition(Vector2D newPosition);

	// Example collision handler.
	virtual void OnCollision(ColliderComponent* pOtherCollider) override;
	
	void TakeDamage(double amount) { this->m_currentHp -= amount; }

	bool GetIsDead() const { return m_isDead; }
	double GetTotalHp() const { return m_totalHp; }
	double GetCurrentHp() const { return m_currentHp; }
	Vector2D GetPosition() const { return m_position; }
	SDL_Rect GetTransform() const { return m_renderTransform; }

	void SetDirectionVector(Vector2D vector) { m_directionVector = vector; }
	void SetFacingDirection(FacingDirection direction) { m_facingDirection = direction; }
	void SetHp(double hp) { m_currentHp = hp; }
};

