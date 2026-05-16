#include "DxLib.h"
#include "board.h"
#include "Bubble.h"
#include <math.h>
#include "Random.h"

extern Board board;
int bubble_img[TOTAL_COLOR];

void LoadBubblesImage()
{
	bubble_img[1] = LoadGraph("data/red.png");
	bubble_img[2] = LoadGraph("data/blue.png");
	bubble_img[3] = LoadGraph("data/green.png");
	bubble_img[4] = LoadGraph("data/yellow.png");
	bubble_img[5] = LoadGraph("data/black.png");
	bubble_img[6] = LoadGraph("data/silver.png");
	bubble_img[7] = LoadGraph("data/purple.png");
	bubble_img[8] = LoadGraph("data/orange.png");
}

Bubble::Bubble()
{
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;

	color = 1;
	active = false;

	hit = false;
}

void Bubble::Set(float px, float py, int c)
{
	x = px;
	y = py;
	vx = 0;
	vy = 0;

	color = c; 
	active = false;
}

void Bubble::Shoot(float angle)
{
	float speed = 12.0f;

	vx = cosf(angle) * speed;
	vy = sinf(angle) * speed;

	active = true;
}

//void Bubble::Update()
//{
//	if (!active) return;
//
//	x += vx;
//	y += vy;
//
//	if (x <= BOARD_X + BUBBLE_R)
//	{
//		x = BOARD_X + BUBBLE_R;
//		vx = 3.14159f - vx;
//	}
//	if (x >= BOARD_X + BOARD_W - BUBBLE_R)
//	{
//		x = BOARD_X + BOARD_W - BUBBLE_R;
//		vx = 3.14159f - vx;
//
//	}
//	if (y <= BOARD_Y + BUBBLE_R)
//	{
//		active = false;
//	}
//}

void Bubble::Update()
{
	if (!active) return;

	x += vx;
	y += vy;

	// Left wall
	if (x <= BOARD_X + BUBBLE_R)
	{
		x = BOARD_X + BUBBLE_R;
		vx *= -1;
	}

	// Right wall
	if (x >= BOARD_X + BOARD_W - BUBBLE_R)
	{
		x = BOARD_X + BOARD_W - BUBBLE_R;
		vx *= -1;
	}
	
	// Ceiling
	if (y <= BOARD_Y + BUBBLE_R + board.dropY)
	{
		y = BOARD_Y + BUBBLE_R;
		active = false;
	}
}

void Bubble::Render()
{
	//printfDx("color = %d\n", color);

	DrawGraph((int)x - 16, (int)y - 15, bubble_img[color], TRUE);
}

FallingBubble::FallingBubble()
{
	x = 0;
	y = 0;

	vy = 0;

	color = 1;

	active = false;
}

void FallingBubble::Init(float px, float py, int c)
{
	x = px;
	y = py;

	vy = 2.0f;

	color = c;

	active = true;
}

void FallingBubble::Update()
{
	if (!active)
		return;

	y += vy;

	vy += 0.5f;

	if (y > SCREEN_H + 50)
	{
		active = false;
	}
}

void FallingBubble::Render()
{
	if (!active) return;
	DrawGraph( (int)x - 16, (int)y - 16, bubble_img[color], TRUE);
}