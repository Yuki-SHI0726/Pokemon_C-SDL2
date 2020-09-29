// Charizard.cpp
// Zixuan Shi
// Charizard class

#include "CharizardInGame.h"
#include "CharizardConstants.h"

#include "AnimationComponent.h"
#include "SoundEffectComponent.h"
#include "SoundEffectReferee.h"

#include <SDL_image.h>


CharizardInGame::CharizardInGame(SDL_Renderer* pRenderer, CollisionReferee* pCollisionReferee, SoundEffectReferee* pSoundReferee, Vector2D spawnPosition)
	: Pokemon{ pRenderer, pCollisionReferee, pSoundReferee, { (int)spawnPosition.m_x, (int)spawnPosition.m_y, (int)kCharizardWidth, (int)kCharizardHeight }, kCharizardHp, kSpriteSheetPath, kCharizardFrameCount, kCharizardFrameRate, kCharizardAttack }
{
	m_objectType = "Pokemon";
	m_name = "Charizard";

	// Set up animations
	m_pAnimation->AddAnimationSequence(kIdleAnimation, 0, 7);
	m_pAnimation->AddAnimationSequence(kDeadAnimation, 8, 8);
	m_pAnimation->PlayAnimation(kIdleAnimation);

	// Set up sound effects
	m_pSoundEffect->AddSoundEffect(kCharizardRoarSoundEffectFilePath, kRoarVolume);
	m_pSoundEffect->AddSoundEffect(kCharizardDeathSoundEffectFilePath, kDeathVolume);

	// Set collision
	m_collider.SetCollisionType(ColliderComponent::ColliderType::kTrigger);
}

CharizardInGame::~CharizardInGame()
{
	delete m_pAnimation;
	m_pAnimation = nullptr;

	delete m_pSoundEffect;
	m_pSoundEffect = nullptr;
}

void CharizardInGame::Update(double deltaTime)
{
	if (m_currentHp <= 0)
		m_pAnimation->PlayAnimation(kDeadAnimation);

	m_pAnimation->Update(deltaTime);
}

void CharizardInGame::Render(SDL_Renderer* pRenderer)
{
	m_pAnimation->Render(pRenderer);
	//SDL_RenderDrawRect(pRenderer, &m_collider.GetTransform());
}

void CharizardInGame::ChangeState(AIState* pNewState)
{
}
