#include "Stage.h"

void LoadStage(Board& board, int stageNo)
{
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			board.grid[r][c] = 0;
		}
	}
	if (stageNo == 0)
	{
		int stage0[ROWS][COLS]
			= {
				{ 0, 0, 0, 4, 4, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 3, 3, 0, 0, 0 },
				{ 0, 0, 0, 2, 2, 0, 0, 0 },
		};
		for (int r = 0; r < 4; r++)
		{
			for (int c = 0; c < COLS; c++)
			{
				board.grid[r][c] = stage0[r][c];
			}
		}
	}
	if (stageNo == 1)
	{
		int stage1[ROWS][COLS]
		={
			{ 1, 1, 4, 4, 2, 2, 3, 3 },
			{ 1, 1, 4, 4, 2, 2, 3, 0 },
			{ 2, 2, 3, 3, 1, 1, 4, 4 },
			{ 2, 3, 3, 1, 1, 4, 4, 0 },
		};
		for (int r = 0; r < 4; r++)
		{
			for (int c = 0; c < COLS; c++)
			{
				board.grid[r][c] = stage1[r][c];
			}
		}
	}
	if (stageNo == 2)
	{
		int stage2[ROWS][COLS]
		= {
			{ 0, 0, 0, 5, 5, 0, 0, 0 },
			{ 0, 0, 0, 7, 0, 0, 0, 0 },
			{ 0, 0, 0, 6, 0, 0, 0, 0 },
			{ 0, 0, 0, 2, 0, 0, 0, 0 },
			{ 0, 0, 0, 3, 0, 0, 0, 0 },
			{ 0, 0, 0, 3, 0, 0, 0, 0 },
			{ 0, 0, 0, 6, 0, 0, 0, 0 },
			{ 0, 0, 0, 7, 0, 0, 0, 0 },

		};
		for (int r = 0; r < ROWS; r++)
		{
			for (int c = 0; c < COLS; c++)
			{
				board.grid[r][c] = stage2[r][c];
			}
		}
	}
	if (stageNo == 3)
	{
		int stage3[ROWS][COLS]
		={
			{ 3, 0, 0, 0, 0, 0, 0, 3 },
			{ 1, 3, 2, 4, 1, 3, 2, 0 },
			{ 4, 0, 0, 0, 0, 0, 0, 4 },
			{ 2, 4, 1, 3, 2, 4, 1, 0 },
			{ 0, 0, 0, 1, 0, 0, 0, 0 },
			{ 0, 0, 0, 3, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0, 0, 0, 0 },

		};
		for (int r = 0; r < ROWS; r++)
		{
			for (int c = 0; c < COLS; c++)
			{
				board.grid[r][c] = stage3[r][c];
			}
		}
	}
	if (stageNo == 4)
	{
		int stage4[ROWS][COLS]
		= {
			{ 0, 5, 5, 0, 0, 2, 2, 0 },
			{ 0, 6, 0, 0, 0, 7, 0, 0 },
			{ 0, 2, 0, 0, 0, 3, 0, 0 },
			{ 0, 6, 0, 0, 0, 3, 0, 0 },
			{ 0, 6, 0, 0, 0, 3, 0, 0 },
			{ 0, 1, 0, 0, 0, 6, 0, 0 },
			{ 0, 6, 0, 0, 0, 2, 0, 0 },
			{ 0, 1, 0, 0, 0, 3, 0, 0 },
		};
		for (int r = 0; r < ROWS; r++)
		{
			for (int c = 0; c < COLS; c++)
			{
				board.grid[r][c] = stage4[r][c];
			}
		}
	}
}