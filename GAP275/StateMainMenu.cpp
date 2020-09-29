// StateMainMenu.cpp
// Zixuan Shi
// State MainMenu scene

#include "StateMainMenu.h"
#include "StateMainMenuConstants.h"

#include "PokemonGame.h"
#include "SDLGame.h"
#include "UIButton.h"
#include "UITextField.h"
#include "StaticImageObject.h"
#include "CharizardInGame.h"
#include "SoundEffectComponent.h"
#include "ParticleEmitter.h"

#include <iostream>
#include <SDL_ttf.h>
#include <SDL_image.h>

//////////////////////////////////////////////////////////
// Constructor.
//////////////////////////////////////////////////////////
StateMainMenu::StateMainMenu(PokemonGame* pOwner)
	: m_pOwner(pOwner)
	, m_gameObjects()
	, m_keyboardButtonIndex{ 0 }
	, m_particles{  }
{
	// Load font.
	TTF_Font* pTextFont = TTF_OpenFont(kTextFontPath, kTextFontSize);
	TTF_Font* pNavigationFont = TTF_OpenFont(kNavigationFontPath, kNavigationFontSize);

	//-------------------------------------------------------------------------------------------------
	// Picture Background
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new StaticImageObject(kBackgroundRectangle, kBackgroundFilePath, pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Charizard
	//-------------------------------------------------------------------------------------------------
	CharizardInGame* pCharizard = new CharizardInGame(pOwner->GetGame()->GetRenderer(), pOwner->GetGame()->GetCollisionReferee(), pOwner->GetGame()->GetSoundEffectReferee(), kCharizardPosition);
	m_gameObjects.emplace_back(pCharizard);
	pCharizard->GetSoundEffectComponent()->PlaySoundEffect(kRoarIndex, kRoarLoop);


	//-------------------------------------------------------------------------------------------------
	// Title text
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new UITextField(pTextFont, kTitle, kTitleColor, kTitlePosition, pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Play button
	//-------------------------------------------------------------------------------------------------
	// Play Button Text
	UITextField* pPlayButtonText = new UITextField(pTextFont, kPlayButtonText, kButtonTextColor, kPlayTextPosition, pOwner->GetGame()->GetRenderer());
	// Button
	UIButton* pPlayButton = new UIButton(kPlayButtonRectangle, kDarkButtonPath, kLightButtonPath, pPlayButtonText, pOwner->GetGame()->GetRenderer());
	pPlayButton->SetCallback([pOwner]()->void
		{
			if (pOwner->GetSaveSystem()->GetTotalSaveSlotAmount() <= kMaxSaveSlotCount)
			{
				pOwner->SetCurrentGameSavingSlot();
				pOwner->SetIsNewGame(true);
				pOwner->LoadScene(PokemonGame::SceneName::kGameplay);
			}
			else
			{
				std::cout << "The save slot is full!";
			}
		});
	m_gameObjects.push_back(pPlayButton);
	m_buttonSet.push_back(pPlayButton);

	//-------------------------------------------------------------------------------------------------
	// Credits button
	//-------------------------------------------------------------------------------------------------
	// Credits Button Text
	UITextField* pCreditsButtonText = new UITextField(pTextFont, kCreditsButtonText, kButtonTextColor, kCreditsTextPosition, pOwner->GetGame()->GetRenderer());
	UIButton* pCreditsButton = new UIButton(kCreditsButtonRectangle, kDarkButtonPath, kLightButtonPath, pCreditsButtonText, pOwner->GetGame()->GetRenderer());
	pCreditsButton->SetCallback([pOwner]()->void
		{
			pOwner->LoadScene(PokemonGame::SceneName::kCredits);
		});
	m_gameObjects.push_back(pCreditsButton);
	m_buttonSet.push_back(pCreditsButton);

	//-------------------------------------------------------------------------------------------------
	// Load button, load old game from disk
	//-------------------------------------------------------------------------------------------------
	// Load Button Text
	UITextField* pLoadButtonText = new UITextField(pTextFont, kLoadButtonText, kButtonTextColor, kLoadTextPosition, pOwner->GetGame()->GetRenderer());
	UIButton* pLoadButton = new UIButton(kLoadButtonRectangle, kDarkButtonPath, kLightButtonPath, pLoadButtonText, pOwner->GetGame()->GetRenderer());
	pLoadButton->SetCallback([pOwner]()->void
		{
			pOwner->LoadScene(PokemonGame::SceneName::kLoad);
		});
	m_gameObjects.push_back(pLoadButton);
	m_buttonSet.push_back(pLoadButton);


	//-------------------------------------------------------------------------------------------------
	// Quit button
	//-------------------------------------------------------------------------------------------------
	// Quit Button Text
	UITextField* pQuitButtonText = new UITextField(pTextFont, kQuitButtonText, kButtonTextColor, kQuitTextPosition, pOwner->GetGame()->GetRenderer());
	UIButton* pQuitButton = new UIButton(kQuitButtonRectangle, kDarkButtonPath, kLightButtonPath, pQuitButtonText, pOwner->GetGame()->GetRenderer());
	pQuitButton->SetCallback([pOwner]()->void
		{
			pOwner->GetGame()->Quit();
		});
	m_gameObjects.push_back(pQuitButton);
	m_buttonSet.push_back(pQuitButton);


	//-------------------------------------------------------------------------------------------------
	// keyboard and/or controller navigation of buttons in all game states.
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new UITextField(pNavigationFont, kMainMenuNavigationText, kNavigationColor, kMainMenuNavigationPosition, pOwner->GetGame()->GetRenderer()));
	m_gameObjects.push_back(new UITextField(pNavigationFont, kNavigationTitle, kNavigationColor, kNavigationPosition, pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Particle
	//-------------------------------------------------------------------------------------------------
	// Create right particle texture
	ParticleEmitter::Texture texture;
	SDL_Surface* pSurface = IMG_Load(kRightParticleTexturePath);
	texture.m_pTexture = SDL_CreateTextureFromSurface(pOwner->GetGame()->GetRenderer(), pSurface);

	SDL_SetTextureAlphaMod(texture.m_pTexture, kAlphaTexture);	// New stuff

	// Create right particle object
	ParticleEmitter* pRightParticle = new ParticleEmitter{ kRightParticlePosition,kParticleSize, kParticleCount, kMaxSpeed, kRadius, texture, rightXRange, rightYRange, true, kParticleDuration };
	m_gameObjects.push_back(pRightParticle);
	m_particles.emplace_back(pRightParticle);

	// Create left particle texture
	pSurface = IMG_Load(kLeftParticleTexturePath);
	texture.m_pTexture = SDL_CreateTextureFromSurface(pOwner->GetGame()->GetRenderer(), pSurface);
	SDL_FreeSurface(pSurface);

	// Create left particle object
	ParticleEmitter* pLeftParticle = new ParticleEmitter{ kLeftParticlePosition,kParticleSize, kParticleCount, kMaxSpeed, kRadius, texture, leftXRange, leftYRange, true, kParticleDuration };
	m_gameObjects.push_back(pLeftParticle);
	m_particles.emplace_back(pLeftParticle);


	TTF_CloseFont(pTextFont);
	TTF_CloseFont(pNavigationFont);
}

//////////////////////////////////////////////////////////
// Destructor.
//////////////////////////////////////////////////////////
StateMainMenu::~StateMainMenu()
{
	for (GameObject* object : m_gameObjects)
	{
		delete object;
		object = nullptr;
	}

	m_gameObjects.clear();
}

///////////////////////////////////////
// Updates this scene.
///////////////////////////////////////
void StateMainMenu::Update(double deltaTime)
{
	for (GameObject* pObject : m_gameObjects)
	{
		pObject->Update(deltaTime);
	}

	// For particles slow down and speed up
	static double time = 0;
	static bool shouldSetSlow = true;
	time += deltaTime;

	if (time >= kTransformSecond)
	{
		// Set speed
		for (auto& particle : m_particles)
		{
			particle->SetSpeed((shouldSetSlow) ? (kMinSpeed) : (kMaxSpeed));
		}

		// Reset data
		shouldSetSlow = !shouldSetSlow;
		time = 0;
	}
}

//////////////////////////////////////////////////////////
// Renders this scene.
//////////////////////////////////////////////////////////
void StateMainMenu::Render(SDL_Renderer* pRenderer)
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
bool StateMainMenu::HandleEvent(SDL_Event* pEvent)
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

//////////////////////////////////////////////////////////
// Changes button focus when using keyboard or controller.
//////////////////////////////////////////////////////////
void StateMainMenu::ChangeButtonFocus(int direction)
{
	int current = m_keyboardButtonIndex + direction;
	m_keyboardButtonIndex = (current) % m_buttonSet.capacity();

	for (unsigned i = 0; i < m_buttonSet.capacity(); ++i)
	{
		m_buttonSet[i]->SetIsHighlighted(i == m_keyboardButtonIndex);
	}
}
