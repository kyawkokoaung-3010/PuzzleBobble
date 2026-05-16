#ifndef GAMEMECHANIC_H
#define GAMEMECHANIC_H

#include "board.h"
#define MAX_FALLINGBUBBLE 100

// Logic functions
int IsBubbleSameColor(int r, int c, int color);
void RemovedConnectedBubble();
void IsConnectedAbove(int r, int c);
void DropBubble();
void ConnectBubble(float x, float y, int color, int& outR, int& outC);

void AddFallingBubble(float x, float y, int color);
void PushBubbleToDown();
bool GameOver();
int MaxBubbleColors(int stageNum);

// Shared variables that Game.cpp needs to see
extern bool placed[ROWS][COLS];
extern bool connected[ROWS][COLS];

#endif