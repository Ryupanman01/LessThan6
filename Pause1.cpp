#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Pause1.h"

static int PauseImage;		//�|�[�Y��ʉ摜
static int mImagecursor;	//�J�[�\���摜

static int MenuNumber = 0;	//���j���[�J�[�\���Ǘ��p�ϐ�

//������
void Pause1_Initialize() {
	//�摜
	PauseImage = LoadGraph("images/Pause1.png");
	mImagecursor = LoadGraph("images/cursol.png");

	//�J�[�\���̏����ʒu
	MenuNumber = 0;
}

//�I������
void Pause1_Finalize() {
	//�摜
	DeleteGraph(PauseImage);
	DeleteGraph(mImagecursor);
}

//�X�V
void Pause1_Update() {
	//�J�[�\���̓����ɍ��킹���V�[���̐؂�ւ��ƃJ�[�\���̓���
	if (iKeyFlg & PAD_INPUT_DOWN) {
		PlaySound("sounds/Cursor.mp3", DX_PLAYTYPE_BACK);
		if (++MenuNumber > 1) MenuNumber = 0;
	}
	if (iKeyFlg & PAD_INPUT_UP) {
		PlaySound("sounds/Cursor.mp3", DX_PLAYTYPE_BACK);
		if (--MenuNumber < 0) MenuNumber = 1;
	}
	if (iKeyFlg == PAD_INPUT_10 || iKeyFlg == PAD_INPUT_1) { //Z�L�[��������Ă�����
		PlaySound("sounds/Put.mp3", DX_PLAYTYPE_BACK);
		switch (MenuNumber) { //�V�[���ɂ���ď����𕪊�
		case 0:
			SceneMgr_ChangeScene(eScene_Game1); //�V�[�����Q�[����ʂɕύX
			break;
		case 1:
			SceneMgr_ChangeScene(eScene_Title); //�V�[�����Q�[����ʂɕύX
			break;
		}
	}
}

//�`��
void Pause1_Draw() {
	DrawGraph(120, 100, PauseImage, FALSE);
	//���j���[�J�[�\��
	DrawRotaGraph(150, 260 + MenuNumber * 50, 0.07f, 0, mImagecursor, TRUE);
}