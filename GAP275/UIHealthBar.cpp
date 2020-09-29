// UIHealthBar.cpp
// Zixuan Shi
// A rectangle represents current and max health of an object.

#include "UIHealthBar.h"
#include "UIConstants.h"

#include "StaticImageObject.h"
#include "CollidableMovingObject.h"
#include "UITextField.h"

#include <SDL_ttf.h>
#include <algorithm>

UIHealthBar::UIHealthBar(Vector2D hpInterfacePosition, SDL_Renderer* pRenderer, CollidableMovingObject* pOwner)
	: GameObject()
	, m_baseBarRectangle{  }
	, m_currentBarRectangle{  }
	, m_pOwner{ pOwner }
	, m_hpBarColor{ kHealthyHpColor }
	, m_pImage{}
	, m_pCurrentHpText{nullptr}
{
	SDL_Rect hpBarRectangle{ (int)hpInterfacePosition.m_x + kHpBarXDiff, (int)hpInterfacePosition.m_y + kHpBarYDiff , kHealthBarWidth, kHealthBarHeight, };


	// hp bars
	m_baseBarRectangle = hpBarRectangle;
	m_currentBarRectangle = hpBarRectangle;


	// Interface
	SDL_Rect hpInterfaceRectangle{ (int)hpInterfacePosition.m_x, (int)hpInterfacePosition.m_y, kInterfaceWidth, kInterfaceHeight };
	m_pImage = new StaticImageObject{ hpInterfaceRectangle, kInterfacePath, pRenderer };


	//---------------------------------------------------------------------------------------------------------
	// Texts
	//---------------------------------------------------------------------------------------------------------
	TTF_Font* pTextFont = TTF_OpenFont(kTextFontPath, kTextFontSize);

	// Name
	Vector2D namePosition = { ((double)hpInterfaceRectangle.x + kNamePositionDiffX), ((double)hpInterfaceRectangle.y + kNamePositionDiffY) };
	m_textFields.push_back(new UITextField{ pTextFont , pOwner->GetName(), kBaseColor, namePosition, pRenderer });

	TTF_CloseFont(pTextFont);
}

UIHealthBar::~UIHealthBar()
{
	delete m_pImage;
	m_pImage = nullptr;

	for (auto& object : m_textFields)
	{
		delete object;
		object = nullptr;
	}
}

void UIHealthBar::Render(SDL_Renderer* pRenderer)
{
	// Interface
	m_pImage->Render(pRenderer);

	// Base Hp bar
	SDL_SetRenderDrawColor(pRenderer, kBaseColor.r, kBaseColor.g, kBaseColor.b, kBaseColor.a);
	SDL_RenderFillRect(pRenderer, &m_baseBarRectangle);

	// Current hp bar
	SDL_SetRenderDrawColor(pRenderer, m_hpBarColor.r, m_hpBarColor.g, m_hpBarColor.b, m_hpBarColor.a);
	SDL_RenderFillRect(pRenderer, &m_currentBarRectangle);

	// Text fields
	for (auto& object : m_textFields)
	{
		object->Render(pRenderer);
	}
}

////////////////////////////////////////////////////////////////////////////
// Update hp bar by current hp's value in comparison with total hp
////////////////////////////////////////////////////////////////////////////
void UIHealthBar::Update(double deltaTime)
{
	// Current hp bar's width
	// Formular: Length = currentHp/totalHp * originalLength;
	m_currentBarRectangle.w = int((m_pOwner->GetCurrentHp() / m_pOwner->GetTotalHp()) * m_baseBarRectangle.w);
	if (m_currentBarRectangle.w < 0)
		m_currentBarRectangle.w = 0;

	// Color
	// Greater than half
	if (m_pOwner->GetCurrentHp() >= (m_pOwner->GetTotalHp() / 2))
		m_hpBarColor = kHealthyHpColor;

	// Less than half but greater than 1/4
	else if (m_pOwner->GetCurrentHp() < (m_pOwner->GetTotalHp() / 2) &&
		m_pOwner->GetCurrentHp() >(m_pOwner->GetTotalHp() / 4))
		m_hpBarColor = kHalfHpColor;

	// Less than 1/4
	else
		m_hpBarColor = kLowHpColor;
}
