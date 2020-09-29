// UIButton.h
// Zixuan Shi
// UI Button class

#include "UIButton.h"

#include "StaticImageObject.h"
#include "UITextField.h"

#include <iostream>

/////////////////////////////////////////////////////////////////////
// Constructor.
/////////////////////////////////////////////////////////////////////
UIButton::UIButton(SDL_Rect transform, const char* darkButtonPath, const char* brightButtonPath, UITextField* pText, SDL_Renderer* pRenderer)
	: m_transform(transform)
	, m_isHighlighted(false)
	, m_pDarkImage{ new StaticImageObject{transform , darkButtonPath, pRenderer } }
	, m_pBrightImage{ new StaticImageObject{transform , brightButtonPath, pRenderer } }
	, m_textFields{}
{
	m_textFields.push_back(pText);
}

/////////////////////////////////////////////////////////////////////
// Destructor.
/////////////////////////////////////////////////////////////////////
UIButton::~UIButton()
{
	delete m_pDarkImage;
	m_pDarkImage = nullptr;
	delete m_pBrightImage;
	m_pBrightImage = nullptr;

	for (auto& text : m_textFields)
	{
		delete text;
		text = nullptr;
	}
}

/////////////////////////////////////////////////////////////////////
// Renders this object.
/////////////////////////////////////////////////////////////////////
void UIButton::Render(SDL_Renderer* pRenderer)
{
	//Render the button picture
	// Select the color to use.
	StaticImageObject* pOject = m_isHighlighted ? m_pBrightImage : m_pDarkImage;
	pOject->Render(pRenderer);

	// displays text on top of the image at all times
	//Render the text
	for (auto& text : m_textFields)
	{
		text->Render(pRenderer);
	}
}

/////////////////////////////////////////////////////////////////////
// Handles the given event within the context of this object.
/////////////////////////////////////////////////////////////////////
void UIButton::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
		// Mouse hover
	case SDL_MOUSEMOTION:
		m_isHighlighted = HitTest(pEvent->button.x, pEvent->button.y);
		break;

		// Mouse click
	case SDL_MOUSEBUTTONDOWN:
		if (m_callback != nullptr)
		{
			if (HitTest(pEvent->button.x, pEvent->button.y))
			{
				m_callback();
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////
// Triggers the button's callback as if it had been clicked.
/////////////////////////////////////////////////////////////////////
void UIButton::Trigger()
{
	if (m_callback != nullptr)
		m_callback();
}

/////////////////////////////////////////////////////////////////////
// Returns whether the given x,y are within the bounds of the button.
/////////////////////////////////////////////////////////////////////
bool UIButton::HitTest(int x, int y)
{
	return (x > m_transform.x && x < m_transform.x + m_transform.w &&
		y > m_transform.y && y < m_transform.y + m_transform.h);
}
