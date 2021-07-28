#include "DxLib.h"
#include "Input.h"
#include "Stage.h"
#include "SceneMgr.h"

//�摜
static int mImageStage;
static int mImageCursor;

//�J�[�\��
static int MenuNumber;

//�J�[�\���ʒu
static int x = 0;

//������
void Stage_Initialize() {
	//�摜
	mImageStage = LoadGraph("images/Stage.png");
	mImageCursor = LoadGraph("images/cursol.png");

	//�J�[�\�������ʒu
	MenuNumber = 0;
}

//�I������
void Stage_Finalize() {
	//�摜
	DeleteGraph(mImageStage);
	DeleteGraph(mImageCursor);
}

//�X�V
void Stage_Update() {
	//�J�[�\���̓����ɍ��킹���V�[���̐؂�ւ��J�[�\���̓���
	if (iKeyFlg & PAD_INPUT_RIGHT) {
		PlaySound("sounds/Cursor.mp3", DX_PLAYTYPE_BACK);
		if (++MenuNumber > 1) MenuNumber = 0;
	}
	if (iKeyFlg & PAD_INPUT_LEFT) {
		PlaySound("sounds/Cursor.mp3", DX_PLAYTYPE_BACK);
		if (--MenuNumber < 0) MenuNumber = 1;
	}
	if (iKeyFlg == PAD_INPUT_10 || iKeyFlg == PAD_INPUT_1) { //Z�L�[��������Ă�����
		PlaySound("sounds/Put.mp3", DX_PLAYTYPE_BACK);
		switch (MenuNumber) { //�V�[���ɂ���ď����𕪊�
		case 0: //���݂̉�ʂ����j���[�Ȃ�
			SceneMgr_ChangeScene(eScene_Game); //�l�p�`��
			break;
		case 1:
			SceneMgr_ChangeScene(eScene_Game2); //�Ђ��`��
			break;
		}
	}
	if (iKeyFlg == PAD_INPUT_B || iKeyFlg == PAD_INPUT_9) {//Esc�L�[��������Ă�����
		PlaySound("sounds/Back.mp3", DX_PLAYTYPE_BACK);
		SceneMgr_ChangeScene(eScene_Mode);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Stage_Draw() {
	DrawGraph(0, 0, mImageStage, false);
	DrawRotaGraph(30 + 230 * MenuNumber, 372, 0.1f, 0, mImageCursor, true);
}