// StateLoss.h
// Zixuan Shi
// State Loss scene

#include "StateLoss.h"
#include "StateLossConstants.h"

#include "PokemonGame.h"
#include "SDLGame.h"
#include "UIButton.h"
#include "UITextField.h"
#include "StaticImageObject.h"

#include <iostream>

StateLoss::StateLoss(PokemonGame* pOwner)
	: m_pOwner(pOwner)
	, m_gameObjects()
	, m_keyboardButtonIndex{ 0 }
{
	// Load font.
	TTF_Font* m_pTextFont = TTF_OpenFont(kTextFontPath, kTextFontSize);
	TTF_Font* m_pTitleFont = TTF_OpenFont(kTitleFontPath, kTitleFontSize);
	TTF_Font* pNavigationFont = TTF_OpenFont(kNavigationFontPath, kNavigationFontSize);


	//-------------------------------------------------------------------------------------------------
	// Picture Background
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new StaticImageObject(kBackgroundRectangle, kBackgroundFilePath, pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Title text
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new UITextField(m_pTitleFont, kTitle, kTitleColor, kTitlePosition, pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Replay button
	//-------------------------------------------------------------------------------------------------
	// Replay Button Text
	UITextField* pReplayButtonText = new UITextField(m_pTextFont, kReplayButtonText, kButtonTextColor, kReplayTextPosition, pOwner->GetGame()->GetRenderer());

	// Button
	UIButton* pReplayButton = new UIButton(kReplayButtonRectangle, kDarkButtonPath, kLightButtonPath, pReplayButtonText, pOwner->GetGame()->GetRenderer());
	pReplayButton->SetCallback([pOwner]()->void
		{
			pOwner->SetIsReplaying(true);
			pOwner->LoadScene(PokemonGame::SceneName::kGameplay);
		});
	m_gameObjects.push_back(pReplayButton);


	//-------------------------------------------------------------------------------------------------
	// MainMenu button
	//-------------------------------------------------------------------------------------------------
	// MainMenu Button Text
	UITextField* pMainMenuButtonText = new UITextField(m_pTextFont, kMainMenuButtonText, kButtonTextColor, kMainMenuTextPosition, pOwner->GetGame()->GetRenderer());

	UIButton* pMainMenuButton = new UIButton(kMainMenuButtonRectangle, kDarkButtonPath, kLightButtonPath, pMainMenuButtonText, pOwner->GetGame()->GetRenderer());
	pMainMenuButton->SetCallback([pOwner]()->void
		{
			pOwner->LoadScene(PokemonGame::SceneName::kMainMenu);
		});
	m_gameObjects.push_back(pMainMenuButton);


	//-------------------------------------------------------------------------------------------------
	// Credits button
	//-------------------------------------------------------------------------------------------------
	// Credits Button Text
	UITextField* pCreditsButtonText = new UITextField(m_pTextFont, kCreditsButtonText, kButtonTextColor, kCreditsTextPosition, pOwner->GetGame()->GetRenderer());

	UIButton* pCreditsButton = new UIButton(kCreditsButtonRectangle, kDarkButtonPath, kLightButtonPath, pCreditsButtonText, pOwner->GetGame()->GetRenderer());
	pCreditsButton->SetCallback([pOwner]()->void
		{
			pOwner->LoadScene(PokemonGame::SceneName::kCredits);
		});
	m_gameObjects.push_back(pCreditsButton);


	//-------------------------------------------------------------------------------------------------
	// Quit button
	//-------------------------------------------------------------------------------------------------
	// Quit Button Text
	UITextField* pQuitButtonText = new UITextField(m_pTextFont, kQuitButtonText, kButtonTextColor, kQuitTextPosition, pOwner->GetGame()->GetRenderer());
	UIButton* pQuitButton = new UIButton(kQuitButtonRectangle, kDarkButtonPath, kLightButtonPath, pQuitButtonText, pOwner->GetGame()->GetRenderer());

	pQuitButton->SetCallback([pOwner]()->void
		{
			pOwner->GetGame()->Quit();
		});
	m_gameObjects.push_back(pQuitButton);


	//-------------------------------------------------------------------------------------------------
	// keyboard and/or controller navigation of buttons in all game states.
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new UITextField(pNavigationFont, kLossNavigationText, kNavigationColor, kLossNavigationPosition, pOwner->GetGame()->GetRenderer()));
	m_gameObjects.push_back(new UITextField(pNavigationFont, kNavigationTitle, kNavigationColor, kNavigationPosition, pOwner->GetGame()->GetRenderer()));


	// Store buttons in m_buttonSet, as well.
	m_buttonSet.push_back(pReplayButton);
	m_buttonSet.push_back(pMainMenuButton);
	m_buttonSet.push_back(pCreditsButton);
	m_buttonSet.push_back(pQuitButton);


	TTF_CloseFont(m_pTextFont);
	TTF_CloseFont(m_pTitleFont);
	TTF_CloseFont(pNavigationFont);
}

StateLoss::~StateLoss()
{
	for (GameObject* object : m_gameObjects)
	{
		delete object;
		object = nullptr;
	}

	m_gameObjects.clear();
}

void StateLoss::Update(double deltaTime)
{
	for (GameObject* pObject : m_gameObjects)
	{
		pObject->Update(deltaTime);
	}
}

void StateLoss::Render(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(pRenderer);
	for (GameObject* object : m_gameObjects)
	{
		object->Render(pRenderer);
	}
	SDL_RenderPresent(pRenderer);
}

bool StateLoss::HandleEvent(SDL_Event* pEvent)
{
	// Global events
	switch (pEvent->type)
	{
		// Window event can close the game.
	case SDL_WINDOWEVENT:
		if (pEvent->window.event == SDL_WINDOWEVENT_CLOSE)
			return true;	// Signal to quit
		break;

		// Keyboard events can scroll through and activate buttons.
	case SDL_KEYDOWN:
		switch (pEvent->key.keysym.scancode)
		{
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
			ChangeButtonFocus(1);
			break;
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
			ChangeButtonFocus(-1);
			break;
		case SDL_SCANCODE_RETURN:
		case SDL_SCANCODE_SPACE:
			if (m_keyboardButtonIndex != -1)
			{
				m_buttonSet[m_keyboardButtonIndex]->Trigger();
			}
			break;
		}
		break;

		// Mouse events cancel out keyboard and controller interaction.
	case SDL_MOUSEMOTION:
		m_keyboardButtonIndex = -1;
		break;
	}

	// Allow game objects to handle events as well.
	for (GameObject* object : m_gameObjects)
	{
		object->HandleEvent(pEvent);
	}


	return false;
}

void StateLoss::ChangeButtonFocus(int direction)
{
	int current = m_keyboardButtonIndex + direction;
	m_keyboardButtonIndex = (current) % m_buttonSet.capacity();

	for (unsigned i = 0; i < m_buttonSet.capacity(); ++i)
	{
		m_buttonSet[i]->SetIsHighlighted(i == m_keyboardButtonIndex);
	}
}
