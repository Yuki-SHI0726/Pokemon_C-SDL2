// StateTitleScreenConstants.h
// Zixuan Shi
// State TitleScreen constants

#pragma once

#include "GameConstants.h"

// Music
//static constexpr const char* kMusicPath = "assets/Music/TitleScreenMusic.mp3";

// Font
static constexpr int kTextFontSize = 40;
static constexpr const char* kTextFontPath = "assets/Font/Rye-Regular.ttf";

// Background Picture
static const SDL_Rect kBackgroundRectangle = { 0, 0, kWindowWidth, kWindowHeight };
static constexpr const char* kBackgroundFilePath = "assets/Background/TitleScreenBackground.jpg";

// Title text
static constexpr const char* kTitle = "Press any key to continue";
static const SDL_Color kTitleColor = { 15,15,15,255 };
static const Vector2D kTitlePosition = { 180, 280 };
