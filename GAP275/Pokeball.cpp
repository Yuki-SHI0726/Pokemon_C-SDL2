// Pokeball.cpp
// Zixuan Shi
// Pokeball class

#include "Pokeball.h"
#include "PokeballConstants.h"

#include "AnimationComponent.h"

Pokeball::Pokeball(SDL_Renderer* pRenderer, CollisionReferee* pReferee, Vector2D spawnPosition)
	: CollidableStaticObject({ (int)spawnPosition.m_x, (int)spawnPosition.m_y,(int)kWidth,(int)kHeight }, pReferee)
	, m_pAnimation{ new AnimationComponent{kSpriteSheetPath, kFrameRate, { (int)spawnPosition.m_x, (int)spawnPosition.m_y,(int)kWidth,(int)kHeight }, kFrameCount, pRenderer} }
	, m_isCollected{ false }
{
	m_objectType = "Pokeball";
	m_name = "Pokeball";

	m_pAnimation->AddAnimationSequence(kIdleAnimation, 0, 18);
	m_pAnimation->PlayAnimation(kIdleAnimation);

	m_collider.SetCollisionType(ColliderComponent::ColliderType::kTrigger);
}

Pokeball::~Pokeball()
{
	delete m_pAnimation;
	m_pAnimation = nullptr;
}

void Pokeball::Update(double deltaTime)
{
	m_pAnimation->Update(deltaTime);
}

void Pokeball::Render(SDL_Renderer* pRenderer)
{
	if (!m_isCollected)
		m_pAnimation->Render(pRenderer);
	//SDL_RenderDrawRect(pRenderer, &m_collider.GetTransform());
}
