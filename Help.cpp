#include "Help.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Input.h"

static int mImageHandle; //画像ハンドル格納用変数

//初期化
void Help_Initialize() {
	//画像
	mImageHandle = LoadGraph("images/Help.png");
}

//終了処理
void Help_Finalize() {
	//画像の解放
	DeleteGraph(mImageHandle);
}

//更新
void Help_Update() {
	if (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0) {//Escキーが押されていたら
		PlaySound("sounds/Back.mp3", DX_PLAYTYPE_BACK);
		SceneMgr_ChangeScene(eScene_Title);//シーンをメニューに変更
	}
}

//描画
void Help_Draw() {
	DrawGraph(0, 0, mImageHandle, FALSE);
}