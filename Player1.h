#pragma once

#pragma once
const int PLAYER_WIDTH = 43;
const int PLAYER_HEIGHT = 43;
const int PLAYER_POS_X = 24;
const int PLAYER_POS_Y = 24 ;

struct PLAYER1 {
	int flg;		//playerの状態フラグ
	int x, y;		//座標
	int w, h;		//幅、高さ
	int time;		//時間
	int cursorx;
	int cursory;
};

extern struct PLAYER1 mPlayer;

extern void Player1_Initialize();
extern void Player1_Finalize();
extern void Player1_Update();
extern void Player1_Draw();