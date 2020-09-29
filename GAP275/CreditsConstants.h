// CreditsConstants.h
// Zixuan Shi
// Credits scene constants

#pragma once
#pragma once
#include "Vector2D.h"
#include <SDL.h>

// Font
static constexpr int kCreditsFontSize = 30;
static constexpr const char* kTextFontPath = "assets/Font/arial.ttf";
static const SDL_Color kTextColor = { 255, 255, 255, 200 };

// Background Picture
static const SDL_Rect kBackgroundRectangle = { 0, 0, 800, 600 };
static constexpr const char* kBackgroundFilePath = "assets/Background/CreditsBackground.jpg";

// Credits title
static constexpr const char* kCredits = "Made by: ";
static const Vector2D kCreditsPosition = { 50, 100 };

// Information
static constexpr const char* kDeveloperName = "Zixuan Shi (Yuki)";
static const Vector2D kDeveloperPosition = { 50, 200 };

static constexpr const char* kEmail = "Email: szx0726@gmail.com";
static const Vector2D kEmailPosition = { 50, 250 };

static constexpr const char* kPhone = "Phone: 415-503-7615";
static const Vector2D kPhonePosition = { 50, 300 };

static constexpr const char* kSpriteCredits = "Sprite Sheets: JoshR691";
static const Vector2D kSpriteSheetCreditsPosition = { 50, 350 };

// Buttons//////////////////////////////////////////////////////////////
static const SDL_Color kButtonTextColor = { 225, 225, 225, 225 };
static constexpr int kButtonX = 50;
static constexpr int kButtonY = 200;
static constexpr const char* kDarkButtonPath = "assets/UI/SandstoneRoundButtonDark.png";
static constexpr const char* kLightButtonPath = "assets/UI/SandstoneRoundButtonBright.png";

// Quit Button
static constexpr int kQuitButtonY = kButtonY + 200;
static constexpr const char* kQuitButtonText = "Menu";
static const Vector2D kQuitTextPosition = { kButtonX + 20, kQuitButtonY };
static const SDL_Rect kQuitButtonRectangle = { kButtonX , kQuitButtonY, 120, 50 };

// Sound Effect
static constexpr const char* kSnorlaxRoarSoundEffectFilePath = "assets/Music/SnorlaxRoar.wav";
static constexpr int kRoarVolume = 140;
static constexpr int kRoarIndex = 0;
static constexpr int kRoarLoop = 0;
