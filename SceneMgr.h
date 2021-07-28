#pragma once

typedef enum {
	eScene_Title,	//タイトル画面
	eScene_Game,	//正方形Nomal.ver
	eScene_Game1,   //正方形Lessthan.ver
	eScene_Game2,	//ひし形Nomal.ver
	eScene_Game3,	//ひし形Lessthan.ver
	eScene_Help,	//ヘルプ画面
	eScene_End,		//エンド画面
	eScene_Stop,	//ストップ
	eScene_Stage,	//正方形ステージ
	eScene_Stage1,  //ひし形ステージ
	eScene_Mode,	//モード画面
	eScene_None,
}eScene;

void SceneMgr_Initialize();
void SceneMgr_Finalize();
void SceneMgr_Update();
void SceneMgr_Draw();

//引数nextSceneにシーンを変更する
void  SceneMgr_ChangeScene(eScene nextScene);

//ゲーム終了メニューが選択されたかどうかを返す
int SceneMgr_GameEnd_Status();