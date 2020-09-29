// StateLossConstants.h
// Zixuan Shi
// State Loss constants

#pragma once
#include "GameConstants.h"

// Font
static constexpr int kTextFontSize = 40;
static constexpr int kTitleFontSize = 50;
static constexpr const char* kTextFontPath = "assets/Font/YeonSung-Regular.ttf";
static constexpr const char* kTitleFontPath = "assets/Font/Rye-Regular.ttf";

// Background Picture
static const SDL_Rect kBackgroundRectangle = { 0, 0, kWindowWidth, kWindowHeight };
static constexpr const char* kBackgroundFilePath = "assets/Background/LossBackground.png";

// Title text
static constexpr const char* kTitle = "You Lost";
static const SDL_Color kTitleColor = { 200,100,100,200 };
static const Vector2D kTitlePosition = { 300, 100 };

// Navigation
static constexpr const char* kLossNavigationText = "Choose a button to press";
static const Vector2D kLossNavigationPosition = { 400, 20 };

// Buttons//////////////////////////////////////////////////////////////
static const SDL_Color kButtonTextColor = { 225, 225, 225, 225 };
static constexpr int kButtonX = 330;
static constexpr int kButtonY = 200;
static constexpr int kButtonW = 150;
static constexpr int kButtonH = 50;
static constexpr const char* kDarkButtonPath = "assets/UI/SandstoneRoundButtonDark.png";
static constexpr const char* kLightButtonPath = "assets/UI/SandstoneRoundButtonBright.png";

// Replay button 
static constexpr int kReplayButtonY = kButtonY + 0;
static constexpr const char* kReplayButtonText = "Replay";
static const Vector2D kReplayTextPosition = { kButtonX + 20, kReplayButtonY };
static const SDL_Rect kReplayButtonRectangle = { kButtonX , kReplayButtonY, kButtonW, kButtonH };

// Main Menu Button
static constexpr int kMainMenuButtonY = kButtonY + 100;
static constexpr const char* kMainMenuButtonText = "Menu";
static const Vector2D kMainMenuTextPosition = { kButtonX + 30, kMainMenuButtonY };
static const SDL_Rect kMainMenuButtonRectangle = { kButtonX , kMainMenuButtonY, kButtonW, kButtonH };

// Credits Button
static constexpr int kCreditsButtonY = kButtonY + 200;
static constexpr const char* kCreditsButtonText = "Credits";
static const Vector2D kCreditsTextPosition = { kButtonX + 20, kCreditsButtonY };
static const SDL_Rect kCreditsButtonRectangle = { kButtonX , kCreditsButtonY, kButtonW, kButtonH };

// Quit Button
static constexpr int kQuitButtonY = kButtonY + 300;
static constexpr const char* kQuitButtonText = "Quit";
static const Vector2D kQuitTextPosition = { kButtonX + 40, kQuitButtonY };
static const SDL_Rect kQuitButtonRectangle = { kButtonX , kQuitButtonY, kButtonW, kButtonH };

// Check Win Button
static constexpr int kCheckWinButtonY = kButtonY;
static constexpr const char* kCheckWinText = "CheckWin";
static const Vector2D kCheckWinTextPosition = { kButtonX - 200, kCheckWinButtonY };
static const SDL_Rect kCheckWinButtonRectangle = { kButtonX - 200 , kCheckWinButtonY, kButtonW + 20, kButtonH };
