// AnimationComponent.h
// Zixuan Shi
// This component handles animation playing

#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <string>
#include <map>

////////////////////////////////////////////////////////////////////
// A game object component for handling animation.
////////////////////////////////////////////////////////////////////
class AnimationComponent
{
private:

	////////////////////////////////////////////////////////////////////
	// A named animation sequence.
	////////////////////////////////////////////////////////////////////
	struct AnimationSequence
	{
	public:
		std::string m_name;
		int m_firstFrame;
		int m_lastFrame;
	};

private:
	// Number of animation frames to show per second.
	const double m_kAnimationFrameRate;

	// Number of animation frames placed horizontally on the sprite sheet.
	int m_spriteSheetColumns;

	// Texture of full sprite sheet, for rendering.
	SDL_Texture* m_pSpriteSheetTexture;

	// Object position and dimensions.
	SDL_Rect m_transform;

	// Position and dimensions of the current frame of the sprite sheet.
	SDL_Rect m_currentFrameTransform;

	// Index of the current frame.
	int m_currentFrameNumber;

	// Time remaining until the animation should advance to the next frame.
	double m_nextFrameTime;

	// Current anmation sequence name.
	std::string m_currentSequenceName;

	// Map of this object's animation sequences.
	std::map<std::string, AnimationSequence> m_allAnimations;

public:
	AnimationComponent(const char* spriteSheetPath, double frameRate, SDL_Rect transform, int frameCount, SDL_Renderer* pRenderer);
	~AnimationComponent();

	// Adds a new animation sequence to this object.
	// If a sequence by this name exists, that data will be overwritten.
	void AddAnimationSequence(std::string name, int firstFrame, int lastFrame);

	// Plays the named animation sequence.
	void PlayAnimation(std::string sequenceName);

	// Updates the animation's frame.
	void Update(double deltaTime);

	// Renders the current frame of the animation.
	void Render(SDL_Renderer * pRenderer);

	// Sets x,y coordinates.
	void SetPosition(Vector2D newPosition);

	// Get Transform
	SDL_Rect GetTransform() const { return m_transform; }

private:
	// Resets time to next frame based on frame rate.
	void ResetFrameTime();

	// Updates the position of the source transform on the sprite sheet.
	void UpdateSourceTransform();
};

