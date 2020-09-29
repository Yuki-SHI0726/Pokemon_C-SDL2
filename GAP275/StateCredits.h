// StateCredits.h
// Zixuan Shi
// Credits scene

#pragma once
#include "GameState.h"
#include <vector>
#include "Vector2D.h"
#include <SDL_ttf.h>
#include "StaticImageObject.h"

class GameObject;
class PokemonGame;
class UIButton;
class SoundEffectComponent;

//////////////////////////
// A credits state
//////////////////////////
class StateCredits : public GameState
{
private:
	PokemonGame* m_pOwner;

	// Begin storing game objects in a vector.
	std::vector<GameObject*> m_gameObjects;

	// Set of buttons in this menu.
	std::vector<UIButton*> m_buttonSet;

	// Currently active keyboard button.
	int m_keyboardButtonIndex;

	// Sound effect for credits page
	SoundEffectComponent* m_pSoundEffect;

public:
	StateCredits(PokemonGame* pOwner);
	~StateCredits();

	virtual void Render(SDL_Renderer* pRenderer) override;

	virtual bool HandleEvent(SDL_Event* pEvent) override;

	// Changes button focus when using keyboard or controller.
	void ChangeButtonFocus(int direction);
};

