#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"
#include "Random.h"
#include "board.h"
#include "Bubble.h"
#include "Stage.h"
#include "GameMechanic.h"
#include "Launcher.h"

Board board;

Bubble shotBubble;
Bubble nextBubble;

Launcher cannon;
Arrow aim;
Handle handle;
Turning npc;

Float2 bag;

extern FallingBubble falling_bubble[MAX_FALLINGBUBBLE];
//====================cannon====================
float centerX = SCREEN_W / 2;
float bottomY = SCREEN_H - 40;

float aim_angle = -1.57f;//bubble_angle

//====================warning line====================
float warningline_x;
float warningline_y;

//====================bubble bumbers====================
int now_num;
int next_num;

//====================stage====================
int stagebg_img;
int stageNo;//stage number
bool stageCleared[MAX_STAGE];

int shot_count = 0;
int shot_limit = 6; // when player shoot 6 times the wall will fall

int bag_img;
int gameover_line_img;

int credit = 2;

//====================score====================
int score;
int total_score;

bool gameover[MAX_STAGE];

//====================timer====================
float playing_timer;
int gameover_timer = 0;
int stageClear_timer = 0;

//====================fonts====================
int gameover_font;
int stageCleared_font;
int txtui_font;

extern int drop_count;
//---------------------------------------------------------------------------------
// èâä˙âªèàóù
//---------------------------------------------------------------------------------
void GameInit()
{
    warningline_x = 198;
    warningline_y = SCREEN_H - 90;

    stageNo = stage0;
    playing_timer = 0;
    stageClear_timer = 0;

    drop_count = 0;

    int max_color = MaxBubbleColors(stageNo);
    now_num = GetRandomI(1, max_color);
    next_num = GetRandomI(1, max_color);

    nextBubble.Set(centerX - 70, bottomY + 10, next_num );

    cannon.Init();
    aim.Init();
    handle.Init();
    npc.Init();
    /*for (int i = 0; i < MAX_FALLINGBUBBLE; i++)
    {
        falling_bubble[i].active = false;
    }*/
    for (int i = 0; i < MAX_STAGE; i++)
    {
        stageCleared[i] = false;
        gameover[i] = false;
    }
    // load stage

    LoadStage(board, stageNo);
    
    stagebg_img = LoadGraph("data/bg.png");// load launcher image

    LoadBubblesImage();

    bag.x = centerX - 150.0f;
    bag.y = bottomY - 20.0f;
    bag_img = LoadGraph("data/bag.png");;// load bag image
    gameover_line_img = LoadGraph("data/gameover_line1.png");;// load gameover line image
    gameover_font = CreateFontToHandle(NULL, 24, 3);
    stageCleared_font = CreateFontToHandle(NULL, 60, 3);
    txtui_font = CreateFontToHandle( NULL, 20, 10 );
}

//---------------------------------------------------------------------------------
// çXêVèàóù
//---------------------------------------------------------------------------------
void GameUpdate()
{
    /*if (CheckHitKey(KEY_INPUT_0)) { stageNo = 0; }
    if (CheckHitKey(KEY_INPUT_1)) { stageNo = 1; }
    if (CheckHitKey(KEY_INPUT_2)) { stageNo = 2; }*/
    
    for (int i = 0; i < MAX_STAGE; i++)
    {
        if(!stageCleared[i] && stageClear_timer <= 0)
            playing_timer += 1.0f;
    }
    cannon.Set(centerX + 5, bottomY + 5);
    aim.Set(centerX, bottomY - 30.0f);
    handle.Set(centerX + 28.0f, bottomY);
    npc.Set(centerX + 19.0f, bottomY - 15.0f);
    //====================Aim====================
    if (!shotBubble.active && !gameover[stageNo])
    {
        if (CheckHitKey(KEY_INPUT_LEFT))  { aim_angle -= 0.04f;}
        if (CheckHitKey(KEY_INPUT_RIGHT)){ aim_angle += 0.04f;}
        if (aim_angle <= -2.95f) {aim_angle = -2.95f;}
        if (aim_angle >= -0.15f) { aim_angle = -0.15f; }

        cannon.Update();
        aim.Update();
        handle.Update();
        npc.Update();
    }
    //====================Bubble to shoot(ready)====================
    if (!shotBubble.active)
    {
        shotBubble.Set(centerX, bottomY - 30, now_num );

        if (PushHitKey(KEY_INPUT_SPACE) && !gameover[stageNo] && !stageCleared[stageNo])
        {
            shotBubble.Shoot(aim_angle);
            shot_count++;
        }
    }
    //====================Update Moving Bubble====================
    bool activated = shotBubble.active;

    shotBubble.Update();
    //====================Collision With Board Bubbles====================
    bool hit = false;
    if (shotBubble.active)
    {
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < board.GetTotalCol(r); c++)
            {
                if (board.grid[r][c] == 0)
                    continue;

                Float2 p = board.GetPos(r, c);

                float dx = shotBubble.x - p.x;
                float dy = shotBubble.y - p.y;

                float distSq = dx * dx + dy * dy;

                float hitDist = BUBBLE_D - 2.0f;

                if (distSq <= hitDist * hitDist)
                {
                    shotBubble.active = false;
                    hit = true;
                    break;
                }
            }
            if (hit) break;
        }
    }

    for (int i = 0; i < MAX_FALLINGBUBBLE; i++)
    {
        falling_bubble[i].Update();
    }
    //====================Attach Bubble====================
    if (activated && !shotBubble.active)
    {
        int placedR, placedC;
        ConnectBubble(
            shotBubble.x,
            shotBubble.y,
            shotBubble.color,
            placedR,
            placedC
        );
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < board.GetTotalCol(r); c++)
            {
                placed[r][c] = false;
            }
        }
        int count = IsBubbleSameColor( placedR, placedC, shotBubble.color);
        if (count >= 3)
        {
            score += count * 10;
            RemovedConnectedBubble();
            DropBubble();
            drop_count = 0;
        }
        // change to next bubble
        now_num = next_num;

        int max_color = MaxBubbleColors(stageNo);
        next_num = GetRandomI(1, max_color);

        nextBubble.Set( centerX - 70, bottomY + 10, next_num );

        if (shot_count > shot_limit)
        {
            PushBubbleToDown();
            shot_count = 0;
        }

    }
    /*for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < board.GetTotalCol(r); c++)
        {
            if (board.grid[r][c] == 0 && !stageCleared[stageNo])
            {
                stageCleared[stageNo] = true;
                break;
            }
        }
    }*/
    bool any_bubble_left = false;
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < board.GetTotalCol(r); c++)
        {
            if (board.grid[r][c] != 0) // Found a bubble!
            {
                any_bubble_left = true;
                break;
            }
        }
        if (any_bubble_left) break;
    }

    // If no bubbles were left, the stage is clear
    if (!any_bubble_left)
    {
        stageCleared[stageNo] = true;
    }

    if (GameOver())
    {
        gameover[stageNo] = true;
        gameover_timer++;
    }
    /*if (PushHitKey(KEY_INPUT_LCONTROL))
    {
        stageCleared[stageNo] = true;
    }*/
    if (gameover[stageNo])
    {
        int temp_score = total_score;
        if (PushHitKey(KEY_INPUT_RETURN))
        {
            gameover[stageNo] = false;
            gameover_timer = 0;
            score = temp_score;
            shot_count = 0;
            board.dropY = 0.0f;
            credit--;
            LoadStage(board, stageNo);
        }
    }

    if (stageCleared[stageNo])
    {
        if (stageClear_timer == 0)
        {
            int clear_bonus = 10000 * (stageNo + 1);
            score += clear_bonus;                   
            total_score = score;                    
        }
        stageClear_timer++;

        if (stageClear_timer >= 360)
        {
            stageCleared[stageNo] = false;
            stageNo += 1;

            shot_count = 0;
            board.dropY = 0.0f;
            playing_timer = 0.0f;
            stageClear_timer = 0;
            LoadStage(board, stageNo);
        }
    }
}

//---------------------------------------------------------------------------------
// ï`âÊèàóù
//---------------------------------------------------------------------------------
void GameRender()
{
    //====================Background====================
    DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, stagebg_img, TRUE);
    //====================Board Frame====================
    /*DrawFillBox(
        (int)BOARD_X - 10,
        (int)BOARD_Y - 10,
        (int)(BOARD_X + BOARD_W + 12),
        430,
        GetColor(220, 180, 100)
    );*/

    //====================Play Area====================
    /*DrawFillBox(
        (int)BOARD_X - 2,
        (int)BOARD_Y - 2,
        (int)(BOARD_X + BOARD_W + 2),
        430,
        GetColor(20, 90, 90)
    );*/
    //====================Border====================
    /*DrawLineBox(
        (int)BOARD_X - 2,
        (int)BOARD_Y - 2,
        (int)(BOARD_X + BOARD_W + 2),
        430,
        GetColor(0, 0, 0),
        4
    );*/
    //====================SCORE====================
    DrawFormatString(
        50,
        35,
        GetColor(255, 255, 255),
        "%08d",
        score
    );
    //DrawStringToHandle(50, 35, "%08d", GetColor(255, 255, 0), txtui_font);
    //====================UI====================
    /*DrawString(
        40, 20,
        "1UP",
        GetColor(0, 255, 0)
    );*/
    DrawStringToHandle(40, 20, "1UP", GetColor(0, 255, 0), txtui_font);

    DrawString(
        SCREEN_W / 2 - 30, SCREEN_H - 16,
        "ROUND 0",
        GetColor(255, 255, 255)
    ); 
    DrawFormatString(
        SCREEN_W / 2 + 32, SCREEN_H - 16,
        GetColor(255, 255, 255),
        "%d", stageNo + 1
    );
    DrawFormatString(
        SCREEN_W - 75, SCREEN_H - 16,
        GetColor(255, 255, 255),
        "CREDIT %d", credit
    );
    //====================Warning Line====================
    /*DrawLine((int)warningline_x,
        (int)warningline_y,
        (int)452,
        (int)warningline_y,
        GetColor(255, 0, 0),
        5
    );*/
    DrawGraph(warningline_x - 2, warningline_y - 3, gameover_line_img, TRUE);
    //====================Aim Line====================
    if (stageNo == stage0)
    {
        DrawString(
            SCREEN_W / 2 - 30, SCREEN_H /2,
            "TRAINING",
            GetColor(255, 255, 255)
        );
        DrawLineAA(
            (int)centerX,
            (int)bottomY - 30,
            (int)(centerX + cosf(aim_angle) * 150),
            (int)(bottomY - 30 + sinf(aim_angle) * 150),
            GetColor(255, 255, 255)
        );
    }
    //====================Board Bubbles====================
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < board.GetTotalCol(r); c++)
        {
            if (board.grid[r][c] == 0)
                continue;

            Float2 p = board.GetPos(r, c);

            DrawGraph(
                (int)(p.x - BUBBLE_R),
                (int)(p.y - BUBBLE_R),
                bubble_img[board.grid[r][c]],
                TRUE
            );
        }
    }
    //====================Ball Placement====================
    /*for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        for (int col = 0; col < BOARD_WIDTH; col++)
        {
            int x = SCREEN_W/3 - 4 + col * BUBBLE_SIZE;
            if (row % 2 == 1) x += BUBBLE_RADIUS;

            int y = 65 + row * ROW_SPACING;

            DrawCircle(x, y, BUBBLE_RADIUS, GetColor(255, 255, 255), FALSE);
        }
    }*/
    cannon.Render();
    aim.Render();
    handle.Render();
    npc.Render();

    DrawGraphF(bag.x, bag.y, bag_img, TRUE);
    //====================Bubbles====================
    shotBubble.Render();
    nextBubble.Render();
    //====================GameOver Line====================
    int ceiling_x = centerX - 128;
    int ceiling_y = bottomY - 390;
    DrawFillBox(ceiling_x, ceiling_y, ceiling_x + 256, ceiling_y + board.dropY, GetColor(179, 179, 179));
    //====================GameOver UIt====================
    if (gameover[stageNo])
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        DrawFillBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0));
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        if ((gameover_timer / 30) % 2 == 0)
        {
            DrawStringToHandle( 150, SCREEN_H / 2, "PUSH START BUTTON TO CONTINUE", GetColor(255, 255, 0), gameover_font);
            //DrawString(100, SCREEN_H / 2, "PUSH START BUTTON TO CONTINUE", GetColor(255, 255, 0));
        }
    }

    if (stageCleared[stageNo])
    {
        if (stageClear_timer <= 60)
        {
            DrawStringToHandle(SCREEN_W / 2 - 190, SCREEN_H / 2 - 110, "STAGE CLEARED", GetColor(0, 255, 0), stageCleared_font);
        }
        else if(stageClear_timer > 60 && stageClear_timer < 360)
        {
            float played_time = playing_timer / 60;
            DrawFormatStringToHandle(SCREEN_W / 2 - 80, SCREEN_H / 2 - 110, GetColor(0, 255, 0), stageCleared_font, "%.0f sec", played_time);
            DrawFormatStringToHandle(SCREEN_W / 2 - 190, SCREEN_H / 2 - 40, GetColor(0, 255, 0), stageCleared_font, "%08d pts", total_score);

        }
    }
    if (gameover[stageNo] && credit <= 0)
    {
        DrawStringToHandle(SCREEN_W / 2 - 120, SCREEN_H / 2 - 110, "GAMEOVER", GetColor(0, 255, 0), stageCleared_font);

    }
    for (int i = 0; i < MAX_FALLINGBUBBLE; i++)
    {
        falling_bubble[i].Render();
    }
}

//---------------------------------------------------------------------------------
// èIóπèàóù
//---------------------------------------------------------------------------------
void GameExit()
{
}