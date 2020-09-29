// Bush.cpp
// Zixuan Shi
// Bush object implementation

#include "Bush.h"
#include "BushConstants.h"

#include "Player.h"
#include "StaticImageObject.h"

#include <iostream>
#include <SDL_image.h>

Bush::Bush(Vector2D spawnPosition, CollisionReferee* pReferee, SDL_Renderer* pRenderer, Player* pPlayer)
	: CollidableStaticObject{ {(int)spawnPosition.m_x, (int)spawnPosition.m_y, kWidth, kHeight}, pReferee }
	, m_transform{ (int)spawnPosition.m_x, (int)spawnPosition.m_y, kWidth, kHeight }
	, m_isOnEnter{ false }
	, m_pPlayer{ pPlayer }
	, m_pDarkImage{ new StaticImageObject{m_transform , kDarkBushPath, pRenderer } }
	, m_pBrightImage{ new StaticImageObject{m_transform , kBrightBushPath, pRenderer } }
	, m_randomNumberGenerator{}
	, m_isDirty{ false }
{
	m_objectType = "Bush";
	m_objectType = "Wall";

	//m_isFirstTimeEnter = true;

	// Collision
	m_collider.SetCollisionType(ColliderComponent::ColliderType::kTrigger);
}

Bush::~Bush()
{
	delete m_pDarkImage;
	m_pDarkImage = nullptr;
	delete m_pBrightImage;
	m_pBrightImage = nullptr;
}

void Bush::Render(SDL_Renderer* pRenderer)
{
	StaticImageObject* pOject = m_isOnEnter ? m_pBrightImage : m_pDarkImage;
	pOject->Render(pRenderer);
}

void Bush::Update(double deltaTime)
{
	m_isOnEnter = CheckPlayerOnEnter();

	// If player is on enter and has pokeball, generate random number to get pokemon
	if ((m_isOnEnter) && (m_pPlayer->GetPokeballCount() > 0) && (!m_isDirty))
	{
		// Generate random number 
		int encounterPokemonChance = m_randomNumberGenerator.GenerateRandomNumber<int>(kEncounterPokemonChance);

		if (encounterPokemonChance == 1)
		{
			// Reduce player's pokeball depot
			m_pPlayer->ReducePokeballAmount();

			m_pPlayer->SetReadyCapturePokemon(true);
		}

		m_isDirty = true;
	}
}

//////////////////////////////////////////////////////////////////////////////////////
// Return true if the player is above the bush
// The purpose of this function is I want to know if the player has left the bush
//////////////////////////////////////////////////////////////////////////////////////
bool Bush::CheckPlayerOnEnter()
{
	// Calculator bush bounds
	int bushLeft = m_transform.x;
	int bushRight = m_transform.x + m_transform.w;
	int bushTop = m_transform.y;
	int bushBottom = m_transform.y + m_transform.h;

	// Calculate Player bounds.
	int otherLeft = m_pPlayer->GetAnimationComponent()->GetTransform().x;
	int otherRight = m_pPlayer->GetAnimationComponent()->GetTransform().x + m_pPlayer->GetAnimationComponent()->GetTransform().w;
	int otherTop = m_pPlayer->GetAnimationComponent()->GetTransform().y + (m_pPlayer->GetAnimationComponent()->GetTransform().h / 2);	// I only want my player's lower half body can trigger the bush collision
	int otherBottom = m_pPlayer->GetAnimationComponent()->GetTransform().y + m_pPlayer->GetAnimationComponent()->GetTransform().h;

	bool xOverlap = bushLeft < otherRight && bushRight > otherLeft;

	// Check if they also overlap vertically
	// by comparing top vs. bottom and bottom vs. top.
	bool yOverlap = bushTop < otherBottom && bushBottom > otherTop;

	// If they overlap both horizontally and vertically,
	// then they truly overlap.
	if (xOverlap && yOverlap)
	{
		return true;
	}
	else
	{
		m_isDirty = false;
		return false;
	}
}
