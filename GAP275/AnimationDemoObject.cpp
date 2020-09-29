#include "Player.h"

////////////////////////////////////////////////////////
// Constructor.
////////////////////////////////////////////////////////
Player::Player(SDL_Renderer* pRenderer)
	: CollidableMovingObject()
	, m_animation("assets/mario.png", 2, 16, 16, 6, pRenderer)
{
	m_animation.AddAnimationSequence("idle", 0, 0);
	m_animation.AddAnimationSequence("run", 1, 3);
	m_animation.AddAnimationSequence("skid", 4, 4);
	m_animation.AddAnimationSequence("jump", 5, 5);
	m_animation.PlayAnimation("idle");
}

////////////////////////////////////////////////////////
// Destructor.
////////////////////////////////////////////////////////
Player::~Player()
{
}

////////////////////////////////////////////////////////
// Updates the animation component.
////////////////////////////////////////////////////////
void Player::Update(double deltaTime)
{
	m_animation.Update(deltaTime);
}

////////////////////////////////////////////////////////
// Renders the animation component.
////////////////////////////////////////////////////////
void Player::Render(SDL_Renderer * pRenderer)
{
	m_animation.Render(pRenderer);
}


