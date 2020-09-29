// StateWin.h
// Zixuan Shi
// State Win scene

#pragma once
#include "GameState.h"

#include "SDL_ttf.h"
#include "StaticImageObject.h"

#include <vector>

class GameObject;
class PokemonGame;
class UIButton;

////////////////////////////////////////////////
// If the player won the game, go to this scene
////////////////////////////////////////////////
class StateWin : public GameState
{
private:
	PokemonGame* m_pOwner;

	std::vector<GameObject*> m_gameObjects;

	std::vector<UIButton*> m_buttonSet;

	int m_keyboardButtonIndex;

public:
	StateWin(PokemonGame* pOwner);
	~StateWin();

	virtual void Update(double deltaTime) override;

	// Renders this scene.
	virtual void Render(SDL_Renderer* pRenderer) override;

	// Handles the given event.
	// Returns true when it's time to quit.
	virtual bool HandleEvent(SDL_Event* pEvent) override;

	// Changes button focus when using keyboard or controller.
	void ChangeButtonFocus(int direction);
};

