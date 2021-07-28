#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Player.h"

//�ϐ�
struct PLAYER mPlayer;
static int mImagePlayer;

//������
void Player_Initialize() {
	mImagePlayer = LoadGraph("images/Player.png");

	//�v���C���[�̏����ݒ�
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	mPlayer.w = PLAYER_WIDTH;
	mPlayer.h = PLAYER_HEIGHT;
	mPlayer.cursorx = 3;
	mPlayer.cursory = 3;
	mPlayer.time = 0;
}

//�I������
void Player_Finalize() {
	//�摜
	DeleteGraph(mImagePlayer);
}

//�X�V
void Player_Update() {
	//�J�[�\���̓����Ɖ�ʂ̊O�ɏo���Ƃ��̏���
	if (iKeyFlg & PAD_INPUT_LEFT) {
		if (--mPlayer.cursorx < 0)
			mPlayer.cursorx = 7;
	}
	if (iKeyFlg & PAD_INPUT_RIGHT) {
		if (++mPlayer.cursorx > 7)
			mPlayer.cursorx = 0;
	}
	if (iKeyFlg & PAD_INPUT_UP) {
		if (--mPlayer.cursory < 0)
			mPlayer.cursory = 7;
	}
	if (iKeyFlg & PAD_INPUT_DOWN) {
		if (++mPlayer.cursory > 7)
			mPlayer.cursory = 0;
	}
}

//�`��
void Player_Draw() {
	//�v���C���[�̕\��
	if (mPlayer.flg) {
	}
	else if (iNowKey & PAD_INPUT_LEFT) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 60, mPlayer.y + mPlayer.cursory * 60, 1.0, 0, mImagePlayer, TRUE);
	}
	else if (iNowKey & PAD_INPUT_RIGHT) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 60, mPlayer.y + mPlayer.cursory * 60, 1.0, 0, mImagePlayer, TRUE);
	}
	else if (iNowKey & PAD_INPUT_UP) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 60, mPlayer.y + mPlayer.cursory * 60, 1.0, 0, mImagePlayer, TRUE);
	}
	else if (iNowKey & PAD_INPUT_DOWN) {
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 60, mPlayer.y + mPlayer.cursory * 60, 1.0, 0, mImagePlayer, TRUE);
	}
	else {//�Ԃ������Ƃ��̕\��
		DrawRotaGraph(mPlayer.x + mPlayer.cursorx * 60, mPlayer.y + mPlayer.cursory * 60, 1.0, 0, mImagePlayer, TRUE);
	}
}