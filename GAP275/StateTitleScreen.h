// StateTitleScreen.h
// Zixuan Shi
// State TitleScreen scene

#pragma once
#include "GameState.h"
#include "StaticImageObject.h"

#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include "Vector2D.h"

class PokemonGame;
class GameObject;

class StateTitleScreen : public GameState
{
private:
	// State machine that is operating this state.
	PokemonGame* m_pOwner;

	// Begin storing game objects in a vector.
	std::vector<GameObject*> m_gameObjects;

public:
	StateTitleScreen(PokemonGame* pOwner);
	~StateTitleScreen();

	// Renders this scene.
	virtual void Render(SDL_Renderer* pRenderer) override;

	// Handles the given event.
	// Returns true when it's time to quit.
	virtual bool HandleEvent(SDL_Event* pEvent) override;
};

