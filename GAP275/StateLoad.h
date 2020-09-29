// StateLoad.h
// Zixuan Shi
// State Load scene

#pragma once
#include "GameState.h"

#include <vector>

class GameObject;
class PokemonGame;
class UIButton;
class SoundEffectReferee;
class Player;

//////////////////////////////////////////////////
// Module 13, Saving and Loading
//////////////////////////////////////////////////
class StateLoad : public GameState
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

	Player* m_pPlayer;

public:
	StateLoad(PokemonGame* pOwner);
	~StateLoad();

	virtual void Update(double deltaTime) override;

	// Renders this scene.
	virtual void Render(SDL_Renderer* pRenderer) override;

	// Handles the given event.
	// Returns true when it's time to quit.
	virtual bool HandleEvent(SDL_Event* pEvent) override;

	// Changes button focus when using keyboard or controller.
	void ChangeButtonFocus(int direction);
};

