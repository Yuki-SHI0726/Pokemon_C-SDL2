// StaticImageObject.cpp
// Zixuan Shi
// Renders an image with no special behavior

#include "StaticImageObject.h"
#include "SDL_image.h"
#include <iostream>

///////////////////////////////////////////////
// An image with no special behavior.
///////////////////////////////////////////////
StaticImageObject::StaticImageObject(SDL_Rect transform, const char* pImagePath, SDL_Renderer* pRenderer)
	: m_transform(transform)
	, m_pTexture(nullptr)
{
	// Make sure pRenderer is not null.
	if (pRenderer == nullptr)
	{
		std::cout << "pRenderer is null." << std::endl;
		return;
	}

	// Load surface from image path.
	SDL_Surface* pSurface = IMG_Load(pImagePath);
	if (pSurface == nullptr)
	{
		std::cout << "Unable to load " << pImagePath << std::endl;
		return;
	}

	// Create texture from surface.
	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (m_pTexture == nullptr)
	{
		std::cout << "Unable to create texture." << std::endl;
	}

	// Free surface.
	SDL_FreeSurface(pSurface);
}

///////////////////////////////////////////////
// Destructor.
///////////////////////////////////////////////
StaticImageObject::~StaticImageObject()
{
	SDL_DestroyTexture(m_pTexture);
}

///////////////////////////////////////////////
// Render this object.
///////////////////////////////////////////////
void StaticImageObject::Render(SDL_Renderer * pRenderer)
{
	SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &m_transform);
}
