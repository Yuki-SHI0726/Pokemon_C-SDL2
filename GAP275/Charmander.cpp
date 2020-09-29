// Charmander.cpp
// Zixuan Shi
// Charmander class

#include "Charmander.h"

#include "AnimationComponent.h"
#include "SoundEffectComponent.h"
#include "SoundEffectReferee.h"
#include "AIComponent.h"
#include "AIHalfHpState.h"
#include "RandomNumberGenerator.h"

#include <SDL_image.h>

Charmander::Charmander(SDL_Renderer* pRenderer, CollisionReferee* pCollisionReferee, SoundEffectReferee* pSoundReferee, Vector2D spawnPosition)
	: Pokemon{ pRenderer, pCollisionReferee, pSoundReferee, { (int)spawnPosition.m_x, (int)spawnPosition.m_y, (int)kCharmanderWidth, (int)kCharmanderHeight }, kCharmanderHp, kSpriteSheetPath, kCharmanderFrameCount, kCharmanderFrameRate, kDamage }
	, m_randomNumberGenerator{}
{
	m_objectType = "Pokemon";
	m_name = "Charmander";

	// Set up animations
	m_pAnimation->AddAnimationSequence(kIdleAnimation, 0, 4);
	m_pAnimation->PlayAnimation(kIdleAnimation);

	// Set up sound effects
	m_pSoundEffect->AddSoundEffect(kCharmanderRoarSoundEffectFilePath, kRoarVolume);

	// Set collision type
	m_collider.SetCollisionType(ColliderComponent::ColliderType::kTrigger);
}

Charmander::~Charmander()
{
	delete m_pAnimation;
	m_pAnimation = nullptr;

	delete m_pSoundEffect;
	m_pSoundEffect = nullptr;
}

void Charmander::Update(double deltaTime)
{
	m_pAnimation->Update(deltaTime);
}

void Charmander::Render(SDL_Renderer* pRenderer)
{
	m_pAnimation->Render(pRenderer);
	//SDL_RenderDrawRect(pRenderer, &m_collider.GetTransform());
}

void Charmander::ChangeState(AIState* pNewState)
{
}

///////////////////////////////
// Move Randomly
///////////////////////////////
void Charmander::MoveRandomly(double deltaTime)
{
	// Time calculator
	static double time = 0;

	time += deltaTime;

	if (time > kMoveCD)
	{
		// For four directions
		int direction = m_randomNumberGenerator.GenerateRandomNumber<int>(3);

		switch (direction)
		{
		case 0:
			m_position.m_x -= kMovingDistance;
			break;

		case 1:
			++m_position.m_x += kMovingDistance;
			break;

		case 2:
			m_position.m_y -= kMovingDistance;
			break;

		case 3:
			++m_position.m_y += kMovingDistance;
			break;
		default:
			break;
		}

		// Set animation
		m_pAnimation->SetPosition(m_position);

		// Set collider position
		m_collider.SetPosition(m_position);

		// Reset time
		time = 0;
	}
}
