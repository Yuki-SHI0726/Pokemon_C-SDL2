// StateMainMenu.h
// Zixuan Shi
// State MainMenu scene

#pragma once
#include "GameState.h"

#include "Vector2D.h"

#include <vector>

class GameObject;
class PokemonGame;
class UIButton;
class SoundEffectReferee;
class ParticleEmitter;

//////////////////////////////////////////////////////////
// Example main menu scene implementation.
//////////////////////////////////////////////////////////
class StateMainMenu : public GameState
{
private:
	// State machine that is operating this state.
	PokemonGame* m_pOwner;

	// Begin storing game objects in a vector.
	std::vector<GameObject*> m_gameObjects;

	// Set of buttons in this menu.
	std::vector<UIButton*> m_buttonSet;

	// Currently active keyboard button.
	int m_keyboardButtonIndex;

	// Particle system
	std::vector<ParticleEmitter*> m_particles;

public:
	StateMainMenu(PokemonGame* pOwner);
	~StateMainMenu();

	virtual void Update(double deltaTime) override;

	// Renders this scene.
	virtual void Render(SDL_Renderer* pRenderer) override;

	// Handles the given event.
	// Returns true when it's time to quit.
	virtual bool HandleEvent(SDL_Event* pEvent) override;

	// Changes button focus when using keyboard or controller.
	void ChangeButtonFocus(int direction);
};

