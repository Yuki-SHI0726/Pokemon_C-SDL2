// CharmanderConstants.h
// Zixuan Shi
// Charmander constants

#pragma once
#include "Vector2D.h"
#include <SDL.h>

extern const double __declspec(selectany)kCharmanderHp = 50;
static constexpr int kDamage = 10;
static constexpr double kCharmanderWidth = 43.2;
static constexpr double kCharmanderHeight = 39;

static constexpr int kMovingDistance = 30;
static constexpr float kMoveCD = 0.5f;

// Animation
static constexpr const char* kSpriteSheetPath = "assets/PokemonSprite/CharmenderSpriteSheet.png";
static constexpr int kCharmanderFrameRate = 6;
static constexpr int kCharmanderFrameCount = 5;

static constexpr const char* kIdleAnimation = "Idle";

// Sound Effect
static constexpr const char* kCharmanderRoarSoundEffectFilePath = "assets/Music/CharmanderRoar.wav";
static constexpr int kRoarVolume = 60;
static constexpr int kRoarIndex = 0;
static constexpr int kRoarLoop = 0;
