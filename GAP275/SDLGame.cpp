// SDLGame.cpp
// Zixuan Shi
// ApplicationLayer, hold sdl window, renderer, referees.
// Classic Init(), Run(), Quit() interface

#include "SDLGame.h"

#include "GameConstants.h"
#include "GameStateMachine.h"

#include <chrono>
#include <iostream>

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <limits>
#include <cmath>
#include <iomanip>

SDLGame::SDLGame()
	: m_pWindow(nullptr)
	, m_pRenderer(nullptr)
	, m_collisionReferee()
	, m_pStateMachine(nullptr)
	, m_shouldQuit(false)
	, m_musicReferee{ }
	, m_soundEffectReferee{}
	, m_pParticle{}
{
}

SDLGame::~SDLGame()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Attempts to initialize SDL. Returns an error code (0 means success).
///////////////////////////////////////////////////////////////////////////////////////////////////////////
int SDLGame::SetUpSDL(GameStateMachine* pStateMachine)
{
	if (InitialSDL() == kErrorCode)
		return kErrorCode;

	if (SetUpSDLWindow() == kErrorCode)
		return kErrorCode;

	if (SetUpSDLRenderer() == kErrorCode)
		return kErrorCode;

	if (SetUpSDLMix() == kErrorCode)
		return kErrorCode;

	// Begins listening for events from gamepad ID 0. The gamepad must already be plugged in for this to
	// work, so ideally you should wait for the SDL_CONTROLLERDEVICEADDED event instead. For local
	// multiplayer, you will need to call this once for each player.
	SDL_GameControllerOpen(0);

	if (SetUpSDLTTF() == kErrorCode)
		return kErrorCode;

	if (SetUpStateMachine(pStateMachine) == kErrorCode)
		return kErrorCode;

	// Success.
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Runs the game loop. Won't exit until a quit event has been detected.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SDLGame::RunGameLoop()
{
	bool shouldQuit = false;

	// Allocate a time_point outside that loop so that it is retained between frames.
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::high_resolution_clock::now();

	while (!shouldQuit)
	{
		// Get current time_point.
        auto thisFrameTime = std::chrono::high_resolution_clock::now();

		// Subtract last frame's time_point from this frame's time_point to get the duration of the frame.
        std::chrono::duration<double> lastFrameDuration = thisFrameTime - lastFrameTime;

        // Convert the duration to a double.
        double deltaTime = lastFrameDuration.count();
		
		// Don't forget to pass newFrameCounter into lastFrameCounter.
        lastFrameTime = thisFrameTime;

		shouldQuit = ProcessEvents();

		UpdateGameState(deltaTime);	// Update now takes in delta time.

		m_musicReferee.Update(deltaTime);	// Update the music player

		DisplayOutput();

		if (m_shouldQuit)
			shouldQuit = true;
	}

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> totalGameTime = end - start;

	double gameTime = totalGameTime.count();

	std::cout << "\nYou spent " << std::setprecision(3) << gameTime << " seconds on my Pokemon game. Thank you!\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Deinitializes SDL.
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void SDLGame::ShutDownSDL()
{
	// Save
	//SaveSystem::SaveData& saveData = m_saveSystem.GetData();

	// Just showing
	// saveData.m_playerLocation = playerCurrentPosition;
	//m_saveSystem.Save();

	if (m_pStateMachine != nullptr)
		m_pStateMachine->Cleanup();

	Mix_CloseAudio();			// Close Audio mixer
	m_musicReferee.CleanUp();	// Destroy background music

	SDL_DestroyRenderer(m_pRenderer);	// Destroy renderer.
	SDL_DestroyWindow(m_pWindow);		// Destroy window.
	SDL_Quit();							// Deinitialize SDL.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quits the application.
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void SDLGame::Quit()
{
	m_shouldQuit = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Processes events received by SDL. Returns whether or not the game should continue.
///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SDLGame::ProcessEvents()
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{
		bool quit = m_pStateMachine->HandleEvent(&evt);
		if (quit)
			return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Updates the state of the game simulation based on the passage of time and any events that were detected.
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void SDLGame::UpdateGameState(double deltaTime)
{
	m_pStateMachine->UpdateCurrentState(deltaTime);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draws this program's output.
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void SDLGame::DisplayOutput()
{
	m_pStateMachine->RenderCurrentState(m_pRenderer);
}

//////////////////////////////
// Set up SDL
//////////////////////////////
int SDLGame::InitialSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0)
	{
		std::cout << "SDL_Init() succeeded." << std::endl;
		return 0;
	}
	else
	{
		// SDL_Image
		IMG_Init(IMG_INIT_JPG);

		std::cout << "SDL_Init() failed. Error code " << kErrorCode << ": " << SDL_GetError() << std::endl;
		return kErrorCode;
	}
}

///////////////////////////////
// Create a SDL window here
///////////////////////////////
int SDLGame::SetUpSDLWindow()
{
	// The game is played in an 800x600 unresizable window.

	// Change this later
	m_pWindow = SDL_CreateWindow("Programming_ZixuanShi_Pokemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWindowWidth, kWindowHeight, 0);

	void SDL_SetWindowResizable(SDL_Window * m_pWindow, SDL_bool SDL_FALSE);

	if (m_pWindow != nullptr)
	{
		std::cout << "SDL_CreateWindow() succeeded" << std::endl;
		return kGoodCode;
	}
	else
	{
		std::cout << "SDL_CreateWindow() failed. Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		system("pause");
		return kErrorCode;
	}
}

//////////////////////////////
// Set up SDL renderer here
//////////////////////////////
int SDLGame::SetUpSDLRenderer()
{
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

	if (m_pRenderer != nullptr)
	{
		std::cout << "SDL_CreateRenderer() succeeded" << std::endl;
		return kGoodCode;
	}
	else
	{
		std::cout << "SDL_CreateRenderer() failed" << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return kErrorCode;
	}
}

////////////////////////
// Initialize SDL_ttf.
////////////////////////
int SDLGame::SetUpSDLTTF()
{
	int ttfReturnCode = TTF_Init();

	if (ttfReturnCode == 0)
	{
		std::cout << "TTF_Init() succeeded" << SDL_GetError() << std::endl;
		return ttfReturnCode;
	}
	else
	{
		std::cout << "TTF_Init() failed. Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return ttfReturnCode;
	}
}

int SDLGame::SetUpStateMachine(GameStateMachine* pStateMachine)
{
	// Initialize state machine.
	if (pStateMachine != nullptr && pStateMachine->Init())
	{
		// Print success message.
		std::cout << "State machine succeeded." << std::endl;
		m_pStateMachine = pStateMachine;
		return 0;
	}
	else
	{
		std::cout << "Failed to create state machine." << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_DestroyRenderer(m_pRenderer);
		SDL_Quit();
		system("pause");
		return kErrorCode;
	}
}


//////////////////////////////////////
// Initialize SDL_mixer
int SDLGame::SetUpSDLMix()
{
	int errorCode = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	if (errorCode == 0)
	{
		std::cout << "Mix_OpenAudio() Succeeded." << std::endl;
	}
	else
	{
		std::cout << "Mix_OpenAudio() Failed. Error: " << Mix_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		return errorCode;
	}

	int audioFlags = MIX_INIT_MP3;
	errorCode = Mix_Init(audioFlags);

	if (errorCode == audioFlags)
	{
		std::cout << "Mix_Init() Succeeded." << std::endl;
	}
	else
	{
		std::cout << "Mix_Init() failed. Error: " << Mix_GetError() << std::endl;
		Mix_CloseAudio();
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		return errorCode;
	}

	// Add musics and play
	m_musicReferee.AddMusicSequence(kMusicBPath);
	m_musicReferee.AddMusicSequence(kMusicAPath);
	m_musicReferee.PlayMusic();

	return errorCode;
}
