#pragma once

#pragma once
const int PLAYER_WIDTH = 43;
const int PLAYER_HEIGHT = 43;
const int PLAYER_POS_X = 24;
const int PLAYER_POS_Y = 24 ;

struct PLAYER1 {
	int flg;		//player�̏�ԃt���O
	int x, y;		//���W
	int w, h;		//���A����
	int time;		//����
	int cursorx;
	int cursory;
};

extern struct PLAYER1 mPlayer;

extern void Player1_Initialize();
extern void Player1_Finalize();
extern void Player1_Update();
extern void Player1_Draw();