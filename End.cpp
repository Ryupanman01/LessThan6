#include "End.h"
#include "SceneMgr.h"
#include "DxLib.h"

//画像
static int mImageHandle;
//エンド画面表示時間
static int StopTime;

//初期化
void End_Initialize() {
	//BGM
	PlayMusic("sounds/End.mp3", DX_PLAYTYPE_BACK);
	//画像
	mImageHandle = LoadGraph("images/End.png");
	//止めるための時間
	StopTime = 0;
}

//終了処理
void End_Finalize() {
	//画像
	DeleteGraph(mImageHandle);
	//BGM
	StopMusic();
}

//描画
void End_Draw() {
	//画像
	DrawGraph(0, 0, mImageHandle, FALSE);

	//タイムの加算処理&終了（3秒後）
	if (++StopTime > 180) {
		SceneMgr_ChangeScene(eScene_Stop);  //シーンをゲーム画面に変更
	}
}