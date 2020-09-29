// PokemonGame.cpp
// Zixuan Shi
// State machine for this game, inherited from GameStateMachine

#include "PokemonGame.h"

#include "SaveSystem.h"
#include "StateGameplay.h"
#include "StateMainMenu.h"
#include "StateCredits.h"
#include "StateTitleScreen.h"
#include "StateLoss.h"
#include "StateWin.h"
#include "StateCombat.h"
#include "StateLoad.h"

#include "SDLGame.h"

/////////////////////////////////////////////
// Constructor.
/////////////////////////////////////////////
PokemonGame::PokemonGame(SDLGame* pOwner)
	: m_pOwner(pOwner)
	, m_pCurrentState(nullptr)
	, m_pNextState(nullptr)
	, m_pFont{ nullptr }
	, m_saveSystem{ 0 }
	, m_currentGameSaveSlot{0}
	, m_isNewGame{ false }
	, m_isReplaying{ false }
{
}

/////////////////////////////////////////////
// Destructor.
/////////////////////////////////////////////
PokemonGame::~PokemonGame()
{
}

/////////////////////////////////////////////
// Initializes this state machine.
// Returns false if any errors occur.
/////////////////////////////////////////////
bool PokemonGame::Init()
{
	LoadScene(SceneName::kTitleScreen);
	return true;
}

/////////////////////////////////////////////
// Updates current state.
/////////////////////////////////////////////
void PokemonGame::UpdateCurrentState(double deltaTime)
{
	if (m_pNextState != nullptr)
	{
		ChangeState(m_pNextState);
		m_pNextState = nullptr;
	}

	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Update(deltaTime);
	}
}

/////////////////////////////////////////////
// Renders current state.
/////////////////////////////////////////////
void PokemonGame::RenderCurrentState(SDL_Renderer* pRenderer)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Render(pRenderer);
	}
}

/////////////////////////////////////////////
// Handles the given event.
// Returns true when it's time to quit.
/////////////////////////////////////////////
bool PokemonGame::HandleEvent(SDL_Event* pEvent)
{
	if (m_pCurrentState == nullptr)
	{
		return false;
	}
	else
	{
		return m_pCurrentState->HandleEvent(pEvent);
	}
}

/////////////////////////////////////////////
// Exits current state and enters pNewState.
/////////////////////////////////////////////
void PokemonGame::ChangeState(GameState* pNewState)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
	}

	delete m_pCurrentState;
	m_pCurrentState = pNewState;
	pNewState->Enter();
}

/////////////////////////////////////////////
// Loads the given scene on the next update.
/////////////////////////////////////////////
void PokemonGame::LoadScene(SceneName scene)
{
	// If you load the next scene right away, you run the danger of destroying the
	// scene in the middle of a loop.
	// So instead let it be destroyed at the beginning of the next update.

	switch (scene)
	{
	case SceneName::kTitleScreen:
		m_pNextState = new StateTitleScreen(this);
		break;
	case SceneName::kMainMenu:
		m_pNextState = new StateMainMenu(this);
		break;
	case SceneName::kGameplay:
		m_pNextState = new StateGameplay(this);
		break;
	case SceneName::kCredits:
		m_pNextState = new StateCredits(this);
		break;
	case SceneName::kLoss:
		m_pNextState = new StateLoss(this);
		break;
	case SceneName::kWin:
		m_pNextState = new StateWin(this);
		break;
	case SceneName::kCombat:
		m_pNextState = new StateCombat(this);
		break;
	case SceneName::kLoad:
		m_pNextState = new StateLoad(this);
		break;
	}
}

/////////////////////////////////////////////
// Cleans up this state machine.
// Returns false if any errors occur.
/////////////////////////////////////////////
bool PokemonGame::Cleanup()
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
		delete m_pCurrentState;
	}

	TTF_CloseFont(m_pFont);

	return true;
}