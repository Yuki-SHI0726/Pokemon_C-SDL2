// StateLoadConstants.h
// Zixuan Shi
// State Load constants

#pragma once
#include "GameConstants.h"

// Game object position
const Vector2D kPlayerPosition = { 500,0 };

// Music

// Buttons//////////////////////////////////////////////////////////////
static const SDL_Color kButtonTextColor = { 225, 225, 225, 225 };
static constexpr int kButtonX = 330;
static constexpr int kButtonY = 150;
static constexpr int kButtonW = 150;
static constexpr int kButtonH = 50;
static constexpr const char* kDarkButtonPath = "assets/UI/SandstoneRoundButtonDark.png";
static constexpr const char* kLightButtonPath = "assets/UI/SandstoneRoundButtonBright.png";

// Save slot
static constexpr const char* kNoDataSaveSlotButtonPath = "assets/UI/SaveSlotButtonNoData.png";
static constexpr const char* kDarkSaveSlotButtonPath = "assets/UI/SaveSlotButtonDark.png";
static constexpr const char* kLightSaveSlotButtonPath = "assets/UI/SaveSlotButtonBright.png";
static constexpr int kSaveSlotButtonH = 80;

// Navigation
static constexpr const char* kMainMenuNavigationText = "Choose a button to press";
static const Vector2D kMainMenuNavigationPosition = { 400, 20 };

// Font
static constexpr int kTextFontSize = 40;
static constexpr int kSaveSlotFontSize = 15;
static constexpr int kTextXDiff = 30;
static constexpr int kTextYDiff = 20;
static constexpr const char* kTextFontPath = "assets/Font/YeonSung-Regular.ttf";

// Background Picture
static const SDL_Rect kBackgroundRectangle = { 0, 0, kWindowWidth, kWindowHeight };
static constexpr const char* kBackgroundFilePath = "assets/Background/StateLoadBackground.jpg";

// Title text
static constexpr const char* kTitle = "Save game slots";
static const SDL_Color kTitleColor = { 255, 255, 255, 200 };
static const Vector2D kTitlePosition = { 240, 100 };

// Load1 button 
static constexpr int kLoadOneButtonY = kButtonY + 0;
static const Vector2D kLoadOneTextPosition = { kButtonX + kTextXDiff, kLoadOneButtonY };
static const SDL_Rect kLoadOneButtonRectangle = { kButtonX , kLoadOneButtonY, kButtonW, kButtonH };

// Main Menu Button
static constexpr int kMenuButtonY = kButtonY + 300;
static constexpr const char* kMenuButtonText = "Menu";
static const Vector2D kMenuTextPosition = { kButtonX + kTextXDiff, kMenuButtonY };
static const SDL_Rect kMenuButtonRectangle = { kButtonX , kMenuButtonY, kButtonW, kButtonH };

// Sound Effect
static constexpr const char* kCharizardRoarSoundEffectFilePath = "assets/Music/CharizardRoar.wav";
static constexpr int kRoarVolume = 60;
static constexpr int kRoarIndex = 0;
static constexpr int kRoarLoop = 0;
