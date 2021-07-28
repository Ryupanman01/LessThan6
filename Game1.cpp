#include "Game1.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Player.h"
#include "Input.h"
#include "Pause1.h"

//�Ֆʂ̑傫��
#define Boardsize 8

//��Ԃ̒�`
#define NONE -1
#define WHITE 0
#define BLACK 1

//�F
#define Blackcolor GetColor(0,0,0)
#define Whitecolor GetColor(255,255,255)
#define Redcolor GetColor(230,0,0)
#define Bluecolor GetColor(0,0,230)

//�摜
static int mImageBanmen;
static int komaImage[2];
static int ResultImage;

//�Ֆ�
static int Banmen[Boardsize][Boardsize];

//�^�[��
static int turn_flg;//BLACK;
static int turn_count;

//�R�}��
static int b;
static int w;

//�����x�N�g����
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

//�����x�N�g��
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

//�R�}���u���邩�𒲂ׂ鏈��
static bool checkPut(int color, int i, int j, bool turnOver) {
	if (Banmen[i][j] != NONE)
		return false;

	//�R�}�̒u��������𒲂ׂ鏈��
	for (int c = 0; c < DIRECTION_MAX; c++) {
		int x = i, y = j;
		y += directions[c][0];
		x += directions[c][1];

		//(1�̎���0�A0�̎���1 ,�Ƃ������Z)
		if (Banmen[x][y] != (color ^ 1))
			continue;
		while (1) {
			y += directions[c][0];
			x += directions[c][1];

			//�������ׂ�������Ֆʂ̘g���o���ꍇ�A���ׂ�̂���߂�
			if ((x < 0) || (x >= Boardsize) || (y < 0) || (y >= Boardsize)) {
				break;
			}
			//�����Ֆʂɉ����Ȃ��}�X������Β��ׂ�̂���߂�
			if (Banmen[x][y] == NONE) {
				break;
			}
			//�����ՖʂɎ����̐F������΁A���Ԃ��������ł���
			if (Banmen[x][y] == color) {
				if (!turnOver)
					return true;

				//�R�}�𗠕Ԃ�����
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

//�p�X����A���ʔ���
static bool checkPutAll(int color) {
	for (int y = 0; y < Boardsize; y++) {
		for (int x = 0; x < Boardsize; x++) {
			if (checkPut(color, y, x, false))
				return true;
		}
	}
	return false;
}

//������
void Game1_Initialize() {
	//�摜
	mImageBanmen = LoadGraph("images/banmen1.png");
	ResultImage = LoadGraph("images/Result.png");
	LoadDivGraph("images/koma.png", 2, 2, 1, 60, 60, komaImage);

	//BGM
	PlayMusic("sounds/Game.mp3", DX_PLAYTYPE_LOOP);

	//�^�[���J�E���g
	turn_count = 0;
	turn_flg = BLACK;

	//�|�[�Y
	pause_flg = 0;

	//�Ֆʏ�����
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

	//�v���C���[
	Player_Initialize();

	//�|�[�Y
	Pause1_Initialize();
}

//�I������
void Game1_Finalize() {
	DeleteGraph(mImageBanmen);
	DeleteGraph(ResultImage);

	//BGM���~
	StopMusic();

	//�v���C���[
	Player_Finalize();
	//�|�[�Y
	Pause1_Finalize();
}

//�X�V
void Game1_Update() {
	Player_Update();
	if (pause_flg == 1) {
		Pause1_Update();
	}else
	if (((b + w) >= 64 || (!checkPutAll(BLACK) && !checkPutAll(WHITE))) && (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0)) { //Esc�L�[��������Ă�����
		PlaySound("sounds/Back.mp3", DX_PLAYTYPE_BACK);
		SceneMgr_ChangeScene(eScene_Title);								//�V�[�������j���[�ɕύX
	}
	if (iKeyFlg == PAD_INPUT_9) {
		pause_flg = (pause_flg ^ 1);
	}
}

//�`��
void Game1_Draw() {
	//�摜
	DrawGraph(0, 0, mImageBanmen, FALSE);

	//�
	CheckKoma();

	if ((b + w) < 64 && (checkPutAll(BLACK) || checkPutAll(WHITE))) {
		//�t���O���o������|�[�Y��ʕ`��
		if (pause_flg == 1) {
			Pause1_Draw();
		}
		else {
			//�t���O���o���Ă��Ȃ���΃Q�[����ʕ`��
			Player_Draw();	//�v���C���[
			Put();			//���u��
			KomaDraw();		//��`��
			Turn();			//�^�[��
		}
	}
	else if ((b + w) >= 64 || !checkPutAll(BLACK) && !checkPutAll(WHITE)) {
		checkWinner();	//���U���g
	}
}

//��̕\��
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

//�w�肵���ʒu�ɋ��`��
void Put() {
	//�u���Ȃ��Ƃ���ɒu�����Ƃ��ł��Ȃ�
	if (!checkPut(turn_flg, mPlayer.cursorx, mPlayer.cursory, false)) {
		return;
	}
	else if (turn_flg == BLACK && (iKeyFlg & PAD_INPUT_10 || iKeyFlg & PAD_INPUT_A)) {
		PlaySound("sounds/coma.mp3", DX_PLAYTYPE_BACK);
		checkPut(turn_flg, mPlayer.cursorx, mPlayer.cursory, true);
		Banmen[mPlayer.cursorx][mPlayer.cursory] = BLACK;
		turn_count += 1;
		turn_flg = WHITE;	//�^�[���𔒂ɂ���
		if (!checkPutAll(WHITE))	//���������u�����Ƃ��ł��Ȃ��Ɣ��f������
			turn_flg = BLACK;	//���̃^�[���ɂ���

	}
	else if (turn_flg == WHITE && (iKeyFlg & PAD_INPUT_10 || iKeyFlg & PAD_INPUT_A)) {
		PlaySound("sounds/coma.mp3", DX_PLAYTYPE_BACK);
		checkPut(turn_flg, mPlayer.cursorx, mPlayer.cursory, true);
		Banmen[mPlayer.cursorx][mPlayer.cursory] = WHITE;
		turn_count += 1;
		turn_flg = BLACK;	//�^�[�������ɂ���
		if (!checkPutAll(BLACK))	//���������u�����Ƃ��ł��Ȃ��Ɣ��f������
			turn_flg = WHITE;	//���̃^�[���ɂ���

	}
}

//�
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

//���Ҕ���
void checkWinner() {

	CheckKoma();	//��̐��𐔂���

	//Result��ʕ\��
	DrawGraph(100, 50, ResultImage, TRUE);
	SetFontSize(30);
	DrawFormatString(170, 230, Blackcolor, "�� : %d��", b);
	DrawFormatString(170, 270, Whitecolor, "�� : %d��", w);

	//���҂�\��
	SetFontSize(25);
	if (b < w)
		DrawString(175, 160, "��Winner!", Blackcolor);
	else if (b > w)
		DrawString(175, 160, "��Winner!", Whitecolor);
	else
		DrawString(190, 160, "�`Draw�`", Redcolor);
}

void Turn() {
	//�^�[���\��
	SetFontSize(15);
	if (turn_flg == BLACK) {
		DrawString(180, 232, "��Player�^�[��", Blackcolor);
	}
	else if (turn_flg == WHITE) {
		DrawString(180, 232, "��Player�^�[��", Whitecolor);
	}
}