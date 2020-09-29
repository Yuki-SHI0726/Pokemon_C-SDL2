// StateMainMenuConstants.h
// Zixuan Shi
// State MainMenu constants

#pragma once
#include "GameConstants.h"

// Game object position
static const Vector2D kCharizardPosition = { 580, 400 };

// Music
static constexpr const char* kMusicPath = "assets/Music/MainMenuMusic.mp3";

// Buttons//////////////////////////////////////////////////////////////
static const SDL_Color kButtonTextColor = { 225, 225, 225, 225 };
static constexpr int kButtonX = 330;
static constexpr int kButtonY = 200;
static constexpr int kButtonW = 150;
static constexpr int kButtonH = 50;
static constexpr const char* kDarkButtonPath = "assets/UI/SandstoneRoundButtonDark.png";
static constexpr const char* kLightButtonPath = "assets/UI/SandstoneRoundButtonBright.png";

// Navigation
static constexpr const char* kMainMenuNavigationText = "Choose a button to press";
static const Vector2D kMainMenuNavigationPosition = { 400, 20 };

// Font
static constexpr int kTextFontSize = 40;
static constexpr const char* kTextFontPath = "assets/Font/YeonSung-Regular.ttf";

// Background Picture
static const SDL_Rect kBackgroundRectangle = { 0, 0, kWindowWidth, kWindowHeight };
static constexpr const char* kBackgroundFilePath = "assets/Background/MainMenuBackground.jpg";

// Title text
static constexpr const char* kTitle = "Yuki's Pokemon Game";
static const SDL_Color kTitleColor = { 255, 255, 255, 200 };
static const Vector2D kTitlePosition = { 220, 100 };

// Play button 
static constexpr int kPlayButtonY = kButtonY + 0;
static constexpr const char* kPlayButtonText = "Start";
static const Vector2D kPlayTextPosition = { kButtonX + 30, kPlayButtonY };
static const SDL_Rect kPlayButtonRectangle = { kButtonX , kPlayButtonY, kButtonW, kButtonH };

// Credits Button
static constexpr int kCreditsButtonY = kButtonY + 100;
static constexpr const char* kCreditsButtonText = "Credits";
static const Vector2D kCreditsTextPosition = { kButtonX + 20, kCreditsButtonY };
static const SDL_Rect kCreditsButtonRectangle = { kButtonX , kCreditsButtonY, kButtonW, kButtonH };

// Load Button
static constexpr int kLoadButtonY = kButtonY + 200;
static constexpr const char* kLoadButtonText = "Load";
static const Vector2D kLoadTextPosition = { kButtonX + 40, kLoadButtonY };
static const SDL_Rect kLoadButtonRectangle = { kButtonX , kLoadButtonY, kButtonW, kButtonH };

// Quit Button
static constexpr int kQuitButtonY = kButtonY + 300;
static constexpr const char* kQuitButtonText = "Quit";
static const Vector2D kQuitTextPosition = { kButtonX + 40, kQuitButtonY };
static const SDL_Rect kQuitButtonRectangle = { kButtonX , kQuitButtonY, kButtonW, kButtonH };

// Sound Effect
static constexpr const char* kCharizardRoarSoundEffectFilePath = "assets/Music/CharizardRoar.wav";
static constexpr int kRoarVolume = 60;
static constexpr int kRoarIndex = 0;
static constexpr int kRoarLoop = 0;

// Particle
static const Vector2D kParticleSize = { 20, 20 };
static constexpr int kParticleCount = 50;
static constexpr float kMaxSpeed = 250;
static constexpr float kMinSpeed = 50;
static constexpr double kTransformSecond = 3.0;
static constexpr float kRadius = 30000;
static constexpr double kParticleDuration = 20;

// Right particle
static const Vector2D kRightParticlePosition = { 600, 300 };
static const std::pair<float, float> rightXRange = { 0.5f, 1.0f };
static const std::pair<float, float> rightYRange = { -0.3f, 0.3f };
static constexpr const char* kRightParticleTexturePath = "assets/GameObjects/Particle/FireParticle.png";

// Left particle
static const Vector2D kLeftParticlePosition = { 200, 300 };
static const std::pair<float, float> leftXRange = { -0.5f, 0.0f };
static const std::pair<float, float> leftYRange = { -0.3f, 0.3f };
static constexpr const char* kLeftParticleTexturePath = "assets/GameObjects/Particle/ThunderParticle.png";

// Particle texture
static const Uint8 kAlphaTexture = 150;


