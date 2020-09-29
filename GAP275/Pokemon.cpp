// Pokemon.cpp
// Zixuan Shi
// Base class of pokemon

#include "Pokemon.h"

#include "AnimationComponent.h"
#include "SoundEffectComponent.h"
#include "SoundEffectReferee.h"

#include <SDL_image.h>

Pokemon::Pokemon(SDL_Renderer* pRenderer, CollisionReferee* pCollisionReferee, SoundEffectReferee* pSoundReferee, SDL_Rect pokemonRectangle, double pokemonHp,
	const char* kPokemonSpriteSheet, int frameCount, int frameRate, int damage)
	: CollidableMovingObject(pokemonRectangle, pCollisionReferee, pokemonHp)
	, m_pAnimation{ new AnimationComponent(kPokemonSpriteSheet, frameRate, pokemonRectangle, frameCount, pRenderer) }
	, m_pSoundEffect{ new SoundEffectComponent(this, pSoundReferee) }
	, m_pCurrentState{ nullptr }
	, m_pPreviousState{ nullptr }
	, m_attackDamage{ damage }
{
}

Pokemon::~Pokemon()
{
	delete m_pAnimation;
	m_pAnimation = nullptr;

	delete m_pSoundEffect;
	m_pSoundEffect = nullptr;
}
