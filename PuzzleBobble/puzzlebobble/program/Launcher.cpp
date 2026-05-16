#include "Launcher.h"
#include "DxLib.h"
#include "Game.h"
#include "Main.h"

void Launcher::Init()
{
	x = 0;
	y = 0;
	img_x = 0;
	img_y = 0;
	launcher_img = LoadGraph("data/launcher3.png");// load launcher image
	//animTimer = 0;
	active = true;
}

void Launcher::Set(float px, float py)
{
	x = px;
	y = py;
}

void Launcher::Update()
{
	if (active) {
		/*if (CheckHitKey(KEY_INPUT_LEFT)) { img_x += 84; }
		if (CheckHitKey(KEY_INPUT_RIGHT)){ img_x -= 84; }
		if (img_x < 0)img_x = 672;
		if (img_x > 672)img_x = 0;*/
		if (CheckHitKey(KEY_INPUT_LEFT)) { img_x += 119; }
		if (CheckHitKey(KEY_INPUT_RIGHT)) { img_x -= 119; }
		if (img_x < 0)img_x = 1309;
		if (img_x > 1309)img_x = 0;
	}
}
void Launcher::Render()
{
	if (active)
	{
		//DrawRectGraph(x - 45, y - 26, img_x, img_y, 84, 44, launcher_img, TRUE);
		DrawRectGraph(x - 74, y - 64, img_x, img_y, 119, 85, launcher_img, TRUE);
	}
}

void Arrow::Init()
{
	x = 0;
	y = 0;
	rot = -1.57f;
	active = true;
	arrow_img = LoadGraph("data/arrow.png");
}
void Arrow::Set(float px, float py)
{
	x = px;
	y = py;
}
void Arrow::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT)) { rot -= ARROW_ROT_SPEED; }
	if (CheckHitKey(KEY_INPUT_RIGHT)) {rot += ARROW_ROT_SPEED; }
	if (rot < -80.0f)rot = -80.0f;
	if (rot > 80.0f) rot = 80.0f;
}
void Arrow::Render()
{
	//printfDx("rot = %f\n", rot);
	DrawRotaGraph(x, y, 1.0f, TO_RADIAN(rot), arrow_img, TRUE);
}

void Handle::Init()
{
	x = 0;
	y = 0;
	rot = -1.57f;
	active = true;
	handle_img = LoadGraph("data/handle.png");
}
void Handle::Set(float px, float py)
{
	x = px;
	y = py;
}
void Handle::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_RIGHT)) 
	{
		y = y + 5.0f;
	}
	/*if (rot < -80.0f)rot = -80.0f;
	if (rot > 80.0f) rot = 80.0f;*/
}
void Handle::Render()
{
	//printfDx("rot = %f\n", rot);
	DrawRotaGraph(x, y, 1.0f, TO_RADIAN(rot), handle_img, TRUE);
}

void Turning::Init()
{
	x = 0;
	y = 0;

	img_x = 0;
	img_y = 0;
	animTimer = 0;
	active = true;
	turning_img = LoadGraph("data/turning2.png");
	standing_img = LoadGraph("data/standing2.png");
}
void Turning::Set(float px, float py)
{
	x = px;
	y = py;
}
void Turning::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT)) 
	{ 
		active = true;
		animTimer++;
		if (animTimer % 5 == 0)
		{
			img_x -= 48;
		}
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT)) 
	{
		active = true;
		animTimer++;
		if (animTimer % 5 == 0)
		{
			img_x += 48;
		}
	}
	else
	{
		active = false;
	}
	if (img_x < 0)img_x = 336;
	if (img_x > 336)img_x = 0;
}
void Turning::Render()
{
	if(active)
	DrawRectGraph(x, y, img_x, img_y, 48, 41, turning_img, TRUE);
	else
	{
		DrawRectGraph(x, y, 0, 0, 48, 41, standing_img, TRUE);
	}

}