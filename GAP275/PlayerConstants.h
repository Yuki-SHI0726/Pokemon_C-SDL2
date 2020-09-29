// PlayerConstants.h
// Zixuan Shi
// Player's constants

#pragma once

#include "GameConstants.h"

static constexpr double kPlayerWidth = 48.0;
static constexpr double kPlayerHeight = 58.0;
static constexpr double kPlayerSpeed = 150;
static constexpr double kPlayerHp = 100;

// Animation
static constexpr const char* kPlayerSpriteSheetPath = "assets/Player/PlayerWalkSpriteSheet.png";
static constexpr int kPlayerFrameRate = 8;
static constexpr int kPlayerFrameCount = 12;

static const std::string kFacingDownIdleAnimation = "facingDownIdle";
static const std::string kFacingDownRunAnimation = "facingDownRun";

static const std::string kFacingUpIdleAnimation = "facingUpIdle";
static const std::string kFacingUpRunAnimation = "facingUpRun";

static const std::string kFacingRightIdleAnimation = "facingRightIdle";
static const std::string kFacingRightRunAnimation = "facingRightRun";

static const std::string kFacingLeftIdleAnimation = "facingLeftIdle";
static const std::string kFacingLeftRunAnimation = "facingLeftRun";

// Sound Effect
static constexpr const char* kPlayerInitiationSoundEffectFilePath = "assets/Music/Demacia.wav";
static constexpr int kInitiationVolume = 100;
static constexpr int kInitiationIndex = 0;
static constexpr int kInitiationLoop = 0;

static constexpr const char* kPlayerDeathSoundEffectFilePath = "assets/Music/PlayerDeathSoundEffect.wav";
static constexpr int kDeathVolume = 140;
static constexpr int kDeathIndex = 1;
static constexpr int kDeathLoop = 0;
