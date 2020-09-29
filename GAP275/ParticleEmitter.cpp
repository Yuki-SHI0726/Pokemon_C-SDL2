// ParticleEmitter.cpp
// Zixuan Shi
// ParticleEmitter class, spawn and play particles

#include "ParticleEmitter.h"
#include "CollidableMovingObject.h"

#include <SDL_image.h>

///////////////////////////
// Ctor
///////////////////////////
// 
ParticleEmitter::ParticleEmitter(Vector2D centerPoint, Vector2D size, int particleCount, float maxSpeed, float radius, 
	Texture texture, std::pair<float, float> xRange, std::pair<float, float> yRange, bool isUsingTexture,
	double lifeTime, CollidableMovingObject* pOwner)
	: m_centerPoint{ centerPoint }
	, m_size{ size }
	, m_particleCount{ particleCount }
	, m_radius{ radius }
	, m_pParticles{ new Particle[m_particleCount] }
	, m_rng{}
	, m_pOwner{ pOwner }
	, m_isUsingTexture{ isUsingTexture }
	, m_lifeTime{ lifeTime }
	, m_particleXRange{ xRange }
	, m_particleYRange{ yRange }
{
	if (isUsingTexture)
		m_texture.m_pTexture = texture.m_pTexture;
	else
		m_texture.m_color = texture.m_color;

	m_objectType = "Particle Emitter";
	
	// Set each loop's initial offset and randomized velocity.
	for (int i = 0; i < m_particleCount; ++i)
	{
		m_pParticles[i].m_positionOffset = { Vector2D{} };

		SetSpeed(maxSpeed, i);
	}
}

ParticleEmitter::~ParticleEmitter()
{
	if (m_isUsingTexture)
		SDL_DestroyTexture(m_texture.m_pTexture);

	delete[] m_pParticles;
	m_pParticles = nullptr;
}

///////////////////////////////////////////
// Loop over paricles and update position
///////////////////////////////////////////
void ParticleEmitter::Update(double deltaTime)
{
	// If the particle system has an owner, follow the owner
	if (m_pOwner)
	{
		m_centerPoint.m_x = m_pOwner->GetPosition().m_x + (m_pOwner->GetTransform().w / 2);
		m_centerPoint.m_y = m_pOwner->GetPosition().m_y /*+ (m_pOwner->GetTransform().h / 2)*/;
	}

	for (int i = 0; i < m_particleCount; ++i)
	{
		// Update each particle's position.
		m_pParticles[i].m_positionOffset.m_x += m_pParticles[i].m_velocity.m_x * (float)deltaTime;
		m_pParticles[i].m_positionOffset.m_y += m_pParticles[i].m_velocity.m_y * (float)deltaTime;
		
		// If Particle is past the edge of the system radius recycle it.
		if (m_pParticles[i].m_positionOffset.GetSquareLength() > m_radius)
		{
			if (m_lifeTime == -2)
				m_shouldErase = true;
			else
				m_pParticles[i].m_positionOffset = { Vector2D{} };
		}
	}
}

//////////////////////////////////////////////
// Render every particle
//////////////////////////////////////////////
void ParticleEmitter::Render(SDL_Renderer* pRenderer)
{
	// All particles will be rendered with a solid color we are not using Texture
	if (!m_isUsingTexture)
		SDL_SetRenderDrawColor(pRenderer, m_texture.m_color.r, m_texture.m_color.g, m_texture.m_color.b, m_texture.m_color.a);
	
	for (int i = 0; i < m_particleCount; ++i)
	{
		Particle& particle = m_pParticles[i];
		Vector2D& position = particle.m_positionOffset;

		SDL_Rect particleTransform;
		particleTransform.x = (int)m_centerPoint.m_x + (int)position.m_x;
		particleTransform.y = (int)m_centerPoint.m_y + (int)position.m_y;
		particleTransform.h = (int)m_size.m_x;	// Particle's height
		particleTransform.w = (int)m_size.m_y;	// Particle's width

		if (m_isUsingTexture)
			SDL_RenderCopy(pRenderer, m_texture.m_pTexture, nullptr, &particleTransform);
		else
			SDL_RenderFillRect(pRenderer, &particleTransform);
	}
}

////////////////////////////////////////////////////////////////////
// Particles can be made to speed up or slow down by this functoin
// particleIndex is for time complexity purpose
////////////////////////////////////////////////////////////////////
void ParticleEmitter::SetSpeed(float maxSpeed, int particleIndex)
{
	if (particleIndex == -1)
	{
		// Set each loop's initial offset and randomized velocity.
		for (int i = 0; i < m_particleCount; ++i)
		{
			// Particles may travel UP TO maxSpeed pixels per second.
			m_pParticles[i].m_velocity = Vector2D{ ((double)m_rng.GenerateRandomFloat(m_particleXRange.first, m_particleXRange.second) * maxSpeed), ((double)m_rng.GenerateRandomFloat(m_particleYRange.first, m_particleYRange.second) * maxSpeed) };
		}
	}
	else
	{
		m_pParticles[particleIndex].m_positionOffset = { Vector2D{} };
		m_pParticles[particleIndex].m_velocity = Vector2D{ ((double)m_rng.GenerateRandomFloat(m_particleXRange.first, m_particleXRange.second) * maxSpeed), ((double)m_rng.GenerateRandomFloat(m_particleYRange.first, m_particleYRange.second) * maxSpeed) };
	}
}

void ParticleEmitter::SetTexture(Texture texture, int particleIndex, bool isUsingTexture)
{
}
