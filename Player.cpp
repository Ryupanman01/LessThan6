#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Player.h"

//変数
struct PLAYER mPlayer;
static int mImagePlayer;

//初期化
void Player_Initialize() {
	mImagePlayer = LoadGraph("images/Player.png");

	//プレイヤーの初期設定
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	mPlayer.w = PLAYER_WIDTH;
	mPlayer.h = PLAYER_HEIGHT;
	mPlayer.cursorx = 3;
	mPlayer.cursory = 3;
	mPlayer.time = 0;
}

//終了処理
void Player_Finalize() {
	//画像
	DeleteGraph(mImagePlayer);
}

//更新
void Player_Update() {
	//カーソルの動きと画面の外に出たときの処理
	if (iKeyFlg & PAD_INPUT_LEFT) {
		if (--mPlayer.cursorx < 0)
			mPlayer.cursorx = 7;
	}
	if (iKeyFlg & PAD_INPUT_RIGHT) {
		if (++mPlayer.cursorx > 7)
			mPlayer.cursorx = 0;
	}
	if (iKeyFlg & PAD_INPUT_UP) {
		if (--mPlayer.cursory < 0)
			mPlayer.cursory = 7;
	}
	if (iKeyFlg & PAD_INPUT_DOWN) {
		if (++mPlayer.cursory > 7)
			mPlayer.cursory = 0;
	}
}

//描画
void Player_Draw() {
	//プレイヤーの表示
	if (mPlayer.flg) {
	}
	else if (iNowKey & PAD_INPUT_LEFT) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 60, mPlayer.y + mPlayer.cursory * 60, 1.0, 0, mImagePlayer, TRUE);
	}
	else if (iNowKey & PAD_INPUT_RIGHT) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 60, mPlayer.y + mPlayer.cursory * 60, 1.0, 0, mImagePlayer, TRUE);
	}
	else if (iNowKey & PAD_INPUT_UP) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 60, mPlayer.y + mPlayer.cursory * 60, 1.0, 0, mImagePlayer, TRUE);
	}
	else if (iNowKey & PAD_INPUT_DOWN) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 60, mPlayer.y + mPlayer.cursory * 60, 1.0, 0, mImagePlayer, TRUE);
	}
	else {//ぶつかったときの表示
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 60, mPlayer.y + mPlayer.cursory * 60, 1.0, 0, mImagePlayer, TRUE);
	}
}