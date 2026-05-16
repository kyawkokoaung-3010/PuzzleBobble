#ifndef LAUNCHER_H
#define LAUNCHER_H
#define ARROW_ROT_SPEED 2.3f

class Launcher
{
public:
	float x, y;
	float img_x, img_y;
	bool active;
	//int animTimer;
	/*bool hit;*/
	int launcher_img;

	void Init();

	void Set(float px, float py);
	void Update();
	void Render();
};

void LoadBubblesImage();

class Arrow
{
public:
	float x, y;
	float rot;
	bool active;
	int arrow_img;

	void Init();
	void Set(float px, float py);
	void Update();
	void Render();
};

class Handle
{
public:
	float x, y;
	float rot;
	bool active;
	int handle_img;

	void Init();
	void Set(float px, float py);
	void Update();
	void Render();
};

class Turning
{
public:
	float x, y;
	float img_x, img_y;
	bool active;
	int turning_img;
	int standing_img;
	int animTimer;

	void Init();
	void Set(float px, float py);
	void Update();
	void Render();
};
#endif