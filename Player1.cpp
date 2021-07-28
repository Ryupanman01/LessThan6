#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Player1.h"

//変数
struct PLAYER1 mPlayer;
static int mImagePlayer1;

//初期化
void Player1_Initialize() {
	mImagePlayer1 = LoadGraph("images/Player1.png");

	//プレイヤーの初期設定
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	mPlayer.cursorx = 4;
	mPlayer.cursory = 5;
	mPlayer.time = 0;
}

//終了処理
void Player1_Finalize() {
	//画像
	DeleteGraph(mImagePlayer1);
}

//更新
void Player1_Update() {
	//カーソルの動きと画面の外に出たときの処理
	if (iKeyFlg & PAD_INPUT_LEFT) {
		if (--mPlayer.cursorx < 0)
			mPlayer.cursorx = 9;
	}
	if (iKeyFlg & PAD_INPUT_RIGHT) {
		if (++mPlayer.cursorx > 9)
			mPlayer.cursorx = 0;
	}
	if (iKeyFlg & PAD_INPUT_UP) {
		if (--mPlayer.cursory < 0)
			mPlayer.cursory = 9;
	}
	if (iKeyFlg & PAD_INPUT_DOWN) {
		if (++mPlayer.cursory > 9)
			mPlayer.cursory = 0;
	}
}

//描画
void Player1_Draw() {
	//プレイヤーの表示
	if (mPlayer.flg) {
	}
	else if (iNowKey & PAD_INPUT_LEFT) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 48, mPlayer.y + mPlayer.cursory * 48, 1.0, 0, mImagePlayer1, TRUE);
	}
	else if (iNowKey & PAD_INPUT_RIGHT) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 48, mPlayer.y + mPlayer.cursory * 48, 1.0, 0, mImagePlayer1, TRUE);
	}
	else if (iNowKey & PAD_INPUT_UP) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 48, mPlayer.y + mPlayer.cursory * 48, 1.0, 0, mImagePlayer1, TRUE);
	}
	else if (iNowKey & PAD_INPUT_DOWN) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 48, mPlayer.y + mPlayer.cursory * 48, 1.0, 0, mImagePlayer1, TRUE);
	}
	else {//ぶつかったときの表示
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 48, mPlayer.y + mPlayer.cursory * 48, 1.0, 0, mImagePlayer1, TRUE);
	}
}
