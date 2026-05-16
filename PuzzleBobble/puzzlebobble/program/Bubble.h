#ifndef BUBBLE_H
#define BUBBLE_H

#define TOTAL_COLOR 9

extern int bubble_img[TOTAL_COLOR];

void LoadBubblesImage();

class Bubble
{
public:
	float x, y;
	float vx, vy;
	bool active;
	int color;
	bool hit;

	Bubble();

	void Set(float px, float py, int c);
	void Shoot(float angle);
	void Update();
	void Render();
};

void LoadBubblesImage();

class FallingBubble
{
public:
	float x, y;
	float vy;

	int color;

	bool active;

	FallingBubble();

	void Init(float px, float py, int c);

	void Update();

	void Render();
};

#endif