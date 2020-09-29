// StateCombatConstants.h
// Zixuan Shi
// Combat scene constants

#pragma once
#include "GameConstants.h"

// Game Objects position
const Vector2D kCharmanderPosition = { 580, 300 };
const Vector2D kCharizardPosition = { 500, 150 };
const Vector2D kPikachuPosition = { 180, 300 };

extern const double kCharmanderHp;

// Buttons//////////////////////////////////////////////////////////////
static const SDL_Color kButtonTextColor = { 225, 225, 225, 225 };
static constexpr int kButtonX = 130;
static constexpr int kButtonY = 500;
static constexpr int kButtonW = 180;
static constexpr int kButtonH = 50;
static constexpr const char* kDarkButtonPath = "assets/UI/SandstoneRoundButtonDark.png";
static constexpr const char* kLightButtonPath = "assets/UI/SandstoneRoundButtonBright.png";

// Navigation
static constexpr const char* kCombatNavigationText = "Choose a move to use";
static const Vector2D kCombatNavigationPosition = { 450, 20 };

// Font 
static constexpr int kTextFontSize = 30;
static constexpr const char* kTextFontPath = "assets/Font/arial.ttf";

// Background Picture
static const SDL_Rect kBackgroundRectangle = { 0, 0, kWindowWidth, kWindowHeight };
static constexpr const char* kBackgroundFilePath = "assets/Background/CombatBackground.png";

/*Pikachu Moves*//////////////////////////////////////////////////////////
// Thunder button
static constexpr int kThunderButtonY = kButtonY + 5;
static constexpr const char* kThunderButtonText = "Thunder";
static const Vector2D kThunderTextPosition = { kButtonX + 25, kThunderButtonY };
static const SDL_Rect kThunderButtonRectangle = { kButtonX , kThunderButtonY, kButtonW, kButtonH };

// Tail whip button
static constexpr int kTailwhipButtonY = kButtonY + 50;
static constexpr const char* kTailwhipButtonText = "Tail whip";
static const Vector2D kTailwhipTextPosition = { kButtonX, kTailwhipButtonY };
static const SDL_Rect kTailwhipButtonRectangle = { kButtonX , kTailwhipButtonY, kButtonW, kButtonH };

/*UI*//////////////////////////////////////////////////////////////////////
const Vector2D kEnemyHealthInterfaceSpawnPosition = { 0,0 };
const Vector2D kPikachuHealthInterfaceSpawnPosition = { 500,350 };

/*Sound Effect*//////////////////////////////////////////////////////////////
static constexpr int kCharmanderRoarIndex = 0;
static constexpr int kCharmanderRoarLoop = 0;

static constexpr int kDeathIndex = 1;
static constexpr int kDeathLoop = 0;

/*Particle*//////////////////////////////////////////////////////////////
// Charizard death
static const Vector2D kParticleSize = { 5, 5 };
static constexpr int kParticleCount = 500;
static constexpr float kMaxSpeed = 200;
static constexpr float kRadius = 30000;
static const std::pair<float, float> xRange = { -1.0f, 1.0f };
static const std::pair<float, float> yRange = { -2.0f, -0.5f };

// Particle texture
static const SDL_Color kParticleColor = { 255, 0, 0, 225 };

// attack Particle
static constexpr int kCount = 1;
static const Vector2D kSize = { 50, 50 };
static constexpr float kSpeed = 300;
static constexpr float kAttackRadius = 130000;

// Pikachu
static const std::pair<float, float> thunderXRange = { 1.0f, 1.0f };
static const std::pair<float, float> thunderYRange = { -0.4f, 0.0f };
static constexpr const char* kThunderTexturePath = "assets/GameObjects/Particle/ThunderParticle.png";

// Charmander
static const std::pair<float, float> fireXRange = { -1.0f, 0.0f };
static const std::pair<float, float> fireYRange = { 0.0f, 0.2f };
static const Vector2D kCharmanderAttackPosition = { 500, 250 };
static constexpr const char* kFireTexturePath = "assets/GameObjects/Particle/FireParticle.png";
