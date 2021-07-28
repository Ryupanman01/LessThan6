#pragma once

//const int SCREEN_WIDTH = 480;
//const int SCREEN_HEIGHT = 480;
const int PLAYER_WIDTH = 60;
const int PLAYER_HEIGHT = 60;
const int PLAYER_POS_X = 30;
const int PLAYER_POS_Y = 30;

struct PLAYER {
	int flg;		//playerの状態フラグ
	int x, y;		//座標
	int w, h;		//幅、高さ
	int time;		//時間
	int cursorx;
	int cursory;
};

extern struct PLAYER mPlayer;

extern void Player_Initialize();
extern void Player_Finalize();
extern void Player_Update();
extern void Player_Draw();