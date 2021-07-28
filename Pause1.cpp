#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Pause1.h"

static int PauseImage;		//ポーズ画面画像
static int mImagecursor;	//カーソル画像

static int MenuNumber = 0;	//メニューカーソル管理用変数

//初期化
void Pause1_Initialize() {
	//画像
	PauseImage = LoadGraph("images/Pause1.png");
	mImagecursor = LoadGraph("images/cursol.png");

	//カーソルの初期位置
	MenuNumber = 0;
}

//終了処理
void Pause1_Finalize() {
	//画像
	DeleteGraph(PauseImage);
	DeleteGraph(mImagecursor);
}

//更新
void Pause1_Update() {
	//カーソルの動きに合わせたシーンの切り替えとカーソルの動き
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
		case 0:
			SceneMgr_ChangeScene(eScene_Game1); //シーンをゲーム画面に変更
			break;
		case 1:
			SceneMgr_ChangeScene(eScene_Title); //シーンをゲーム画面に変更
			break;
		}
	}
}

//描画
void Pause1_Draw() {
	DrawGraph(120, 100, PauseImage, FALSE);
	//メニューカーソル
	DrawRotaGraph(150, 260 + MenuNumber * 50, 0.07f, 0, mImagecursor, TRUE);
}