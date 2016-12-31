#pragma once

#include "timer.h"

#include <cstddef>

const int kFPS = 60;
const double kFrameDelay(double(1000000.0) / double(kFPS));
const int kGameTime = 60;
const int kFontSize = 25;
const int kSpriteWidth = 38;
const int kSpriteHeight = 38;
const size_t kNumSprites = 5; // Red, Blue, Green, Yellow and Purple
const size_t kMatchNumber = 3;
const int kRows = 9;
const int kCols = 8;
const int kIdleTimer = 5;
const size_t kBoardStartX = 340;
const size_t kBoardEndX = kBoardStartX + (kCols * kSpriteWidth);
const size_t kBoardStartY = 95;
const size_t kBoardEndY = kBoardStartY + (kRows * kSpriteHeight);
