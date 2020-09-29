// AnimationComponent.cpp
// Zixuan Shi
// Animation component source

#include "AnimationComponent.h"
#include "SDL_image.h"
#include <assert.h>
#include <iostream>

////////////////////////////////////////////////////////////////////
// Constructor.
////////////////////////////////////////////////////////////////////
AnimationComponent::AnimationComponent(const char* spriteSheetPath, double frameRate, SDL_Rect transform, int frameCount, SDL_Renderer* pRenderer)
	: m_kAnimationFrameRate(frameRate)
	, m_currentFrameNumber(-1)
	, m_pSpriteSheetTexture(nullptr)
	, m_nextFrameTime{}
	, m_transform{ transform }
	, m_currentFrameTransform{}
{
	// Attempt to load the image and print an error if it fails.
	SDL_Surface* pImageSurface = IMG_Load(spriteSheetPath);
	if (pImageSurface == nullptr)
	{
		std::cout << "Failed to load image. Error: " << SDL_GetError() << std::endl;
		return;
	}

	// Calculate column count by dividing total width by frame width.
	m_spriteSheetColumns = pImageSurface->w / transform.w;

	// Simple error check to ensure the sprite sheet is big enough to hold the
	// designated number of frames.
	int rows = pImageSurface->h / transform.h;
	if (rows * m_spriteSheetColumns < frameCount)
	{
		std::cout << "Error: sprite sheet too small." << std::endl;
		SDL_FreeSurface(pImageSurface);
		return;
	}

	// Initializes the source rectangle. It will be centered over frame 0 initially.
	m_currentFrameTransform = m_transform;

	// Create the texture and free the image surface.
	m_pSpriteSheetTexture = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);
	SDL_FreeSurface(pImageSurface);
}

////////////////////////////////////////////////////////////////////
// Destructor.
////////////////////////////////////////////////////////////////////
AnimationComponent::~AnimationComponent()
{
	SDL_DestroyTexture(m_pSpriteSheetTexture);
}

////////////////////////////////////////////////////////////////////
// Adds a new animation sequence to this object.
// If a sequence by this name exists, that data will be overwritten.
////////////////////////////////////////////////////////////////////
void AnimationComponent::AddAnimationSequence(std::string name, int firstFrame, int lastFrame)
{
	m_allAnimations[name] = AnimationSequence{ name, firstFrame, lastFrame };
}

////////////////////////////////////////////////////////////////////
// Plays the named animation sequence.
////////////////////////////////////////////////////////////////////
void AnimationComponent::PlayAnimation(std::string sequenceName)
{
	// If the named sequence is already playing, or hasn't been added, do nothing.
	if (sequenceName == m_currentSequenceName ||
		m_allAnimations.find(sequenceName) == m_allAnimations.end())
	{
		return;
	}

	// Access the named sequence and set the current frame to its first frame.
	AnimationSequence& newSequence = m_allAnimations[sequenceName];
	m_currentFrameNumber = newSequence.m_firstFrame;

	// Update sequence name, frame time, and source rectangle.
	m_currentSequenceName = sequenceName;
	ResetFrameTime();
	UpdateSourceTransform();
}

////////////////////////////////////////////////////////////////////
// Updates the animation's frame.
////////////////////////////////////////////////////////////////////
void AnimationComponent::Update(double deltaTime)
{
	// If m_currentFrameNumber is -1, it means no animations have been played.
	if (m_currentFrameNumber == -1)
		return;

	// Access the current animation sequence from the map.
	AnimationSequence& currentSequence = m_allAnimations[m_currentSequenceName];

	// Allocate a dirty flag for whether the frame number has changed.
	bool frameIsDirty = false;

	// As long as deltaTime exceeds m_nextFrameTime, the entire current frame is consumed.
	// Using a loop here allows multiple frames to be skipped if deltaTime is large.
	while (deltaTime > m_nextFrameTime)
	{
		// The frame has changed.
		frameIsDirty = true;

		// Subtract frame time from deltaTime to continue the loop, then reset time.
		deltaTime -= m_nextFrameTime;
		ResetFrameTime();

		// Here we check whether we are now at the end of the current sequence.
		if (currentSequence.m_lastFrame == m_currentFrameNumber)
		{
			// If we are, we move to the beginning of the sequence to loop.
			m_currentFrameNumber = currentSequence.m_firstFrame;
		}
		// If not, we simply increment.
		else
		{
			++m_currentFrameNumber;
		}
	}

	// After accounting for frame changes, remember to subtract from m_nextFrameTime for
	// the next frame.
	m_nextFrameTime -= deltaTime;

	// Here we update the source transform ONLY if the frame changed.
	if (frameIsDirty)
	{
		UpdateSourceTransform();
	}
}

////////////////////////////////////////////////////////////////////
// Renders the current frame of the animation.
////////////////////////////////////////////////////////////////////
void AnimationComponent::Render(SDL_Renderer * pRenderer)
{
	SDL_RenderCopy(pRenderer, m_pSpriteSheetTexture, &m_currentFrameTransform, &m_transform);
}

////////////////////////////////////////////////////////////////////
// Sets x,y coordinates.
////////////////////////////////////////////////////////////////////
void AnimationComponent::SetPosition(Vector2D newPosition)
{
	m_transform.x = (int)newPosition.m_x;
	m_transform.y = (int)newPosition.m_y;
}

////////////////////////////////////////////////////////////////////
// Resets time to next frame based on frame rate.
////////////////////////////////////////////////////////////////////
void AnimationComponent::ResetFrameTime()
{
	// Divide 1 by framerate to get frame duration.
	m_nextFrameTime = 1. / m_kAnimationFrameRate;
}

////////////////////////////////////////////////////////////////////
// Updates the position of the source transform on the sprite sheet.
////////////////////////////////////////////////////////////////////
void AnimationComponent::UpdateSourceTransform()
{
	// Do a little math to get the right position.
	int frameX = m_currentFrameNumber % m_spriteSheetColumns;
	int frameY = m_currentFrameNumber / m_spriteSheetColumns;
	m_currentFrameTransform.x = frameX * m_currentFrameTransform.w;
	m_currentFrameTransform.y = frameY * m_currentFrameTransform.h;
}
