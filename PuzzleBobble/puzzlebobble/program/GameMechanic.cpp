#include "GameMechanic.h"
#include "Main.h"
#include "Random.h"
#include "board.h"
#include "Bubble.h"

extern Board board; // Reference the board from Game.cpp

bool placed[ROWS][COLS];
bool connected[ROWS][COLS];

int drop_count; //how many bubbles droppeds
extern int score;
extern bool stageCleared;

FallingBubble falling_bubble[MAX_FALLINGBUBBLE];
//extern FallingBubble fallingBubble[];

//====================Hex Directions
int evenDir[6][2] =
{
    {-1, -1},{-1, 0},
    {0, -1}, {0, 1},
    {1, -1}, {1, 0}
};
int oddDir[6][2] =
{
    {-1, 0},{-1, 1},
    {0, -1}, {0, 1},
    {1, 0}, {1, 1}
};

int IsBubbleSameColor(int r, int c, int color)
{
    if (r < 0 || r >= ROWS) { return 0; }
    if (c < 0 || c >= board.GetTotalCol(r)) { return 0; }

    if (placed[r][c]) { return 0; }
    if (board.grid[r][c] != color) { return 0; }
    placed[r][c] = true;

    int count = 1;//bubble count
    int(*dir)[2];

    if (r % 2 == 0) { dir = evenDir; }
    else {
        dir = oddDir;
    }

    for (int i = 0; i < 6; i++)
    {
        int nr = r + dir[i][0];
        int nc = c + dir[i][1];

        count += IsBubbleSameColor(nr, nc, color);
    }
    return count;
}

void RemovedConnectedBubble()
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < board.GetTotalCol(r); c++)
        {
            if (placed[r][c])
            {
                board.grid[r][c] = 0;

                drop_count++;
                score += drop_count * 20;
            }
        }
    }
}
//====================check if bubbles are connected to above====================
void IsConnectedAbove(int r, int c)
{
    if (r < 0 || r >= ROWS) { return; }
    if (c < 0 || c >= board.GetTotalCol(r)) { return; }

    if (connected[r][c]) { return; }
    if (board.grid[r][c] == 0) { return; }

    connected[r][c] = true;
    int(*dir)[2];

    if (r % 2 == 0) { dir = evenDir; }
    else {
        dir = oddDir;
    }
    for (int i = 0; i < 6; i++)
    {
        int nr = r + dir[i][0];
        int nc = c + dir[i][1];

        IsConnectedAbove(nr, nc);
    }
}
//====================drop bubbles if matched====================
void DropBubble()
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < board.GetTotalCol(r); c++)
        {
            connected[r][c] = false;
        }
    }
    for (int c = 0; c < board.GetTotalCol(0); c++)
    {
        if (board.grid[0][c] != 0)
        {
            IsConnectedAbove(0, c);
        }
    }
    
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < board.GetTotalCol(r); c++)
        {
            if (board.grid[r][c] != 0 && !connected[r][c])
            {
                Float2 p = board.GetPos(r, c);

                AddFallingBubble(
                    p.x,
                    p.y,
                    board.grid[r][c]);

                board.grid[r][c] = 0;
            }
        }
    }
}

//====================connect shotBubble To Nearest Empty Grid====================
void ConnectBubble(float x, float y, int color, int& outR, int& outC)
{
    int nearRow = 0;
    int nearCol = 0;

    float nearestDist = 999999.0f;

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < board.GetTotalCol(r); c++)
        {
            // only empty cells
            if (board.grid[r][c] != 0) continue;

            Float2 p = board.GetPos(r, c);

            float dx = x - p.x;
            float dy = y - p.y;

            float dist = dx * dx + dy * dy;

            if (dist < nearestDist)
            {
                nearestDist = dist;

                nearRow = r;
                nearCol = c;
            }
        }
    }
    board.grid[nearRow][nearCol] = color;//bubble's color on board
    outR = nearRow;
    outC = nearCol;
}
//====================push bubbles every 6 shots====================
void PushBubbleToDown()
{
    board.dropY += 32.0f;/*
    if (stageCleared)
    {
        board.dropY = 0;
    }*/
}

void AddFallingBubble(float x, float y, int color)
{
    for (int i = 0; i < MAX_FALLINGBUBBLE; i++)
    {
        if (!falling_bubble[i].active)
        {
            falling_bubble[i].Init(x, y, color);
            break;
        }
    }
}

bool GameOver()
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < board.GetTotalCol(r); c++)
        {
            if (board.grid[r][c] == 0)continue;

            Float2 p = board.GetPos(r, c);

            if (p.y + BUBBLE_R >= SCREEN_H - 90)
            {
                return true;
            }
        }
    }
    return false;
}
int MaxBubbleColors(int stageNum)
{
    if (stageNum == 0 || stageNum == 1)return  4;
    //if (stageNum == 2)return 6;
    return 6;

}