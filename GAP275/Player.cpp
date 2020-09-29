// Player.cpp
// Zixuan Shi
// Player in game class

#include "Player.h"
#include "PlayerConstants.h"

#include "AnimationComponent.h"
#include "SoundEffectComponent.h"
#include "Pokeball.h"
#include "Bush.h"

#include <SDL_image.h>
#include <iostream>

////////////////////////////////////////////////////////
// Constructor.
////////////////////////////////////////////////////////
Player::Player(SDL_Renderer* pRenderer, CollisionReferee* pCollisionReferee, SoundEffectReferee* pSoundReferee, Vector2D spawnPosition)
	: CollidableMovingObject({ (int)spawnPosition.m_x, (int)spawnPosition.m_y, (int)kPlayerWidth, (int)kPlayerHeight }, pCollisionReferee, kPlayerHp)
	, m_pAnimation( new AnimationComponent(kPlayerSpriteSheetPath, kPlayerFrameRate, { (int)spawnPosition.m_x, (int)spawnPosition.m_y, (int)kPlayerWidth, (int)kPlayerHeight }, kPlayerFrameCount, pRenderer))
	, m_speed{ kPlayerSpeed }
	, m_isSprinting{ false }
	, m_pSoundEffect{new SoundEffectComponent(this, pSoundReferee)}
	, m_pokeballDepot{ 0 }
	, m_readyToCapturePokemon{ false }
{
	m_objectType = "Player";
	m_name = "Yuki";

	//Set up animation sequences
	m_pAnimation->AddAnimationSequence(kFacingDownIdleAnimation.c_str(), 0, 0);
	m_pAnimation->AddAnimationSequence(kFacingDownRunAnimation.c_str(), 1, 2);
	m_pAnimation->AddAnimationSequence(kFacingUpIdleAnimation.c_str(), 3, 3);
	m_pAnimation->AddAnimationSequence(kFacingUpRunAnimation.c_str(), 4, 5);
	m_pAnimation->AddAnimationSequence(kFacingRightIdleAnimation.c_str(), 6, 6);
	m_pAnimation->AddAnimationSequence(kFacingRightRunAnimation.c_str(), 7, 8);
	m_pAnimation->AddAnimationSequence(kFacingLeftIdleAnimation.c_str(), 9, 9);
	m_pAnimation->AddAnimationSequence(kFacingLeftRunAnimation.c_str(), 10, 11);
	m_pAnimation->PlayAnimation(kFacingDownIdleAnimation);
	
	// Set up sound effects
	m_pSoundEffect->AddSoundEffect(kPlayerInitiationSoundEffectFilePath, kInitiationVolume);
	m_pSoundEffect->AddSoundEffect(kPlayerDeathSoundEffectFilePath, kDeathVolume);

	// Play initiation sound
	m_pSoundEffect->PlaySoundEffect(kInitiationIndex, kInitiationLoop);
}

////////////////////////////////////////////////////////
// Destructor.
////////////////////////////////////////////////////////
Player::~Player()
{
	delete m_pAnimation;
	m_pAnimation = nullptr;

	delete m_pSoundEffect;
	m_pSoundEffect = nullptr;
}

////////////////////////////////////////////////////////
// Updates the animation component.
////////////////////////////////////////////////////////
void Player::Update(double deltaTime)
{
	double deltaPosition = m_speed * deltaTime;

	if (CheckCollision(deltaPosition))
	{
		UpdatePosition(deltaPosition);
		UpdateAnimation(deltaTime);
	}
}

////////////////////////////////////////////////////////
// Renders the animation component.
////////////////////////////////////////////////////////
void Player::Render(SDL_Renderer * pRenderer)
{
	m_pAnimation->Render(pRenderer);
	//SDL_RenderDrawRect(pRenderer, &m_collider.GetTransform());
}

////////////////////////////////////////////////////////////////
// Do the work if the player is on collision with other object
////////////////////////////////////////////////////////////////
void Player::OnCollision(ColliderComponent* pOtherCollider)
{
	// Pokeball
	if (pOtherCollider->GetOwner()->GetObjectType() == "Pokeball")
	{
		Pokeball* pPokeball = static_cast<Pokeball*>(pOtherCollider->GetOwner());

		// If the player has collected that ball
		if (pPokeball->GetIsCollected())
		{
			//std::cout << "You already collected this pokeball";
		}
		else
		{
			// Add pokeball depot
			std::cout << "\nCollected a pokeball!\n";
			++m_pokeballDepot;
			pPokeball->SetIsCollected(true);
		}
	}

	// Pokemon
	if (pOtherCollider->GetOwner()->GetObjectType() == "Pokemon" && m_pokeballDepot > 0)
	{
		m_readyToCapturePokemon = true;
	}
}

/////////////////////////////////////////////////
// Update player position and collider position
/////////////////////////////////////////////////
void Player::UpdatePosition(double deltaPosition)
{
	// Player
	// Idle
	if (m_directionVector.m_y == 0 && m_directionVector.m_x == 0)
	{
		if (m_facingDirection == FacingDirection::kWest)
		{
			m_pAnimation->PlayAnimation(kFacingLeftIdleAnimation.c_str());
		}

		if (m_facingDirection == FacingDirection::kEast)
		{
			m_pAnimation->PlayAnimation(kFacingRightIdleAnimation.c_str());
		}

		if (m_facingDirection == FacingDirection::kNorth)
		{
			m_pAnimation->PlayAnimation(kFacingUpIdleAnimation.c_str());
		}

		if (m_facingDirection == FacingDirection::kSouth)
		{
			m_pAnimation->PlayAnimation(kFacingDownIdleAnimation.c_str());
		}
	}
	// Moving
	else
	{
		// Left
		if (m_directionVector.m_x == -1)
		{
			m_position.m_x -= (m_isSprinting) ? (2 * deltaPosition) : (deltaPosition);
			m_pAnimation->PlayAnimation(kFacingLeftRunAnimation.c_str());
		}

		// Right
		if (m_directionVector.m_x == 1)
		{
			m_position.m_x += (m_isSprinting) ? (2 * deltaPosition) : (deltaPosition);
			m_pAnimation->PlayAnimation(kFacingRightRunAnimation.c_str());
		}

		// Up
		if (m_directionVector.m_y == -1)
		{
			m_position.m_y -= (m_isSprinting) ? (2 * deltaPosition) : (deltaPosition);
			m_pAnimation->PlayAnimation(kFacingUpRunAnimation.c_str());
		}

		// Down
		if (m_directionVector.m_y == 1)
		{
			m_position.m_y += (m_isSprinting) ? (2 * deltaPosition) : (deltaPosition);
			m_pAnimation->PlayAnimation(kFacingDownRunAnimation.c_str());
		}
	}

	// Update Collider position
	m_collider.SetPosition(m_position);
}

void Player::UpdateAnimation(double deltaTime)
{
	m_pAnimation->SetPosition(m_position);
	m_pAnimation->Update(deltaTime);
}

//////////////////////////////////////////////////////////////
// Return true if able to move to the destination.
// Return false if the player shouldn't move to the destination
//////////////////////////////////////////////////////////////
bool Player::CheckCollision(double deltaPosition)
{
	// The destination X of the player
	double destinationX = (m_directionVector.m_x * deltaPosition);

	// The destination Y of the player
	double destinationY = (m_directionVector.m_y * deltaPosition);

	// The destination of the player
	Vector2D destinationPosition(destinationX, destinationY);

	bool canMove = TryMove(destinationPosition);

	return canMove;
}
