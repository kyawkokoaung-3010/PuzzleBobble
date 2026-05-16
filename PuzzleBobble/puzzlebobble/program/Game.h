#pragma once

#define SCREEN_W	650
#define SCREEN_H	480

#define MAX_STAGE 6
enum Stage
{
	stage0,
	stage1,
	stage2,
	stage3,
	stage4,
};

void PushBubbleToDown();
void GameInit();	//	‰Šú‰»ˆ—
void GameUpdate();	//	XVˆ—
void GameRender();	//	•`‰æˆ—
void GameExit();	//	I—¹ˆ—
