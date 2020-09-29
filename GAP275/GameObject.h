// GameObject.h
// Zixuan Shi
// Base interface of all game objects

#pragma once

#include "SDL.h"
#include <string>
#include <SDL_rect.h>

class ColliderComponent;
class StaticImageObject;

///////////////////////
// An in-game object.
///////////////////////
class GameObject
{
public:


protected:
	// #DG: this might be a good place to use an enum instead of a string
	// Strings like this are prone to error.
	const char* m_objectType = "";
	const char* m_name = "";

	bool m_shouldErase = false;	// If we need to erase the object

public:
	virtual ~GameObject() {	}

	// Get this object's type.
	virtual const char* GetObjectType() { return m_objectType; }

	// Get this object's name
	virtual const char* GetName() { return m_name; }

	// Update this object's state.
	virtual void Update(double deltaTime) { }

	// Render this object.
	virtual void Render(SDL_Renderer* pRenderer) { }

	// Callback for when a collision occurs.
	virtual void OnCollision(ColliderComponent* pOtherCollider) { }

	// Handles the given event within the context of this object.
	virtual void HandleEvent(SDL_Event* pEvent) { }

	// Move randomly
	virtual void MoveRandomly(double deltaTime) {};

	virtual bool GetShouldErase() { return m_shouldErase; }
};

