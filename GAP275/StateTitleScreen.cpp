// StateTitleScreen.cpp
// Zixuan Shi
// State TitleScreen scene

#include "StateTitleScreen.h"
#include "StateTitleScreenConstants.h"

#include "PokemonGame.h"
#include "SDLGame.h"
#include "UITextField.h"
#include <iostream>
#include "StateMainMenu.h"

StateTitleScreen::StateTitleScreen(PokemonGame* pOwner)
	: m_pOwner(pOwner)
	, m_gameObjects()
{
	// Load font.
	TTF_Font* m_pTextFont = TTF_OpenFont(kTextFontPath, kTextFontSize);

	//-------------------------------------------------------------------------------------------------
	// Picture Background
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new StaticImageObject(kBackgroundRectangle, kBackgroundFilePath, pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Title text
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new UITextField(m_pTextFont, kTitle, kTitleColor, kTitlePosition, pOwner->GetGame()->GetRenderer()));


	TTF_CloseFont(m_pTextFont);
}

StateTitleScreen::~StateTitleScreen()
{
	for (GameObject* object : m_gameObjects)
	{
		delete object;
		object = nullptr;
	}

	m_gameObjects.clear();
}

void StateTitleScreen::Render(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(pRenderer);
	for (GameObject* object : m_gameObjects)
	{
		object->Render(pRenderer);
	}
	SDL_RenderPresent(pRenderer);
}

bool StateTitleScreen::HandleEvent(SDL_Event* pEvent)
{
	// Global events
	switch (pEvent->type)
	{
		// Window event can close the game.
	case SDL_WINDOWEVENT:
		if (pEvent->window.event == SDL_WINDOWEVENT_CLOSE)
			return true;	// Signal to quit
		break;

	case SDL_KEYDOWN:
	case SDL_MOUSEBUTTONDOWN:
		m_pOwner->LoadScene(PokemonGame::SceneName::kMainMenu);
		break;
	}

	return false;
}
