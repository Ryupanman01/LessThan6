#include "Game1.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Player.h"
#include "Input.h"
#include "Pause1.h"

//盤面の大きさ
#define Boardsize 8

//状態の定義
#define NONE -1
#define WHITE 0
#define BLACK 1

//色
#define Blackcolor GetColor(0,0,0)
#define Whitecolor GetColor(255,255,255)
#define Redcolor GetColor(230,0,0)
#define Bluecolor GetColor(0,0,230)

//画像
static int mImageBanmen;
static int komaImage[2];
static int ResultImage;

//盤面
static int Banmen[Boardsize][Boardsize];

//ターン
static int turn_flg;//BLACK;
static int turn_count;

//コマ数
static int b;
static int w;

//方向ベクトル名
enum {
	DIRECTION_UP,
	DIRECTION_UP_LEFT,
	DIRECTION_LEFT,
	DIRECTION_DOWN_LEFT,
	DIRECTION_DOWN,
	DIRECTION_DOWN_RIGHT,
	DIRECTION_RIGHT,
	DIRECTION_UP_RIGHT,
	DIRECTION_MAX
};

//方向ベクトル
static int directions[][2] = {
	{0,-1},//DIRECTION_UP
	{-1,-1},//DIRECTION_UP_LEFT
	{-1,0},//DIRECTION_LEFT
	{-1,1},//DIRECTION_DOWN_LEFT
	{0,1},//DIRECTION_DOWN
	{1,1},//DIRECTION_DOWN_RIGHT
	{1,0},//DIRECTION_RIGHT
	{1,-1}//DIRECTION_UP_RIGHT
};

//コマが置けるかを調べる処理
static bool checkPut(int color, int i, int j, bool turnOver) {
	if (Banmen[i][j] != NONE)
		return false;

	//コマの置ける方向を調べる処理
	for (int c = 0; c < DIRECTION_MAX; c++) {
		int x = i, y = j;
		y += directions[c][0];
		x += directions[c][1];

		//(1の時は0、0の時は1 ,という演算)
		if (Banmen[x][y] != (color ^ 1))
			continue;
		while (1) {
			y += directions[c][0];
			x += directions[c][1];

			//もし調べる方向が盤面の枠を出た場合、調べるのをやめる
			if ((x < 0) || (x >= Boardsize) || (y < 0) || (y >= Boardsize)) {
				break;
			}
			//もし盤面に何もないマスがあれば調べるのをやめる
			if (Banmen[x][y] == NONE) {
				break;
			}
			//もし盤面に自分の色があれば、裏返す準備ができる
			if (Banmen[x][y] == color) {
				if (!turnOver)
					return true;

				//コマを裏返す処理
				int x2 = i, y2 = j;
				while (1) {
					Banmen[x2][y2] = color;

					y2 += directions[c][0];
					x2 += directions[c][1];

					if ((x2 == x) && (y2 == y))
						break;
				}
				break;
			}
		}
	}
	return false;
}

//パス判定、結果判定
static bool checkPutAll(int color) {
	for (int y = 0; y < Boardsize; y++) {
		for (int x = 0; x < Boardsize; x++) {
			if (checkPut(color, y, x, false))
				return true;
		}
	}
	return false;
}

//初期化
void Game1_Initialize() {
	//画像
	mImageBanmen = LoadGraph("images/banmen1.png");
	ResultImage = LoadGraph("images/Result.png");
	LoadDivGraph("images/koma.png", 2, 2, 1, 60, 60, komaImage);

	//BGM
	PlayMusic("sounds/Game.mp3", DX_PLAYTYPE_LOOP);

	//ターンカウント
	turn_count = 0;
	turn_flg = BLACK;

	//ポーズ
	pause_flg = 0;

	//盤面初期化
	int i, j;
	for (i = 0; i < Boardsize; i++) {
		for (j = 0; j < Boardsize; j++) {
			Banmen[i][j] = NONE;
		}
	}
	Banmen[3][3] = WHITE;
	Banmen[4][4] = WHITE;
	Banmen[3][4] = BLACK;
	Banmen[4][3] = BLACK;

	//プレイヤー
	Player_Initialize();

	//ポーズ
	Pause1_Initialize();
}

//終了処理
void Game1_Finalize() {
	DeleteGraph(mImageBanmen);
	DeleteGraph(ResultImage);

	//BGM中止
	StopMusic();

	//プレイヤー
	Player_Finalize();
	//ポーズ
	Pause1_Finalize();
}

//更新
void Game1_Update() {
	Player_Update();
	if (pause_flg == 1) {
		Pause1_Update();
	}else
	if (((b + w) >= 64 || (!checkPutAll(BLACK) && !checkPutAll(WHITE))) && (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0)) { //Escキーが押されていたら
		PlaySound("sounds/Back.mp3", DX_PLAYTYPE_BACK);
		SceneMgr_ChangeScene(eScene_Title);								//シーンをメニューに変更
	}
	if (iKeyFlg == PAD_INPUT_9) {
		pause_flg = (pause_flg ^ 1);
	}
}

//描画
void Game1_Draw() {
	//画像
	DrawGraph(0, 0, mImageBanmen, FALSE);

	//駒数
	CheckKoma();

	if ((b + w) < 64 && (checkPutAll(BLACK) || checkPutAll(WHITE))) {
		//フラグが経ったらポーズ画面描画
		if (pause_flg == 1) {
			Pause1_Draw();
		}
		else {
			//フラグが経っていなければゲーム画面描画
			Player_Draw();	//プレイヤー
			Put();			//駒を置く
			KomaDraw();		//駒描画
			Turn();			//ターン
		}
	}
	else if ((b + w) >= 64 || !checkPutAll(BLACK) && !checkPutAll(WHITE)) {
		checkWinner();	//リザルト
	}
}

//駒の表示
void KomaDraw() {
	int i, j;
	for (i = 0; i < Boardsize; ++i) {
		for (j = 0; j < Boardsize; ++j) {
			switch (Banmen[i][j]) {
			case NONE:
				break;
			case BLACK:
				DrawGraph(0 + 60 * i, 0 + 60 * j, komaImage[BLACK], TRUE);
				break;
			case WHITE:
				DrawGraph(0 + 60 * i, 0 + 60 * j, komaImage[WHITE], TRUE);
				break;
			default:
				break;
			}
		}
	}
}

//指定した位置に駒を描画
void Put() {
	//置けないところに置くことができない
	if (!checkPut(turn_flg, mPlayer.cursorx, mPlayer.cursory, false)) {
		return;
	}
	else if (turn_flg == BLACK && (iKeyFlg & PAD_INPUT_10 || iKeyFlg & PAD_INPUT_A)) {
		PlaySound("sounds/coma.mp3", DX_PLAYTYPE_BACK);
		checkPut(turn_flg, mPlayer.cursorx, mPlayer.cursory, true);
		Banmen[mPlayer.cursorx][mPlayer.cursory] = BLACK;
		turn_count += 1;
		turn_flg = WHITE;	//ターンを白にする
		if (!checkPutAll(WHITE))	//もし白駒を置くことができないと判断したら
			turn_flg = BLACK;	//黒のターンにする

	}
	else if (turn_flg == WHITE && (iKeyFlg & PAD_INPUT_10 || iKeyFlg & PAD_INPUT_A)) {
		PlaySound("sounds/coma.mp3", DX_PLAYTYPE_BACK);
		checkPut(turn_flg, mPlayer.cursorx, mPlayer.cursory, true);
		Banmen[mPlayer.cursorx][mPlayer.cursory] = WHITE;
		turn_count += 1;
		turn_flg = BLACK;	//ターンを黒にする
		if (!checkPutAll(BLACK))	//もし黒駒を置くことができないと判断したら
			turn_flg = WHITE;	//白のターンにする

	}
}

//駒数
void CheckKoma() {
	int i, j;
	b = 0;
	w = 0;
	for (i = 0; i < Boardsize; i++) {
		for (j = 0; j < Boardsize; j++) {
			switch (Banmen[i][j]) {
			case BLACK:
				b++;
				break;
			case WHITE:
				w++;
				break;
			case NONE:
				break;
			}
		}
	}
}

//勝者判定
void checkWinner() {

	CheckKoma();	//駒の数を数える

	//Result画面表示
	DrawGraph(100, 50, ResultImage, TRUE);
	SetFontSize(30);
	DrawFormatString(170, 230, Blackcolor, "● : %d個", b);
	DrawFormatString(170, 270, Whitecolor, "● : %d個", w);

	//勝者を表示
	SetFontSize(25);
	if (b < w)
		DrawString(175, 160, "●Winner!", Blackcolor);
	else if (b > w)
		DrawString(175, 160, "●Winner!", Whitecolor);
	else
		DrawString(190, 160, "～Draw～", Redcolor);
}

void Turn() {
	//ターン表示
	SetFontSize(15);
	if (turn_flg == BLACK) {
		DrawString(180, 232, "●Playerターン", Blackcolor);
	}
	else if (turn_flg == WHITE) {
		DrawString(180, 232, "●Playerターン", Whitecolor);
	}
}