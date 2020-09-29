// SDLGame.h
// Zixuan Shi
// ApplicationLayer, hold sdl window, renderer, referees.
// Classic Init(), Run(), Quit() interface

#pragma once

#include "GameObject.h"
#include "CollisionReferee.h"
#include "MusicReferee.h"
#include "SoundEffectReferee.h"
#include "Vector2D.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include <vector>

class ParticleEmitter;
class GameStateMachine;

class SDLGame
{
private:
	// Pointer to the application window managed by SDL.
	SDL_Window* m_pWindow;

	// Pointer to the renderer that can be used to draw output.
	SDL_Renderer* m_pRenderer;

	// Referee to manage active colliders.
	CollisionReferee m_collisionReferee;

	// State machine instance for managing scenes.
	GameStateMachine* m_pStateMachine;

	// Whether to quit on the next cycle.
	bool m_shouldQuit;

	// Referee to manage Background music
	MusicReferee m_musicReferee;

	// Referee to manage active Sound Effects
	SoundEffectReferee m_soundEffectReferee;

	// Particle system
	ParticleEmitter* m_pParticle;

public:
	SDLGame();
	~SDLGame();

	// Attempts to initialize SDL. Returns an error code (0 means success).
	int SetUpSDL(GameStateMachine* pStateMachine);

	// Runs the game loop. Won't exit until a quit event has been detected.
	void RunGameLoop();

	// Deinitializes SDL.
	void ShutDownSDL();

	// Quits the application.
	void Quit();

	// Gets this game's renderer instance.
	SDL_Renderer* GetRenderer() { return m_pRenderer; }

	// Gets this game's collision referee.
	CollisionReferee* GetCollisionReferee() { return &m_collisionReferee; }

	// Gets this game's sounds effect's instance
	SoundEffectReferee* GetSoundEffectReferee() { return &m_soundEffectReferee; }

private:
	// Processes events received by SDL. Returns whether or not an exit event was detected.
	bool ProcessEvents();

	// Updates the state of the game simulation based on the passage of time and any events that were detected.
	void UpdateGameState(double deltaTime);

	// Draws this program's output.
	void DisplayOutput();

	int InitialSDL();
	int SetUpSDLWindow();
	int SetUpSDLRenderer();
	int SetUpSDLTTF();
	int SetUpStateMachine(GameStateMachine* pStateMachine);
	int SetUpSDLMix();
};

