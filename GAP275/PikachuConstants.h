// PikachuConstants.h
// Zixuan Shi
// Pikachu constants

#pragma once
#include "Vector2D.h"
#include <SDL.h>

static constexpr int kPikachuHp = 200;
static constexpr int kPikachuAttack = 10;

static constexpr double kPikachuWidth = 100;
static constexpr double kPikachuHeight = 134;

// Animation
static constexpr const char* kPikachuSpriteSheetPath = "assets/PokemonSprite/CombatPikachuFromBack.png";
static constexpr int kPikachuFrameRate = 1;
static constexpr int kPikachuFrameCount = 1;

static constexpr const char* kIdleAnimation = "Idle";

// Sound Effect
static constexpr const char* kPikachuRoarSoundEffectFilePath = "assets/Music/PikachuSoundEffect.wav";
static constexpr const char* kPikachuThunderCriticalStrikeSoundEffectFilePath = "assets/Music/PikachuThunderCriticalStrikeSoundEffect.wav";
static constexpr const char* kPikachuThunderSoundEffectFilePath = "assets/Music/Laser.wav";
static constexpr int kRoarVolume = 80;
static constexpr int kRoarIndex = 0;
static constexpr int kRoarLoop = 0;
static constexpr int kThunderIndex = 1;
static constexpr int kThunderLoop = 0;
static constexpr int kLaserIndex = 2;
static constexpr int kLaserLoop = 0;

// Moves
static constexpr double kThunderDamage = 5;
static constexpr int kTailWhipDamage = 10;
static constexpr int kCriticalStrikeChance = 2;
