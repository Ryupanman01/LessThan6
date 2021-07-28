#include "DxLib.h"
#include "Input.h"
#include "Stage.h"
#include "SceneMgr.h"

//画像
static int mImageStage;
static int mImageCursor;

//カーソル
static int MenuNumber;

//カーソル位置
static int x = 0;

//初期化
void Stage_Initialize() {
	//画像
	mImageStage = LoadGraph("images/Stage.png");
	mImageCursor = LoadGraph("images/cursol.png");

	//カーソル初期位置
	MenuNumber = 0;
}

//終了処理
void Stage_Finalize() {
	//画像
	DeleteGraph(mImageStage);
	DeleteGraph(mImageCursor);
}

//更新
void Stage_Update() {
	//カーソルの動きに合わせたシーンの切り替えカーソルの動き
	if (iKeyFlg & PAD_INPUT_RIGHT) {
		PlaySound("sounds/Cursor.mp3", DX_PLAYTYPE_BACK);
		if (++MenuNumber > 1) MenuNumber = 0;
	}
	if (iKeyFlg & PAD_INPUT_LEFT) {
		PlaySound("sounds/Cursor.mp3", DX_PLAYTYPE_BACK);
		if (--MenuNumber < 0) MenuNumber = 1;
	}
	if (iKeyFlg == PAD_INPUT_10 || iKeyFlg == PAD_INPUT_1) { //Zキーが押されていたら
		PlaySound("sounds/Put.mp3", DX_PLAYTYPE_BACK);
		switch (MenuNumber) { //シーンによって処理を分岐
		case 0: //現在の画面がメニューなら
			SceneMgr_ChangeScene(eScene_Game); //四角形盤
			break;
		case 1:
			SceneMgr_ChangeScene(eScene_Game2); //ひし形盤
			break;
		}
	}
	if (iKeyFlg == PAD_INPUT_B || iKeyFlg == PAD_INPUT_9) {//Escキーが押されていたら
		PlaySound("sounds/Back.mp3", DX_PLAYTYPE_BACK);
		SceneMgr_ChangeScene(eScene_Mode);//シーンをメニューに変更
	}
}

//描画
void Stage_Draw() {
	DrawGraph(0, 0, mImageStage, false);
	DrawRotaGraph(30 + 230 * MenuNumber, 372, 0.1f, 0, mImageCursor, true);
}