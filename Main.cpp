#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);			//ウィンドウモード変更
	SetGraphMode(480, 480, 32);
	DxLib_Init();					//DXライブラリ初期化
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面設定
	
	SceneMgr_Initialize();			//初期化

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {	//画面更新 & メッセージ処理 & 画面消去

		if (SceneMgr_GameEnd_Status()) {//メニューから収量が選択されたら
			break;
		}
		ClearDrawScreen();			//画面消去

		InputKey();					//入力

		SceneMgr_Update();			//更新
		SceneMgr_Draw();			//描画

		ScreenFlip();				//画面更新
	}

	SceneMgr_Finalize();			//終了処理

	DxLib_End();
	return 0;
}