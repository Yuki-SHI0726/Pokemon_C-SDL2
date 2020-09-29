// StateCombat.h
// Zixuan Shi
// Combat scene

#include "StateCombat.h"
#include "StateCombatConstants.h"

#include "PokemonGame.h"
#include "SDLGame.h"
#include "StaticImageObject.h"
#include "UIHealthBar.h"
#include "UIButton.h"
#include "UITextField.h"
#include "SoundEffectComponent.h"
#include "ParticleEmitter.h"
#include "Player.h"
#include "CharizardInGame.h"
#include "Charmander.h"
#include "Pikachu.h"

#include <SDL_image.h>

StateCombat::StateCombat(PokemonGame* pOwner)
	: m_pOwner{ pOwner }
	, m_gameObjects{}
	, m_keyboardButtonIndex{ 0 }
	, m_pPikachu{ nullptr }
	, m_pEnemy{ nullptr }
	, m_pEnemyUIBar{ nullptr }
	, m_hasTranformed{ false }
{
	SaveSystem* pSave = m_pOwner->GetSaveSystem();

	// If we have saved data and player was in the gameplay scene
	if (pSave->GetIsLoaded() && pSave->GetData().m_level == "Combat")
	{
		//-------------------------------------------------------------------
		// Check if the enemy is charmander or charizard
		//-------------------------------------------------------------------
		m_hasTranformed = !pSave->GetData().m_isFightingCharmander;


		//-------------------------------------------------------------------
		// Enemy save
		//-------------------------------------------------------------------
		double enemyHp = pSave->GetData().m_enemyHp;
		// If we haven't transformed yet, we need to spawn a Charmander, vice-versa
		if (!m_hasTranformed)
		{		
			m_pEnemy = new Charmander(m_pOwner->GetGame()->GetRenderer(), m_pOwner->GetGame()->GetCollisionReferee(), m_pOwner->GetGame()->GetSoundEffectReferee(), kCharmanderPosition);
		}
		else
		{
			m_pEnemy = new CharizardInGame(m_pOwner->GetGame()->GetRenderer(), m_pOwner->GetGame()->GetCollisionReferee(), m_pOwner->GetGame()->GetSoundEffectReferee(), kCharizardPosition);
		}
		m_pEnemy->SetHp(enemyHp);


		//-------------------------------------------------------------------
		// Player save
		//-------------------------------------------------------------------
		double pikachuHp = pSave->GetData().m_playerHp;

		m_pPikachu = new Pikachu(m_pOwner->GetGame()->GetRenderer(), m_pOwner->GetGame()->GetCollisionReferee(), m_pOwner->GetGame()->GetSoundEffectReferee(), kPikachuPosition);
		m_pPikachu->SetHp(pikachuHp);
	}
	// if we don't have saved data
	else
	{
		m_pPikachu = new Pikachu(m_pOwner->GetGame()->GetRenderer(), m_pOwner->GetGame()->GetCollisionReferee(), m_pOwner->GetGame()->GetSoundEffectReferee(), kPikachuPosition);

		m_pEnemy = new Charmander{ m_pOwner->GetGame()->GetRenderer(), m_pOwner->GetGame()->GetCollisionReferee(), m_pOwner->GetGame()->GetSoundEffectReferee(), kCharmanderPosition };
	}
}

StateCombat::~StateCombat()
{

}

void StateCombat::Enter()
{
	TTF_Font* pTextFont = TTF_OpenFont(kTextFontPath, kTextFontSize);


	//-------------------------------------------------------------------------------------------------
	// Picture Background
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new StaticImageObject(kBackgroundRectangle, kBackgroundFilePath, m_pOwner->GetGame()->GetRenderer()));


	//-------------------------------------------------------------------------------------------------
	// Pokemons
	//-------------------------------------------------------------------------------------------------
	// Enemy Charmander
	m_gameObjects.emplace_back(m_pEnemy);
	m_pEnemy->GetSoundEffectComponent()->PlaySoundEffect(kCharmanderRoarIndex, kCharmanderRoarLoop);

	// Enemy hp bar
	m_pEnemyUIBar = new UIHealthBar(kEnemyHealthInterfaceSpawnPosition, m_pOwner->GetGame()->GetRenderer(), m_pEnemy);
	m_gameObjects.push_back(m_pEnemyUIBar);

	// Pikachu (as player)
	m_gameObjects.emplace_back(m_pPikachu);

	// Pikachu hp bar
	m_gameObjects.push_back(new UIHealthBar(kPikachuHealthInterfaceSpawnPosition, m_pOwner->GetGame()->GetRenderer(), m_pPikachu));


	//-------------------------------------------------------------------------------------------------
	// Thunder button
	//-------------------------------------------------------------------------------------------------
	// Thunder Button Text
	UITextField* pThunderButtonText = new UITextField(pTextFont, kThunderButtonText, kButtonTextColor, kThunderTextPosition, m_pOwner->GetGame()->GetRenderer());

	// Button
	UIButton* pThunderButton = new UIButton(kThunderButtonRectangle, kDarkButtonPath, kLightButtonPath, pThunderButtonText, m_pOwner->GetGame()->GetRenderer());
	pThunderButton->SetCallback([this]()->void
		{
			m_pPikachu->SetIsThundering(true);
			this->m_pPikachu->Thunder(this->m_pEnemy);
		});
	m_gameObjects.push_back(pThunderButton);


	//-------------------------------------------------------------------------------------------------
	// keyboard and/or controller navigation of buttons in all game states.
	//-------------------------------------------------------------------------------------------------
	m_gameObjects.push_back(new UITextField(pTextFont, kCombatNavigationText, kNavigationColor, kCombatNavigationPosition, m_pOwner->GetGame()->GetRenderer()));
	m_gameObjects.push_back(new UITextField(pTextFont, kNavigationTitle, kNavigationColor, kNavigationPosition, m_pOwner->GetGame()->GetRenderer()));


	// Store buttons in m_buttonSet, as well.
	m_buttonSet.push_back(pThunderButton);


	TTF_CloseFont(pTextFont);
}

void StateCombat::Update(double deltaTime)
{
	for (GameObject* pObject : m_gameObjects)
	{
		pObject->Update(deltaTime);

		if (pObject->GetShouldErase())
		{
			delete pObject;
			m_gameObjects.erase(std::find(m_gameObjects.begin(), m_gameObjects.end(), pObject));
		}
	}

	// charmander attack 
	if (m_pEnemy->GetCurrentHp() > 0)
	{
		static double timeCount = 0;
		timeCount += deltaTime;

		if (timeCount >= 2)
		{
			ParticleEmitter::Texture texture;
			SDL_Surface* pSurface = IMG_Load(kFireTexturePath);
			texture.m_pTexture = SDL_CreateTextureFromSurface(m_pOwner->GetGame()->GetRenderer(), pSurface);
			SDL_FreeSurface(pSurface);

			m_gameObjects.emplace_back(new ParticleEmitter{ kCharmanderAttackPosition,kSize, kCount, kSpeed, kAttackRadius, texture, fireXRange, fireYRange, true, -2 });
			m_pPikachu->TakeDamage(m_pEnemy->GetAttackDamage());

			timeCount = 0;
		}
	}

	if (m_pPikachu->GetIsThundering())
	{
		ParticleEmitter::Texture texture;
		SDL_Surface* pSurface = IMG_Load(kThunderTexturePath);
		texture.m_pTexture = SDL_CreateTextureFromSurface(m_pOwner->GetGame()->GetRenderer(), pSurface);
		SDL_FreeSurface(pSurface);

		m_gameObjects.emplace_back(new ParticleEmitter{ m_pPikachu->GetPosition(),kSize, kCount, kSpeed, kAttackRadius, texture, thunderXRange, thunderYRange, true, -2 });

		m_pPikachu->SetIsThundering(false);
	}

	// If the enemy is less than half hp, upgrade
	if ((m_pEnemy->GetCurrentHp() <= (m_pEnemy->GetTotalHp() * 0.61)) && !m_hasTranformed)
	{
		ProcessCharmanderEvolutionEvent();
	}

	// If the pikachu is dead, end the game with loss scene
	if (m_pPikachu->GetCurrentHp() < 0)
	{
		m_pOwner->LoadScene(PokemonGame::SceneName::kLoss);
	}

	// If the enemy is dead, end the game with win 
	if (m_pEnemy->GetCurrentHp() <= 0)
	{
		// Wait for a couple of seconds, play praticle
		static bool hasSpawnParticle = false;
		static double timeCount = 0;
		timeCount += deltaTime;

		if (!hasSpawnParticle)
		{
			// spawn cone-shaped particle
			ParticleEmitter::Texture texture;
			texture.m_color = kParticleColor;
			m_gameObjects.push_back(new ParticleEmitter{ {m_pEnemy->GetPosition().m_x + ((m_pEnemy->GetTransform().w / 2) + 20.0) , m_pEnemy->GetPosition().m_y + (m_pEnemy->GetTransform().h / 2) }, kParticleSize, kParticleCount, kMaxSpeed, kRadius, texture, xRange, yRange, false, -1});

			// Death sound effect
			m_pEnemy->GetSoundEffectComponent()->PlaySoundEffect(kDeathIndex, kDeathLoop);

			hasSpawnParticle = true;
		}

		if (timeCount >= 5)
		{	
			// reset data for replaying
			m_hasTranformed = false;
			m_pEnemy->SetHp(kCharmanderHp);
			m_pPikachu->SetHp(m_pPikachu->GetTotalHp());
			timeCount = 0;
			hasSpawnParticle = false;

			// Go to the win state
			m_pOwner->LoadScene(PokemonGame::SceneName::kWin);
		}
	}
}

void StateCombat::Render(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(pRenderer);
	for (GameObject* object : m_gameObjects)
	{
		object->Render(pRenderer);
	}
	SDL_RenderPresent(pRenderer);
}

bool StateCombat::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
	case SDL_WINDOWEVENT:
		if (pEvent->window.event == SDL_WINDOWEVENT_CLOSE)
			return true;	// Signal to quit


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

void StateCombat::Exit()
{
	SaveGame();

	for (GameObject* object : m_gameObjects)
	{
		delete object;
		object = nullptr;
	}
}

bool StateCombat::SaveGame()
{
	SaveSystem* pSave = m_pOwner->GetSaveSystem();

	// Save is fighting charmander
	pSave->GetData().m_isFightingCharmander = !m_hasTranformed;

	// Save player position
	pSave->GetData().m_playerHp = m_pPikachu->GetCurrentHp();
	
	// Save player pokeball depot
	pSave->GetData().m_enemyHp = (m_pOwner->GetIsReplaying()) ? (kCharmanderHp) : (m_pEnemy->GetCurrentHp());

	// Save level, gameplay is level 1
	pSave->GetData().m_level = "Combat";

	if (m_pOwner->GetIsNewGame())
	{
		return pSave->Save(m_pOwner->GetSaveSystem()->GetTotalSaveSlotAmount());
	}
	else
	{
		return pSave->Save();
	}
}

bool StateCombat::ProcessKeyboardDownEvent(SDL_KeyboardEvent* pEvent)
{
	return false;
}

void StateCombat::ProcessKeyboardUpEvent(SDL_KeyboardEvent* pEvent)
{
}

void StateCombat::ProcessCharmanderEvolutionEvent()
{
	// Clean the charmander
	delete m_pEnemy;
	m_gameObjects.erase(std::find(m_gameObjects.begin(), m_gameObjects.end(), m_pEnemy));

	// Clean the charmander's UI bar
	delete m_pEnemyUIBar;
	m_gameObjects.erase(std::find(m_gameObjects.begin(), m_gameObjects.end(), m_pEnemyUIBar));

	// Get a new enemy
	m_pEnemy = new CharizardInGame(m_pOwner->GetGame()->GetRenderer(), m_pOwner->GetGame()->GetCollisionReferee(), m_pOwner->GetGame()->GetSoundEffectReferee(), kCharizardPosition);
	m_gameObjects.emplace_back(m_pEnemy);

	// Give a new enemy a health bar
	m_pEnemyUIBar = new UIHealthBar(kEnemyHealthInterfaceSpawnPosition, m_pOwner->GetGame()->GetRenderer(), m_pEnemy);
	m_gameObjects.emplace_back(m_pEnemyUIBar);

	m_pEnemy->GetSoundEffectComponent()->PlaySoundEffect(kCharmanderRoarIndex, kCharmanderRoarLoop);

	// Set the transformed boolean to true
	m_hasTranformed = true;
}

void StateCombat::ChangeButtonFocus(int direction)
{
	int current = m_keyboardButtonIndex + direction;
	m_keyboardButtonIndex = (current) % m_buttonSet.capacity();

	for (unsigned i = 0; i < m_buttonSet.capacity(); ++i)
	{
		m_buttonSet[i]->SetIsHighlighted(i == m_keyboardButtonIndex);
	}
}
