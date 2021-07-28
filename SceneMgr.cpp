#include "DxLib.h"
#include "Help.h"
#include "Game.h"
#include "Game1.h"
#include "Game2.h"
#include "Game3.h"
#include "Title.h"
#include "End.h"
#include "SceneMgr.h"
#include "Stage.h"
#include "Stage1.h"
#include "Mode.h"

static eScene mScene = eScene_Title;			//シーン管理変数
static eScene mNextScene = eScene_None;		//次のシーン管理変数

static void SceneMgr_InitializeModule(eScene scene);//指定モジュールを初期化する
static void SceneMgr_FinalizeModule(eScene scene);	//指定モジュールの終了処理を行う

//初期化
void SceneMgr_Initialize() {
	SceneMgr_InitializeModule(mScene);
}

//終了処理
void SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(mScene);
}

//更新
void SceneMgr_Update() {
	if (mNextScene != eScene_None) {			//次のシーンがセットされていたら
		SceneMgr_FinalizeModule(mScene);		//現在のシーンの終了処理を実行
		mScene = mNextScene;					//次のシーンを現在のシーンセット
		mNextScene = eScene_None;				//次のシーン情報をクリア
		SceneMgr_InitializeModule(mScene);		//現在のシーンを初期化
	}
	switch (mScene) {							//シーンによって処理を分岐
	case eScene_Title:							//現在の画面がメニューなら
		Menu_Update();						//メニュー画面の更新処理をする
		break;
	case eScene_Game:	//現在の画面が正方形Nomal.verなら
		Game_Update();
		break;
	case eScene_Game1:  //現在の画面が正方形LessThan.verなら
		Game1_Update();
		break;
	case eScene_Game2:  //現在の画面がひし形Nomal.verなら
		Game2_Update();
		break;
	case eScene_Game3:	//現在の画面がひし形LessThan.verなら
		Game3_Update();
		break;
	case eScene_Mode:	//現在の画面がモード画面なら
		Mode_Update();
		break;
	case eScene_Stage:	//現在の画面が正方形ステージなら
		Stage_Update();
		break;

	case eScene_Stage1:	//現在の画面がひし形ステージなら
		Stage1_Update();
		break;

	case eScene_Help:	//現在の画面がヘルプ画面なら
		Help_Update();
		break;
	case eScene_End:	//現在の画面がエンド画面なら
		break;
	}
}

//描画
void SceneMgr_Draw() {
	switch (mScene) {
	case eScene_Title:	//現在の画面がタイトル画面なら
		Menu_Draw();
		break;
	case eScene_Game:	//現在の画面が正方形Nomal.verなら
		Game_Draw();
		break;
	case eScene_Game1:  //現在の画面が正方形LessThan.verなら
		Game1_Draw();
		break;
	case eScene_Game2:	//現在の画面がひし形Nomal.verなら
		Game2_Draw();
		break;
	case eScene_Game3:	//現在の画面がひし形LessThan.verなら
		Game3_Draw();
		break;
	case eScene_Mode:	//現在の画面がモード画面なら
		Mode_Draw();
		break;
	case eScene_Stage:	//現在の画面が正方形ステージなら
		Stage_Draw();
		break;
	case eScene_Stage1:	//現在の画面がひし形ステージなら
		Stage1_Draw();
		break;
	case eScene_Help:	//現在の画面がヘルプ画面なら
		Help_Draw();
		break;
	case eScene_End:	//現在の画面がエンド画面なら
		End_Draw();
		break;
	}
}

// 引数 nextScene にシーンを変更する
void SceneMgr_ChangeScene(eScene NextScene) {
	mNextScene = NextScene; //次のシーンをセットする
}

//引数sceneモジュールを初期化する
static void SceneMgr_InitializeModule(eScene scene) {
	switch (scene) {
	case eScene_Title:	//現在の画面がタイトル画面なら
		Menu_Initialize();
		break;
	case eScene_Game:	//現在の画面が正方形Nomal.verなら
		Game_Initialize();
		break;
	case eScene_Game1:  //現在の画面が正方形LessThan.verなら
		Game1_Initialize();
		break;
	case eScene_Game2:	//現在の画面がひし形Nomal.verなら
		Game2_Initialize();
		break;
	case eScene_Game3:	//現在の画面がひし形LessThan.verなら
		Game3_Initialize();
		break;
	case eScene_Mode:	//現在の画面がモード画面なら
		Mode_Initialize();
		break;
	case eScene_Stage:	//現在の画面が正方形ステージなら
		Stage_Initialize();
		break;
	case eScene_Stage1:	//現在の画面がひし形ステージなら
		Stage1_Initialize();
		break;
	case eScene_Help:	//現在の画面がヘルプ画面なら
		Help_Initialize();
		break;
	case eScene_End:	//現在の画面がエンド画面なら
		End_Initialize();
		break;
	}
}

//引数sceneモジュールの終了処理を行う
static void SceneMgr_FinalizeModule(eScene scene) {
	switch (scene) {
	case eScene_Title:	//現在の画面がタイトル画面なら
		Menu_Finalize();
		break;
	case eScene_Game:	//現在の画面が正方形Nomal.verなら
		Game_Finalize();
		break;
	case eScene_Game1:  //現在の画面が正方形LessThan.verなら
		Game1_Finalize();
		break;
	case eScene_Game2:	//現在の画面がひし形Nomal.verなら
		Game2_Finalize();
		break;
	case eScene_Game3:	//現在の画面がひし形LessThan.verなら
		Game3_Finalize();
		break;
	case eScene_Mode:	//現在の画面がモード画面なら
		Mode_Finalize();
		break;
	case eScene_Stage:	//現在の画面が正方形ステージなら
		Stage_Finalize();
		break;

	case eScene_Stage1:	//現在の画面がひし形ステージなら
		Stage1_Finalize();
		break;

	case eScene_Help:	//現在の画面がヘルプ画面なら
		Help_Finalize();
		break;
	case eScene_End:	//現在の画面がエンド画面なら
		End_Finalize();
		break;
	}
}

//メニューで"ゲームエンド"が選択されたかどうかを返す
int SceneMgr_GameEnd_Status() {
	if (mScene == eScene_Stop) {	//ゲームを止める
		return 1;
	}
	else {
		return 0;
	}
}