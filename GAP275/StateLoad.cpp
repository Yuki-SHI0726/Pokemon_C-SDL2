// StateLoad.cpp
// Zixuan Shi
// State Load scene

#include "StateLoad.h"
#include "StateLoadConstants.h"

#include "Player.h"
#include "PokemonGame.h"
#include "SDLGame.h"
#include "UIButton.h"
#include "UITextField.h"
#include "StaticImageObject.h"

#include <SDL_ttf.h>

StateLoad::StateLoad(PokemonGame* pOwner)
	: m_pOwner(pOwner)
	, m_gameObjects()
	, m_keyboardButtonIndex{ 0 }
	, m_pPlayer{ nullptr }
{
	// Load font.
	TTF_Font* pTextFont = TTF_OpenFont(kTextFontPath, kTextFontSize);
	TTF_Font* pNavigationFont = TTF_OpenFont(kNavigationFontPath, kNavigationFontSize);
	TTF_Font* pSaveButtonTextFont = TTF_OpenFont(kNavigationFontPath, kSaveSlotFontSize);

	//-------------------------------------------------------------------------------------------------
	// Picture Background
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new StaticImageObject(kBackgroundRectangle, kBackgroundFilePath, pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Title text
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new UITextField(pTextFont, kTitle, kTitleColor, kTitlePosition, pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Player Object
	//-------------------------------------------------------------------------------------------------
	m_pPlayer = new Player(pOwner->GetGame()->GetRenderer(), pOwner->GetGame()->GetCollisionReferee(), pOwner->GetGame()->GetSoundEffectReferee(), kPlayerPosition);
	m_gameObjects.push_back(m_pPlayer);
	m_pPlayer->SetDirectionVector({ 0,1 });


	//-------------------------------------------------------------------------------------------------
	// Load buttons
	//-------------------------------------------------------------------------------------------------
	int currentButtonY = kButtonY;

	for (size_t i = 1; i <= kMaxSaveSlotCount; ++i)
	{
		// For text y position
		double textCurrentY = currentButtonY;

		// Get Save button text
		SaveSystem* pSave = new SaveSystem(i);
		std::string saveString = pSave->GetSaveSlotString();	// Total string
		size_t currentStringIndex = 0;	// Current String position index
		std::string line = saveString.substr(currentStringIndex, saveString.find("\n"));
		currentStringIndex = saveString.find("\n");

		//saveString = saveString.substr(currentStringIndex + 1, saveString.size());	// O(n) + O(1)
		saveString.erase(0, currentStringIndex + 1);	// O(n)

		// Create load text
		UITextField* pLoadButtonText;

		// Create Button, the image is decided whether the slot has data or not
		UIButton* pLoadButton;

		if (line == "Empty")
		{
			pLoadButtonText = new UITextField(pTextFont, line.c_str(), kButtonTextColor, { (double)(kButtonX + kTextXDiff), textCurrentY }, pOwner->GetGame()->GetRenderer());
			pLoadButton = new UIButton({ kButtonX , currentButtonY, kButtonW, kSaveSlotButtonH }, kNoDataSaveSlotButtonPath, kNoDataSaveSlotButtonPath, pLoadButtonText, pOwner->GetGame()->GetRenderer());
		}
		else
		{
			pLoadButtonText = new UITextField(pSaveButtonTextFont, line.c_str(), kButtonTextColor, { (double)(kButtonX + kTextXDiff), textCurrentY }, pOwner->GetGame()->GetRenderer());
			pLoadButton = new UIButton({ kButtonX , currentButtonY, kButtonW, kSaveSlotButtonH }, kDarkSaveSlotButtonPath, kLightSaveSlotButtonPath, pLoadButtonText, pOwner->GetGame()->GetRenderer());
		}
		
		// Set function callback
		pLoadButton->SetCallback([pOwner, i]()->void
			{
				pOwner->SetSave(i);
				if (pOwner->GetSaveSystem()->Load())
				{
					if (pOwner->GetSaveSystem()->GetData().m_level == "Gameplay")
					{
						pOwner->LoadScene(PokemonGame::SceneName::kGameplay);
					}
					else if (pOwner->GetSaveSystem()->GetData().m_level == "Combat")
					{
						pOwner->LoadScene(PokemonGame::SceneName::kCombat);
					}
				}
			});

		// Find the remainning string lines
		while (saveString.find("\n") != std::string::npos)
		{
			textCurrentY += kTextYDiff;
			line = saveString.substr(0, saveString.find("\n"));
			currentStringIndex = saveString.find("\n");
			saveString.erase(0, currentStringIndex + 1);

			// Text
			pLoadButtonText = new UITextField(pSaveButtonTextFont, line.c_str(), kButtonTextColor, { ((double)kButtonX + (double)kTextXDiff), textCurrentY }, pOwner->GetGame()->GetRenderer());
			pLoadButton->AddText(pLoadButtonText);
		}

		currentButtonY += 100;
		m_gameObjects.push_back(pLoadButton);
		m_buttonSet.push_back(pLoadButton);

		delete pSave;
		pSave = nullptr;
	}

	//-------------------------------------------------------------------------------------------------
	// Main Menu button
	//-------------------------------------------------------------------------------------------------
	// Main Menu Button Text
	UITextField* pMenuButtonText = new UITextField(pTextFont, kMenuButtonText, kButtonTextColor, kMenuTextPosition, pOwner->GetGame()->GetRenderer());
	UIButton* pMenuButton = new UIButton(kMenuButtonRectangle, kDarkButtonPath, kLightButtonPath, pMenuButtonText, pOwner->GetGame()->GetRenderer());
	pMenuButton->SetCallback([pOwner]()->void
		{
			pOwner->LoadScene(PokemonGame::SceneName::kMainMenu);
		});
	m_gameObjects.push_back(pMenuButton);


	//-------------------------------------------------------------------------------------------------
	// keyboard and/or controller navigation of buttons in all game states.
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new UITextField(pNavigationFont, kMainMenuNavigationText, kNavigationColor, kMainMenuNavigationPosition, pOwner->GetGame()->GetRenderer()));
	m_gameObjects.push_back(new UITextField(pNavigationFont, kNavigationTitle, kNavigationColor, kNavigationPosition, pOwner->GetGame()->GetRenderer()));


	// Store buttons in m_buttonSet, as well.
	m_buttonSet.push_back(pMenuButton);


	TTF_CloseFont(pTextFont);
	TTF_CloseFont(pNavigationFont);
	TTF_CloseFont(pSaveButtonTextFont);
}

StateLoad::~StateLoad()
{
	for (GameObject* object : m_gameObjects)
	{
		delete object;
		object = nullptr;
	}

	m_gameObjects.clear();
}

void StateLoad::Update(double deltaTime)
{
	// Make the player walk from top to bottom contigously
	if (m_pPlayer->GetPosition().m_y > kWindowHeight)
	{
		m_pPlayer->SetPosition({ m_pPlayer->GetPosition().m_x, double(0 - m_pPlayer->GetAnimationComponent()->GetTransform().y) });
	}

	for (GameObject* pObject : m_gameObjects)
	{
		pObject->Update(deltaTime);
	}
}

void StateLoad::Render(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(pRenderer);
	for (GameObject* object : m_gameObjects)
	{
		object->Render(pRenderer);
	}
	SDL_RenderPresent(pRenderer);
}

bool StateLoad::HandleEvent(SDL_Event* pEvent)
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

void StateLoad::ChangeButtonFocus(int direction)
{
	int current = m_keyboardButtonIndex + direction;
	m_keyboardButtonIndex = (current) % m_buttonSet.capacity();

	for (unsigned i = 0; i < m_buttonSet.capacity(); ++i)
	{
		m_buttonSet[i]->SetIsHighlighted(i == m_keyboardButtonIndex);
	}
}
