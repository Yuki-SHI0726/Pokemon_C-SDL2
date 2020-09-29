#pragma once
#include "GameState.h"

class PokemonGame;

class StateFullGameSlot : public GameState
{
private:
	// State machine that is operating this state.
	PokemonGame* m_pOwner;

public:
	StateFullGameSlot(PokemonGame* pOwner);
	~StateFullGameSlot();

	virtual void Render(SDL_Renderer* pRenderer) override;

	virtual bool HandleEvent(SDL_Event* pEvent) override;
};

