#include "StateFullGameSlot.h"

StateFullGameSlot::StateFullGameSlot(PokemonGame* pOwner)
	: m_pOwner{ pOwner }
{
}

StateFullGameSlot::~StateFullGameSlot()
{
}

void StateFullGameSlot::Render(SDL_Renderer* pRenderer)
{
}

bool StateFullGameSlot::HandleEvent(SDL_Event* pEvent)
{
	return false;
}
