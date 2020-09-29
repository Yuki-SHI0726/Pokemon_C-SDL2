// StateGamePlayConstants.h
// Zixuan Shi
// State GamePlay constants

#pragma once
#include "GameConstants.h"
#include <SDL.h>

#include <vector>

// Game Object spawn position
const Vector2D kCharmanderPosition = { 480, 400 };
const Vector2D kPokeballPosition = { 300, 300 };
const Vector2D kPlayerPosition = { 380, 200 };

// Bushes
static Vector2D kBushPosition1  = { 50,140 };
static Vector2D kBushPosition2  = { 50,180 };
static Vector2D kBushPosition3  = { 50,220 };
static Vector2D kBushPosition4  = { 50,260 };
static Vector2D kBushPosition5  = { 50,300 };
static Vector2D kBushPosition6  = { 90,140 };
static Vector2D kBushPosition7  = { 90,180 };
static Vector2D kBushPosition8  = { 90,220 };
static Vector2D kBushPosition9  = { 90,260 };
static Vector2D kBushPosition10 = { 90,300 };
static Vector2D kBushPosition11 = { 130,140 };
static Vector2D kBushPosition12 = { 130,180 };
static Vector2D kBushPosition13 = { 130,220 };
static Vector2D kBushPosition14 = { 130,260 };
static Vector2D kBushPosition15 = { 130,300 };
static Vector2D kBushPosition16 = { 170,140 };
static Vector2D kBushPosition17 = { 170,180 };
static Vector2D kBushPosition18 = { 170,220 };
static Vector2D kBushPosition19 = { 170,260 };
static Vector2D kBushPosition20 = { 170,300 };
static Vector2D kBushPosition21 = { 210,140 };
static Vector2D kBushPosition22 = { 210,180 };
static Vector2D kBushPosition23 = { 210,220 };
static Vector2D kBushPosition24 = { 210,260 };
static Vector2D kBushPosition25 = { 210,300 };
std::vector<Vector2D> bushPositions{ kBushPosition1, kBushPosition2, kBushPosition3, kBushPosition4, kBushPosition5, kBushPosition6, kBushPosition7 ,kBushPosition8 ,kBushPosition9,kBushPosition10,kBushPosition11,kBushPosition12,kBushPosition13,kBushPosition14,kBushPosition15,kBushPosition16,kBushPosition17,kBushPosition18,kBushPosition19,kBushPosition20,kBushPosition21,kBushPosition22,kBushPosition23,kBushPosition24,kBushPosition25 };

// Background
static constexpr const char* kBackgroundFilePath = "assets/Background/GameplayBackground.jpg";
static const SDL_Rect kBackgroundRectangle = { 0, 0, kWindowWidth, kWindowHeight };

// Navigation
static constexpr const char* kGamePlayNavigationText = "Collect pokeball, then collides with bushes";
static const Vector2D kMainMenuNavigationPosition = { 400, 20 };

// Walls
// Edge walls
static constexpr int kEdgeWallCount = 4;
static const SDL_Rect kTopWallRectangle = { 0, -1, kWindowWidth, 1 };
static const SDL_Rect kLeftWallRectangle = { -1, 0, 1, kWindowHeight };
static const SDL_Rect kRightWallRectangle = { kWindowWidth, 0, 1, kWindowHeight };
static const SDL_Rect kBottomWallRectangle = { 0, kWindowHeight, kWindowWidth, 1 };

// UI Health Interface
const Vector2D kHealthInterfaceSpawnPosition = { 0,0 };

// Sound effects
static constexpr int kPlayerDeathSoundIndex = 1;
static constexpr int kPlayerDeathSoundLoop = 0;

// Particle
static const Vector2D kParticleSize = { 5, 5 };
static constexpr int kParticleCount = 20;
static constexpr float kMaxSpeed = 50;
static constexpr float kRadius = 300;
static const std::pair<float, float> xRange = { -1.0f, 1.0f };
static const std::pair<float, float> yRange = { -1.0f, 1.0f };

// Particle texture
static const SDL_Color kParticleColor = { 225, 125, 0, 225 };

