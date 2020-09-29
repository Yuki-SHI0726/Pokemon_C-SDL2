// StaticImageObject.h
// Zixuan Shi
// Renders an image with no special behavior

#pragma once
#include "GameObject.h"

///////////////////////////////////////////////
// Renders an image with no special behavior.
///////////////////////////////////////////////
class StaticImageObject : public GameObject
{
private:
	// Position and dimensions.
	SDL_Rect m_transform;

	// Image texture for rendering.
	SDL_Texture* m_pTexture;

public:
	StaticImageObject(SDL_Rect transform, const char* pImagePath, SDL_Renderer* pRenderer);
	~StaticImageObject();

	virtual const char* GetObjectType() override { return "Static Image"; }
	virtual void Render(SDL_Renderer* pRenderer) override;
};

