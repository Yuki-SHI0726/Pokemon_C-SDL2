// StateCredits.cpp
// Zixuan Shi
// Credits scene

#include "StateCredits.h"

#include "StaticImageObject.h"
#include "StateMainMenu.h"
#include "PokemonGame.h"
#include "SDLGame.h"
#include "UIButton.h"
#include "UITextField.h"
#include "SoundEffectComponent.h"

#include "CreditsConstants.h"

StateCredits::StateCredits(PokemonGame* pOwner)
	: m_pOwner{ pOwner }
	, m_gameObjects()
	, m_keyboardButtonIndex{ 0 }
	, m_pSoundEffect{ new SoundEffectComponent(nullptr, pOwner->GetGame()->GetSoundEffectReferee()) }
{
	// Load font.
	TTF_Font* m_pTextFont = TTF_OpenFont(kTextFontPath, kCreditsFontSize);


	//-------------------------------------------------------------------------------------------------
	// Picture Background
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new StaticImageObject(kBackgroundRectangle, kBackgroundFilePath, pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Credits text
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new UITextField(m_pTextFont, kCredits, kTextColor, kCreditsPosition, pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Information
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new UITextField(m_pTextFont, kDeveloperName, kTextColor, kDeveloperPosition, pOwner->GetGame()->GetRenderer()));
	m_gameObjects.push_back(new UITextField(m_pTextFont, kEmail, kTextColor, kEmailPosition, pOwner->GetGame()->GetRenderer()));
	m_gameObjects.push_back(new UITextField(m_pTextFont, kPhone, kTextColor, kPhonePosition, pOwner->GetGame()->GetRenderer()));
	m_gameObjects.push_back(new UITextField(m_pTextFont, kSpriteCredits, kTextColor, kSpriteSheetCreditsPosition, pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Quit button
	//-------------------------------------------------------------------------------------------------
	// Quit Button Text
	UITextField* pMainMenuText = new UITextField(m_pTextFont, kQuitButtonText, kButtonTextColor, kQuitTextPosition, pOwner->GetGame()->GetRenderer());
	UIButton* pMainMenuButton = new UIButton(kQuitButtonRectangle, kDarkButtonPath, kLightButtonPath, pMainMenuText, pOwner->GetGame()->GetRenderer());
	pMainMenuButton->SetCallback([pOwner]()->void
		{
			pOwner->LoadScene(PokemonGame::SceneName::kMainMenu);
		});
	m_gameObjects.push_back(pMainMenuButton);
	// Store buttons in m_buttonSet, as well.
	m_buttonSet.push_back(pMainMenuButton);


	// Play the sound effect
	m_pSoundEffect->AddSoundEffect(kSnorlaxRoarSoundEffectFilePath, kRoarVolume);
	m_pSoundEffect->PlaySoundEffect(kRoarIndex, kRoarLoop);

	TTF_CloseFont(m_pTextFont);
}

StateCredits::~StateCredits()
{
	delete m_pSoundEffect;
	m_pSoundEffect = nullptr;

	for (GameObject* object : m_gameObjects)
	{
		delete object;
		object = nullptr;
	}

	m_gameObjects.clear();
}

void StateCredits::Render(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(pRenderer);
	for (GameObject* object : m_gameObjects)
	{
		object->Render(pRenderer);
	}
	SDL_RenderPresent(pRenderer);
}

//////////////////////////////////////////////////////////
// Handles the given event.
// Returns true when it's time to quit.
//////////////////////////////////////////////////////////
bool StateCredits::HandleEvent(SDL_Event* pEvent)
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

void StateCredits::ChangeButtonFocus(int direction)
{
	int current = m_keyboardButtonIndex + direction;
	m_keyboardButtonIndex = (current) % m_buttonSet.capacity();
	for (unsigned i = 0; i < m_buttonSet.capacity(); ++i)
	{
		m_buttonSet[i]->SetIsHighlighted(i == m_keyboardButtonIndex);
	}

}
