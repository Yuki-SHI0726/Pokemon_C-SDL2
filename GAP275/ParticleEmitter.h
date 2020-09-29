// ParticleEmitter.h
// Zixuan Shi
// ParticleEmitter class, spawn and play particles

#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "RandomNumberGenerator.h"

#include <utility>

class StaticImageObject;
class CollidableMovingObject;

///////////////////////////////
// Particle 
///////////////////////////////
class ParticleEmitter : public GameObject
{
public:
	// Texture union
	union Texture
	{
		SDL_Texture* m_pTexture = nullptr;
		SDL_Color m_color;
	};

	struct Particle
	{
		Vector2D m_positionOffset;
		Vector2D m_velocity;
	};

private:
	// Particle source position.
	Vector2D m_centerPoint;

	// Particle size
	Vector2D m_size;

	// Number of particles in this instance.
	int m_particleCount;

	// Square of the maximum distance particles travel.
	float m_radius;

	// Array of particles.
	Particle* m_pParticles;

	// Random generator
	RandomNumberGenerator m_rng;

	// Particle will follow it's owner and update position by owner's current position
	CollidableMovingObject* m_pOwner;

	// Particle texture, supports either color or texture
	Texture m_texture;

	// A boolean to check if we are using texture to render the particle
	bool m_isUsingTexture;

	// The time that this particle lasts, default to -1, means last forever until we exit the scene
	double m_lifeTime;

	// Used for cone-shaped particle, default to 360 degrees
	// #DG: this could have also been the Vector2D class you created
	std::pair<float, float> m_particleXRange;
	std::pair<float, float> m_particleYRange;

public:
	// Support color ctor
	// #DG: use another object to pass to the constructor, rather than bloat the constructor like this
	ParticleEmitter(Vector2D centerPoint, Vector2D size, int particleCount, float maxSpeed, float radius, // Particle info
		Texture texture, std::pair<float, float> xRange = { -1.0f, 1.0f }, std::pair<float, float> yRange = { -1.0f, 1.0f }, bool isUsingTexture = false,	// Rendering
		double lifeTime = -1, CollidableMovingObject* pOwner = nullptr);
	
	~ParticleEmitter();

	virtual void Update(double deltaTime) override;
	virtual void Render(SDL_Renderer* pRenderer) override;

	// Particle acceleration (particles can be made to speed up or slow down)
	void SetSpeed(float maxSpeed = 60.0f, int particleIndex = -1);
	void SetTexture(Texture texture, int particleIndex = -1, bool isUsingTexture = false);
	void SetIsUsingTexture(bool isUsingTexture) { m_isUsingTexture = isUsingTexture; }
	void SetSize(Vector2D size) { m_size = size; }
};

