// Pikachu.cpp
// Zixuan Shi
// Pikachu class

#include "Pikachu.h"
#include "PikachuConstants.h"

#include "AnimationComponent.h"
#include "SoundEffectComponent.h"
#include "SoundEffectReferee.h"

#include <iostream>
#include <SDL_image.h>

Pikachu::Pikachu(SDL_Renderer* pRenderer, CollisionReferee* pCollisionReferee, SoundEffectReferee* pSoundReferee, Vector2D spawnPosition)
	: Pokemon{ pRenderer, pCollisionReferee, pSoundReferee, {(int)spawnPosition.m_x, (int)spawnPosition.m_y, (int)kPikachuWidth,(int)kPikachuHeight}, kPikachuHp, kPikachuSpriteSheetPath, kPikachuFrameCount, kPikachuFrameRate, kPikachuAttack }
	, m_isThundering{ false }
{
	m_objectType = "Pokemon";
	m_name = "Pikachu";

	// Set up animations
	m_pAnimation->AddAnimationSequence(kIdleAnimation, 0, 0);
	m_pAnimation->PlayAnimation(kIdleAnimation);

	// Set up sound effects
	m_pSoundEffect->AddSoundEffect(kPikachuRoarSoundEffectFilePath, kRoarVolume);
	m_pSoundEffect->AddSoundEffect(kPikachuThunderCriticalStrikeSoundEffectFilePath, kRoarVolume);
	m_pSoundEffect->AddSoundEffect(kPikachuThunderSoundEffectFilePath, kRoarVolume);
	m_pSoundEffect->PlaySoundEffect(kRoarIndex, kRoarLoop);

	m_collider.SetCollisionType(ColliderComponent::ColliderType::kTrigger);
}

Pikachu::~Pikachu()
{
	delete m_pAnimation;
	m_pAnimation = nullptr;

	delete m_pSoundEffect;
	m_pSoundEffect = nullptr;
}

void Pikachu::Update(double deltaTime)
{
	m_pAnimation->Update(deltaTime);
}

void Pikachu::Render(SDL_Renderer* pRenderer)
{
	m_pAnimation->Render(pRenderer);
	//SDL_RenderDrawRect(pRenderer, &m_collider.GetTransform());
}

void Pikachu::Thunder(CollidableMovingObject* pTarget)
{
	// Get a random number for critical strike
	int randomNumber = m_randomNumberGenerator.GenerateRandomNumber(kCriticalStrikeChance);

	// Critical Strike attack occurs if randomNumber is 1
	pTarget->TakeDamage((randomNumber == 1) ? (kThunderDamage * 2) : (kThunderDamage));

	if (randomNumber == 1)
	{
		std::cout << "Pikachu performed a critical strike!" << std::endl;
		m_pSoundEffect->PlaySoundEffect(kThunderIndex, kThunderLoop);
	}
	else
	{
		m_pSoundEffect->PlaySoundEffect(kLaserIndex, kLaserLoop);
	}
}

void Pikachu::TailWhip(CollidableMovingObject* pTarget)
{
	pTarget->TakeDamage(kTailWhipDamage);
}

void Pikachu::ChangeState(AIState* pNewState)
{
}
