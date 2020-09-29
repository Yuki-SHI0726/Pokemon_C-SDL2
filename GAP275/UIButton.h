// UIButton.h
// Zixuan Shi
// UI Button class

#pragma once
#include "GameObject.h"

#include <functional>
#include <vector>

class StaticImageObject;
class UITextField;

/////////////////////////////////////////////////////////////////////
// A clickable button.
/////////////////////////////////////////////////////////////////////
class UIButton : public GameObject
{
private:
	// Dark Button
	StaticImageObject* m_pDarkImage;

	// Bright Button
	StaticImageObject* m_pBrightImage;

	// The Texts on the Button
	std::vector<UITextField*> m_textFields;

	// Position and size.
	SDL_Rect m_transform;

	// Whether this button is currently highlighted.
	bool m_isHighlighted;

	// Function to be called when this button is clicked.
	std::function<void()> m_callback;

public:
	UIButton(SDL_Rect transform, const char* darkButtonPath, const char* brightButtonPath, UITextField* pText, SDL_Renderer* pRenderer);
	~UIButton();

	// Renders this object.
	virtual void Render(SDL_Renderer* pRenderer) override;

	// Handles the given event within the context of this object.
	virtual void HandleEvent(SDL_Event* pEvent) override;

	// Triggers the button's callback as if it had been clicked.
	void Trigger();

	// Sets this button's callback function.
	void SetCallback(std::function<void()> callback) { m_callback = callback; }

	// Sets this button's highlight set.
	void SetIsHighlighted(bool value) { m_isHighlighted = value; }

	// Add additional text to the button
	void AddText(UITextField* pText) { m_textFields.push_back(pText); }

private:
	// Returns whether the given x,y are within the bounds of the button.
	bool HitTest(int x, int y);
};

