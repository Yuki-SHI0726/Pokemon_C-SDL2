// GameState.h
// Zixuan Shi
// State pattern for game, base class of states

#pragma once

struct SDL_Renderer;
union SDL_Event;

//////////////////////////////////
// A game state/scene interface.
//////////////////////////////////
class GameState
{
public:
	virtual ~GameState() {}

	// Initializes this scene.
	virtual void Enter() {}

	// Updates this scene.
	virtual void Update(double deltaTime) {}

	// Renders this scene.
	virtual void Render(SDL_Renderer* pRenderer) = 0;

	// Handles the given event.
	// Returns true when it's time to quit.
	virtual bool HandleEvent(SDL_Event* pEvent) = 0;

	// Cleans up this state before exit.
	virtual void Exit() {}

	// Save system
	virtual bool SaveGame() { return false; }
};

