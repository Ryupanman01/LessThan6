#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Player1.h"

//�ϐ�
struct PLAYER1 mPlayer;
static int mImagePlayer1;

//������
void Player1_Initialize() {
	mImagePlayer1 = LoadGraph("images/Player1.png");

	//�v���C���[�̏����ݒ�
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	mPlayer.cursorx = 4;
	mPlayer.cursory = 5;
	mPlayer.time = 0;
}

//�I������
void Player1_Finalize() {
	//�摜
	DeleteGraph(mImagePlayer1);
}

//�X�V
void Player1_Update() {
	//�J�[�\���̓����Ɖ�ʂ̊O�ɏo���Ƃ��̏���
	if (iKeyFlg & PAD_INPUT_LEFT) {
		if (--mPlayer.cursorx < 0)
			mPlayer.cursorx = 9;
	}
	if (iKeyFlg & PAD_INPUT_RIGHT) {
		if (++mPlayer.cursorx > 9)
			mPlayer.cursorx = 0;
	}
	if (iKeyFlg & PAD_INPUT_UP) {
		if (--mPlayer.cursory < 0)
			mPlayer.cursory = 9;
	}
	if (iKeyFlg & PAD_INPUT_DOWN) {
		if (++mPlayer.cursory > 9)
			mPlayer.cursory = 0;
	}
}

//�`��
void Player1_Draw() {
	//�v���C���[�̕\��
	if (mPlayer.flg) {
	}
	else if (iNowKey & PAD_INPUT_LEFT) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 48, mPlayer.y + mPlayer.cursory * 48, 1.0, 0, mImagePlayer1, TRUE);
	}
	else if (iNowKey & PAD_INPUT_RIGHT) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 48, mPlayer.y + mPlayer.cursory * 48, 1.0, 0, mImagePlayer1, TRUE);
	}
	else if (iNowKey & PAD_INPUT_UP) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 48, mPlayer.y + mPlayer.cursory * 48, 1.0, 0, mImagePlayer1, TRUE);
	}
	else if (iNowKey & PAD_INPUT_DOWN) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 48, mPlayer.y + mPlayer.cursory * 48, 1.0, 0, mImagePlayer1, TRUE);
	}
	else {//�Ԃ������Ƃ��̕\��
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 48, mPlayer.y + mPlayer.cursory * 48, 1.0, 0, mImagePlayer1, TRUE);
	}
}
