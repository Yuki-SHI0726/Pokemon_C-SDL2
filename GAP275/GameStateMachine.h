// GameStateMachine.h
// Zixuan Shi
// State Pattern for game, state machine

#pragma once

class GameState;
struct SDL_Renderer;
union SDL_Event;

/////////////////////////////////////////////////////
// An interface for handling game states/scenes.
/////////////////////////////////////////////////////
class GameStateMachine
{
public:
	virtual ~GameStateMachine() {}

	// Initializes this state machine.
	// Returns false if any errors occur.
	virtual bool Init() = 0;

	// Updates the currently active scene.
	virtual void UpdateCurrentState(double deltaTime) = 0;

	// Renders the currently active scene.
	virtual void RenderCurrentState(SDL_Renderer* pRenderer) = 0;

	// Handles the given event.
	// Returns true when it's time to quit.
	virtual bool HandleEvent(SDL_Event* pEvent) = 0;

	// Exits current state and enters new state.
	virtual void ChangeState(GameState* pNewState) = 0;

	// Cleans up this state machine.
	// Returns false if any errors occur.
	virtual bool Cleanup() = 0;
};

