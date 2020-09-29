// UITextField.h
// Zixuan Shi
// Allow program to present texts

#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL_ttf.h>

//////////////////////////
// A text field.
//////////////////////////
class UITextField : public GameObject
{
private:
	// Position and size for rendering.
	SDL_Rect m_transform;

	// Text texture for rendering.
	SDL_Texture* m_pTexture;

public:
	UITextField(TTF_Font* pFont, const char* pText, SDL_Color color, Vector2D position, SDL_Renderer* pRenderer);
	~UITextField();

	// Renders this object.
	virtual void Render(SDL_Renderer* pRenderer) override;
};

