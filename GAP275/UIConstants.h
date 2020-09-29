// UIConstants.h
// Zixuan Shi
// UI Constants

#pragma once
#include <SDL.h>

// Health Interface
static constexpr const char* kInterfacePath = "assets/UI/HpInterface.png";
static constexpr const char* kTextFontPath = "assets/Font/arial.ttf";
static constexpr int kTextFontSize = 20;
static constexpr int kNamePositionDiffX = 20;
static constexpr int kNamePositionDiffY = 10;

// Health Current Bar
static const SDL_Color kHealthyHpColor = { 15,214,68,255 };
static const SDL_Color kHalfHpColor = { 237,229,2,255 };
static const SDL_Color kLowHpColor = { 237,0,0,255 };

static const SDL_Color kBaseColor = { 100,100,100,255 };

// HP bar Size
static constexpr int kHealthBarWidth = 141;
static constexpr int kHealthBarHeight = 11;
static constexpr int kHpBarXDiff = 114;
static constexpr int kHpBarYDiff = 49;

// Hp interface size
static constexpr int kInterfaceWidth = 267;
static constexpr int kInterfaceHeight = 97;

// hp bar hp text
static constexpr int kTotalHpPositionDiffX = 100;
static constexpr int kCurrentHpPositionDiffX = 80;
static constexpr int kHpPositionDiffY = 29;
