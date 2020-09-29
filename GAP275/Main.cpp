// Main.cpp
// Zixuan Shi
// Program entrance

//#include <vld.h>

#include "SDLGame.h"
#include "PokemonGame.h"

int main(int argc, char* argv[])
{
	// Allocate game manager.
	SDLGame game;
	
	// Allocate game implementation.
	PokemonGame gameInstance(&game);
	
	// Initialize game manager with state machine implementation.
	int returnCode = game.SetUpSDL(&gameInstance);
	
	// Run loop.
	game.RunGameLoop();
	
	// Clean up.
	game.ShutDownSDL();
	
	// Exit.
	return returnCode;
}
