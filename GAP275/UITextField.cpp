// UITextField.cpp
// Zixuan Shi
// Allow program to present texts

#include "UITextField.h"
#include <SDL_ttf.h>

//////////////////////////
// Constructor.
//////////////////////////
UITextField::UITextField(TTF_Font* pFont, const char* pText, SDL_Color color,
	Vector2D position, SDL_Renderer* pRenderer)
	: m_pTexture(nullptr)
	, m_transform()
{
	// Render text to a surface.
	SDL_Surface* pTextSurface = TTF_RenderText_Solid(pFont, pText, color);

	// Create texture from surface.
	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pTextSurface);

	// Set text field's position.
	m_transform.x = (int)position.m_x;
	m_transform.y = (int)position.m_y;

	// Set dimensions based on how big the rendered text is.
	m_transform.w = pTextSurface->w;
	m_transform.h = pTextSurface->h;

	// Always free the surface.
	SDL_FreeSurface(pTextSurface);
}

//////////////////////////
// Constructor.
//////////////////////////
UITextField::~UITextField()
{
	SDL_DestroyTexture(m_pTexture);
}

//////////////////////////
// Renders this object.
//////////////////////////
void UITextField::Render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &m_transform);
}
