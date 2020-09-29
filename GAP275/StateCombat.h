// StateCombat.h
// Zixuan Shi
// Combat scene

#pragma once
#include "GameState.h"

#include "CollidableMovingObject.h"
#include "Vector2D.h"

#include <SDL_ttf.h>
#include <vector>
#include <SDL_mixer.h>
#include <SDL.h>

class GameObject;
class PokemonGame;
class UIButton;
class SoundEffectReferee;
struct SDL_Renderer;
class Player;
class CharizardInGame;
class Pikachu;
class Charmander;
class Pokemon;
class UIHealthBar;

/////////////////////////////////////////////////
// Combat scene implementation
/////////////////////////////////////////////////
class StateCombat :	public GameState
{
private:
	// State machine that is operating this state.
	PokemonGame* m_pOwner;

	// Begin storing game objects in a vector.
	std::vector<GameObject*> m_gameObjects;

	// Set of buttons in this combat scene.
	std::vector<UIButton*> m_buttonSet;

	// Currently active keyboard button.
	int m_keyboardButtonIndex;

	// As player
	Pikachu* m_pPikachu;

	// As enemy
	Pokemon* m_pEnemy;
	UIHealthBar* m_pEnemyUIBar;
	bool m_hasTranformed;

public:
	StateCombat(PokemonGame* pOwner);
	~StateCombat();

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

	// Save player hp and enemy hp
	virtual bool SaveGame() override final;

private:
	bool ProcessKeyboardDownEvent(SDL_KeyboardEvent* pEvent);
	void ProcessKeyboardUpEvent(SDL_KeyboardEvent* pEvent);

	void ProcessCharmanderEvolutionEvent();

	// Changes button focus when using keyboard or controller.
	void ChangeButtonFocus(int direction);
};

