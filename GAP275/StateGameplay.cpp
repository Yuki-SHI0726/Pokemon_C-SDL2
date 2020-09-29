// StateGamePlay.cpp
// Zixuan Shi
// State GamePlay scene

#include "StateGameplay.h"
#include "StateGamePlayConstants.h"

#include "PokemonGame.h"
#include "SDLGame.h"
#include "Player.h"
#include "Pokeball.h"
#include "StaticImageObject.h"
#include "CharizardInGame.h"
#include "Charmander.h"
#include "UIHealthBar.h"
#include "UITextField.h"
#include "Wall.h"
#include "Bush.h"
#include "SaveSystem.h"
#include "ParticleEmitter.h"

#include <SDL_image.h>

///////////////////////////////////////
// Constructor.
///////////////////////////////////////
StateGameplay::StateGameplay(PokemonGame* pOwner)
	: m_pOwner(pOwner)
	, m_gameObjects()
	, m_playerMovingVector{ 0,0 }
	, m_pPlayer{ nullptr }
	, m_pEnemy{ nullptr }
{
	SaveSystem* pSave = m_pOwner->GetSaveSystem();

	// If we have saved data and player was in the gameplay scene
	// #DG: Pokemon games have an option to save from the menu, it would be a good challenge for you to add that to your game as well. 
	if (pSave->GetIsLoaded() && pSave->GetData().m_level == "Gameplay")
	{
		//-------------------------------------------------------------------
		// Player save
		//-------------------------------------------------------------------
		// Player location
		Vector2D playerSavedPosition = pSave->GetData().m_playerPosition;

		// Pokeball count, if greater than one, we don't generate pokeball to this scene
		int pokeballDepot = pSave->GetData().m_pokeballDepot;

		m_pPlayer = new Player(m_pOwner->GetGame()->GetRenderer(), m_pOwner->GetGame()->GetCollisionReferee(), m_pOwner->GetGame()->GetSoundEffectReferee(), playerSavedPosition);
		m_pPlayer->SetPokeballDepot(pokeballDepot);

		//-------------------------------------------------------------------
		// Enemy save
		//-------------------------------------------------------------------
		Vector2D enemySavedPosition = pSave->GetData().m_enemyPosition;
		m_pEnemy = new Charmander{ m_pOwner->GetGame()->GetRenderer(), m_pOwner->GetGame()->GetCollisionReferee(), m_pOwner->GetGame()->GetSoundEffectReferee(), enemySavedPosition };
	}
	// if we don't have saved data
	else
	{
		m_pPlayer = new Player(m_pOwner->GetGame()->GetRenderer(), m_pOwner->GetGame()->GetCollisionReferee(), m_pOwner->GetGame()->GetSoundEffectReferee(), kPlayerPosition);

		m_pEnemy = new Charmander{ m_pOwner->GetGame()->GetRenderer(), m_pOwner->GetGame()->GetCollisionReferee(), m_pOwner->GetGame()->GetSoundEffectReferee(), kCharmanderPosition };
	}

	m_pOwner->SetIsReplaying(false);
}

///////////////////////////////////////
// Destructor.
///////////////////////////////////////
StateGameplay::~StateGameplay()
{
}

///////////////////////////////////////
// Initializes this scene.
///////////////////////////////////////
void StateGameplay::Enter()
{
	TTF_Font* pNavigationFont = TTF_OpenFont(kNavigationFontPath, kNavigationFontSize);

	//-------------------------------------------------------------------
	// Background
	//-------------------------------------------------------------------
	m_gameObjects.push_back(new StaticImageObject(kBackgroundRectangle, kBackgroundFilePath, m_pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------
	// Bushes
	//-------------------------------------------------------------------
	for (auto& bushPosition : bushPositions)
	{
		m_gameObjects.push_back(new Bush{ bushPosition ,m_pOwner->GetGame()->GetCollisionReferee(), m_pOwner->GetGame()->GetRenderer(), m_pPlayer });
	}


	//-------------------------------------------------------------------
	// Player
	//-------------------------------------------------------------------
	// Player Object
	m_gameObjects.push_back(m_pPlayer);

	// Player Hp bar
	m_gameObjects.push_back(new UIHealthBar(kHealthInterfaceSpawnPosition, m_pOwner->GetGame()->GetRenderer(), m_pPlayer));


	//-------------------------------------------------------------------
	// Pokeball, only generate pokeball when the player doesn't have any
	//-------------------------------------------------------------------
	if (m_pPlayer->GetPokeballCount() <= 0)
	{
		m_gameObjects.push_back(new Pokeball{ m_pOwner->GetGame()->GetRenderer(), m_pOwner->GetGame()->GetCollisionReferee(), kPokeballPosition });
	}


	//-------------------------------------------------------------------
	// Pokemons
	//-------------------------------------------------------------------
	m_gameObjects.push_back(m_pEnemy);


	//-------------------------------------------------------------------
	// Walls
	//-------------------------------------------------------------------
	// Edge Walls
	// m_gameObjects.push_back(new Wall{ kTopWallRectangle ,m_pOwner->GetGame()->GetCollisionReferee() });
	// m_gameObjects.push_back(new Wall{ kLeftWallRectangle ,m_pOwner->GetGame()->GetCollisionReferee() });
	// m_gameObjects.push_back(new Wall{ kRightWallRectangle ,m_pOwner->GetGame()->GetCollisionReferee() });
	// m_gameObjects.push_back(new Wall{ kBottomWallRectangle ,m_pOwner->GetGame()->GetCollisionReferee() });


	//-------------------------------------------------------------------------------------------------
	// keyboard and/or controller navigation of buttons in all game states.
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new UITextField(pNavigationFont, kGamePlayNavigationText, kNavigationColor, kMainMenuNavigationPosition, m_pOwner->GetGame()->GetRenderer()));
	m_gameObjects.push_back(new UITextField(pNavigationFont, kNavigationTitle, kNavigationColor, kNavigationPosition, m_pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Particle
	//-------------------------------------------------------------------------------------------------
	ParticleEmitter::Texture texture;
	texture.m_color = kParticleColor;
	m_gameObjects.push_back(new ParticleEmitter{ m_pPlayer->GetPosition(),kParticleSize, kParticleCount, kMaxSpeed, kRadius, texture, xRange, yRange, false, -1, m_pPlayer });


	TTF_CloseFont(pNavigationFont);
}

///////////////////////////////////////
// Updates this scene.
///////////////////////////////////////
void StateGameplay::Update(double deltaTime)
{
	for (GameObject* pObject : m_gameObjects)
	{
		pObject->Update(deltaTime);

		// #DG: this is still something that you want to put in the gameobject's update function. 
		// a better way to handle this  would be to somehow let gameobject's know which game state they are in. 
		// I only want this happen in gameplay state. So I'm not going to put this into pokemon's update function
		if (pObject->GetName() == "Charmander")
		{
			pObject->MoveRandomly(deltaTime);
		}
	}

	// If the player is dead, end the game, play player death sound effect
	if (m_pPlayer->GetCurrentHp() < 0)
	{
		m_pPlayer->GetSoundEffectComponent()->PlaySoundEffect(kPlayerDeathSoundIndex, kPlayerDeathSoundLoop);
		m_pOwner->LoadScene(PokemonGame::SceneName::kLoss);
	}

	// If the player hit the enemy (Pokemon) and the player has pokeballs, go to combat scene
	if (m_pPlayer->GetReadyToCapturePokemon())
	{
		m_pOwner->LoadScene(PokemonGame::SceneName::kCombat);
	}
}

///////////////////////////////////////
// Renders this scene.
///////////////////////////////////////
void StateGameplay::Render(SDL_Renderer* pRenderer)
{
	// Clear.
	SDL_RenderClear(pRenderer);

	// Draw.
	for (GameObject* pObject : m_gameObjects)
	{
		pObject->Render(pRenderer);
	}

	// Present.
	SDL_RenderPresent(pRenderer);
}

///////////////////////////////////////
// Handles the given event.
// Returns true when it's time to quit.
///////////////////////////////////////
bool StateGameplay::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
	case SDL_WINDOWEVENT:
		if (pEvent->window.event == SDL_WINDOWEVENT_CLOSE)
			return true;	// Signal to quit

	case SDL_KEYUP:
		ProcessKeyboardUpEvent(&pEvent->key);
		break;


	case SDL_KEYDOWN:
		return ProcessKeyboardDownEvent(&pEvent->key);
	}

	return false;
}

///////////////////////////////////////
// Cleans up this state before exit.
///////////////////////////////////////
void StateGameplay::Exit()
{
	// Save process
	SaveGame();

	for (GameObject* object : m_gameObjects)
	{
		delete object;
		object = nullptr;
	}
}

///////////////////////////////////////////////////////////////
// Save player position and whether he captured the pokeball
///////////////////////////////////////////////////////////////
bool StateGameplay::SaveGame()
{
	SaveSystem* pSave = m_pOwner->GetSaveSystem();

	// Save player position
	pSave->GetData().m_playerPosition = m_pPlayer->GetPosition();

	// Save player pokeball depot
	pSave->GetData().m_pokeballDepot = m_pPlayer->GetPokeballCount();

	// Save enemy position
	pSave->GetData().m_enemyPosition = m_pEnemy->GetPosition();

	// Save level, gameplay is level 1
	pSave->GetData().m_level = "Gameplay";

	if (m_pOwner->GetIsNewGame())
	{
		return pSave->Save(m_pOwner->GetSaveSystem()->GetTotalSaveSlotAmount());
	}
	else
	{
		return pSave->Save();
	}
}

bool StateGameplay::ProcessKeyboardDownEvent(SDL_KeyboardEvent* pEvent)
{
	// Scan the input code
	if (pEvent->keysym.scancode == SDL_SCANCODE_Q && (pEvent->keysym.mod & KMOD_CTRL))
		return true;

	// If the user want to move the character
	if (pEvent->keysym.scancode == SDL_SCANCODE_W)
	{
		m_playerMovingVector.m_y = -1;
	}

	if (pEvent->keysym.scancode == SDL_SCANCODE_S)
	{
		m_playerMovingVector.m_y = 1;
	}

	if (pEvent->keysym.scancode == SDL_SCANCODE_A)
	{
		m_playerMovingVector.m_x = -1;
	}

	if (pEvent->keysym.scancode == SDL_SCANCODE_D)
	{
		m_playerMovingVector.m_x = 1;
	}

	if (pEvent->keysym.scancode == SDL_SCANCODE_LSHIFT)
		m_pPlayer->SetSprinting(true);

	m_pPlayer->SetDirectionVector(m_playerMovingVector);

	return false;
}

void StateGameplay::ProcessKeyboardUpEvent(SDL_KeyboardEvent* pEvent)
{
	// If the user want to move the character
	if (pEvent->keysym.scancode == SDL_SCANCODE_W)
	{
		m_playerMovingVector.m_y = 0;
		m_pPlayer->SetFacingDirection(Player::FacingDirection::kNorth);
	}

	if (pEvent->keysym.scancode == SDL_SCANCODE_S)
	{
		m_playerMovingVector.m_y = 0;
		m_pPlayer->SetFacingDirection(Player::FacingDirection::kSouth);
	}

	if (pEvent->keysym.scancode == SDL_SCANCODE_A)
	{
		m_playerMovingVector.m_x = 0;
		m_pPlayer->SetFacingDirection(Player::FacingDirection::kWest);
	}

	if (pEvent->keysym.scancode == SDL_SCANCODE_D)
	{
		m_playerMovingVector.m_x = 0;
		m_pPlayer->SetFacingDirection(Player::FacingDirection::kEast);
	}

	if (pEvent->keysym.scancode == SDL_SCANCODE_LSHIFT)
		m_pPlayer->SetSprinting(false);

	//m_pPlayer->SetMoving(false);
	m_pPlayer->SetDirectionVector(m_playerMovingVector);
}
