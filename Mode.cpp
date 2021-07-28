#include "DxLib.h"
#include "Mode.h"
#include "Input.h"
#include "SceneMgr.h"

//画像
static int mImageMode;
static int mImageCursor;

static int MenuNumber;

//初期化
void Mode_Initialize() {
	mImageMode = LoadGraph("images/Mode.png");
	mImageCursor = LoadGraph("images/cursol.png");

	//カーソルの初期位置
	MenuNumber = 0;
}

//終了処理
void Mode_Finalize() {
	//画像終了処理
	DeleteGraph(mImageMode);
	DeleteGraph(mImageCursor);
}

//更新
void Mode_Update() {
	//カーソルの動きに合わせたシーンの切り替えカーソルの動き
	if (iKeyFlg & PAD_INPUT_DOWN) {
		PlaySound("sounds/Cursor.mp3", DX_PLAYTYPE_BACK);
		if (++MenuNumber > 1) MenuNumber = 0;
	}
	if (iKeyFlg & PAD_INPUT_UP) {
		PlaySound("sounds/Cursor.mp3", DX_PLAYTYPE_BACK);
		if (--MenuNumber < 0) MenuNumber = 1;
	}
	if (iKeyFlg == PAD_INPUT_10 || iKeyFlg == PAD_INPUT_1) { //Zキーが押されていたら
		PlaySound("sounds/Put.mp3", DX_PLAYTYPE_BACK);
		switch (MenuNumber) { //シーンによって処理を分岐
		case 0: //現在の画面がメニューなら
			SceneMgr_ChangeScene(eScene_Stage); //Nomalの時
			break;
		case 1:
			SceneMgr_ChangeScene(eScene_Stage1); //LessThanの時
			break;
		}
	}
	if (iKeyFlg == PAD_INPUT_B || iKeyFlg == PAD_INPUT_9) {//Escキーが押されていたら
		PlaySound("sounds/Back.mp3", DX_PLAYTYPE_BACK);
		SceneMgr_ChangeScene(eScene_Title);//シーンをメニューに変更
	}
}

//描画
void Mode_Draw() {
	//画像描画
	DrawGraph(0, 0, mImageMode, false);
	DrawRotaGraph(125, 200 + MenuNumber * 78, 0.1f, 0, mImageCursor, TRUE);
}