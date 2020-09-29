// GameConstant.h
// Zixuan Shi
// Store static constexprs for game

#pragma once
#include <SDL.h>
#include "Vector2D.h"

// SDL window size
static constexpr int kWindowWidth = 800;
static constexpr int kWindowHeight = 600;
static constexpr int kFrameRate = 60;

// Return value
static constexpr int kErrorCode = -1;
static constexpr int kGoodCode = 0;

// quit
static constexpr char kQuit = '1';
static constexpr char kContinue = '2';

// Navigation
static constexpr const char* kNavigationTitle = "Navigation: ";
static constexpr const char* kNavigationFontPath = "assets/Font/arial.ttf";
static constexpr int kNavigationFontSize = 20;
const SDL_Color kNavigationColor = { 100,100,100,255 };
const Vector2D kNavigationPosition = { 300, 20 };

// Music
static constexpr const char* kMusicAPath = "assets/Music/BackgroundMusicB.mp3";
static constexpr const char* kMusicBPath = "assets/Music/CombatMusic.mp3";

// Save and load
static constexpr int kMaxSaveSlotCount = 3;

