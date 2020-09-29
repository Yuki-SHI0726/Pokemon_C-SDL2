// PokemonGame.h
// Zixuan Shi
// State machine for this game, inherited from GameStateMachine

#pragma once
#include "GameStateMachine.h"
#include <SDL_ttf.h>
#include "SaveSystem.h"

class GameState;
class SDLGame;
struct SDL_Renderer;

/////////////////////////////////////////////
// Example GameStateMachine implementation.
/////////////////////////////////////////////
class PokemonGame : public GameStateMachine
{
public:
	enum class SceneName
	{
		kTitleScreen,	// Real Pokemon game always have a title screen.
		kMainMenu,
		kGameplay,
		kCredits,
		kPokemonBattle,
		kWin,
		kCombat,	// Pokemon combat scene
		kLoss,
		kLoad
	};

private:
	// SDLGame object that owns this machine.
	SDLGame* m_pOwner;

	// Currently active scene.
	GameState* m_pCurrentState;

	// A queue up scene.
	// Will become active on the next update.
	GameState* m_pNextState;

	// UI font.
	TTF_Font* m_pFont;

	// Saving and loading manager
	SaveSystem m_saveSystem;

	// Current Game slot
	size_t m_currentGameSaveSlot;

	bool m_isNewGame;

	bool m_isReplaying;

public:
	PokemonGame(SDLGame* pOwner);
	~PokemonGame();

	// Initializes this state machine.
	// Returns false if any errors occur.
	virtual bool Init() override;

	// Updates the currently active scene.
	virtual void UpdateCurrentState(double deltaTime) override;

	// Renders the currently active scene.
	virtual void RenderCurrentState(SDL_Renderer* pRenderer) override;

	// Handles the given event.
	// Returns true when it's time to quit.
	virtual bool HandleEvent(SDL_Event* pEvent) override;

	// Exits current state and enters new state.
	virtual void ChangeState(GameState* pNewState) override;

	// Loads the given scene on the next update.
	void LoadScene(SceneName scene);

	// Gets the SDLGame object that is running this machine.
	SDLGame* GetGame() { return m_pOwner; }

	// Cleans up this state machine.
	// Returns false if any errors occur.
	virtual bool Cleanup() override;

	// Gets this game's save system instance
	SaveSystem* GetSaveSystem() { return &m_saveSystem; }

	bool GetIsNewGame() const { return m_isNewGame; }
	bool GetIsReplaying() const { return m_isReplaying; }

	void SetSave(size_t slot) { m_saveSystem = SaveSystem(slot); }
	void SetCurrentGameSavingSlot() { m_currentGameSaveSlot = m_saveSystem.GetTotalSaveSlotAmount(); }
	void SetIsNewGame(bool boolean) { m_isNewGame = boolean; }
	void SetIsReplaying(bool boolean) { m_isReplaying = boolean; }
};

