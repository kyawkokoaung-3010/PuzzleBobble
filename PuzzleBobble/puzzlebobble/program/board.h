#ifndef BOARD_H
#define BOARD_H

#include "Float2.h"
#include "basedata.h"
#include "Game.h"

const int ROWS = 12;
const int COLS = 8;
const float BUBBLE_R = 16.0f;
const float BUBBLE_D = BUBBLE_R * 2.0f;

const float BOARD_W = COLS * BUBBLE_D;

const float BOARD_X = (SCREEN_W - BOARD_W) / 2.0f;
const float BOARD_Y = 50.0f;

class Board {
    public:
        float dropY = 0.0f;

        Board() {
            for (int y = 0; y < ROWS; y++)
                for (int x = 0; x < COLS; x++)
                    grid[y][x] = 0;
        }
        // Convert Grid index to Screen Position
        Float2 GetPos(int r, int c) {
            float offset = (r % 2 != 0) ? BUBBLE_R : 0.0f;
            
            pos.x = BOARD_X + (c * BUBBLE_D) + BUBBLE_R + offset; // 160 is side margin
            pos.y = BOARD_Y + dropY + (r * (BUBBLE_D * 0.866f)) + BUBBLE_R; // 0.866 makes them nestle
            return pos;
        }

        int GetTotalCol(int row)//even row
        {
            if (row % 2 == 1)return COLS - 1;
            return COLS;
        }
        
        Float2 pos;
        int grid[ROWS][COLS];
};

#endif