// StateGamePlay.h
// Zixuan Shi
// State GamePlay scene

#pragma once
#include "GameState.h"
#include "CollidableMovingObject.h"
#include <vector>

class GameObject;
class PokemonGame;
class CharizardInGame;
struct SDL_Renderer;
class Player;
class Pokemon;

///////////////////////////////////////
// Gameplay scene implementation.
///////////////////////////////////////
class StateGameplay : public GameState
{
private:
	// State machine that is operating this state.
	PokemonGame* m_pOwner;

	// Player game object.
	Player* m_pPlayer;
	Vector2D m_playerMovingVector;
	Pokemon* m_pEnemy;

	// References to game objects in this scene.
	std::vector<GameObject*> m_gameObjects;

public:
	StateGameplay(PokemonGame* pOwner);
	~StateGameplay();

	// Initializes this scene.
	virtual void Enter() override;

	// Updates this scene.
	virtual void Update(double deltaTime) override;

	// Renders this scene.
	virtual void Render(SDL_Renderer* pRenderer) override;

	// Handles the given event.
	// Returns true when it's time to quit.
	virtual bool HandleEvent(SDL_Event* pEvent) override;

	// Cleans up this state before exit.
	virtual void Exit() override;

	// Save player position and whether he captured the pokeball
	virtual bool SaveGame() override final;

private:
	bool ProcessKeyboardDownEvent(SDL_KeyboardEvent* pEvent);
	void ProcessKeyboardUpEvent(SDL_KeyboardEvent* pEvent);
};

