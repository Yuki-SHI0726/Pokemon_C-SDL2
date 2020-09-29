// CharizardConstants.h
// Zixuan Shi
// Charizard constants

#pragma once
#include "Vector2D.h" // #DG: looks like this isn't used. 
#include <SDL.h>


// #DG: You have the right idea with your constants files, but I think you're overusing them. 
// You can simplify the code a lot by sharing a lot of these constants. For example, since "Idle" and "Dead" are used in multiple places, they could be combined into a game constants file. 
// The rest of the constants unique to Charizard should be defined in the Charizard class
static constexpr double kCharizardHp = 150;
static constexpr int kCharizardAttack = 15;

static constexpr double kCharizardWidth = 250.0;
static constexpr double kCharizardHeight = 175;

// Animation
static constexpr const char* kSpriteSheetPath = "assets/PokemonSprite/CharizardSpriteSheet.png";
static constexpr int kCharizardFrameRate = 6;
static constexpr int kCharizardFrameCount = 9;

static constexpr const char* kIdleAnimation = "Idle";
static constexpr const char* kDeadAnimation = "Dead";

// Sound Effect
static constexpr const char* kCharizardRoarSoundEffectFilePath = "assets/Music/CharizardRoar.wav";
static constexpr int kRoarVolume = 60;
static constexpr int kRoarIndex = 0;
static constexpr int kRoarLoop = 0;

static constexpr const char* kCharizardDeathSoundEffectFilePath = "assets/Music/DeathSoundEffect.wav";
static constexpr int kDeathVolume = 300;
static constexpr int kDeathIndex = 1;
static constexpr int kDeathLoop = 0;