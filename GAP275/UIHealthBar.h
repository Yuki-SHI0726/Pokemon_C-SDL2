// UIHealthBar.h
// Zixuan Shi
// A rectangle represents current and max health of an object.

#pragma once
#include "GameObject.h"

#include <vector>

class StaticImageObject;
class CollidableMovingObject;
class Vector2D;
class UITextField;
class GameObject;

////////////////////////////////////////////////////
// A bar showing the hp
////////////////////////////////////////////////////
class UIHealthBar :	public GameObject
{
private:
	CollidableMovingObject* m_pOwner;	// The owner of the hp bar

	SDL_Rect m_currentBarRectangle;		// The bar showing current hp
	SDL_Rect m_baseBarRectangle;	// The bar showing total hp

	SDL_Color m_hpBarColor;	// Three different color of hp bar

	StaticImageObject* m_pImage;

	UITextField* m_pCurrentHpText;
	std::vector<UITextField*> m_textFields;

public:
	UIHealthBar(Vector2D hpInterfacePosition, SDL_Renderer* pRenderer, CollidableMovingObject* pOwner);
	~UIHealthBar();

	// Renders this object.
	virtual void Render(SDL_Renderer* pRenderer) override;
	virtual void Update(double deltaTime) override;
};

