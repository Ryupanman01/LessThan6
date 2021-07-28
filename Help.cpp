#include "Help.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Input.h"

static int mImageHandle; //�摜�n���h���i�[�p�ϐ�

//������
void Help_Initialize() {
	//�摜
	mImageHandle = LoadGraph("images/Help.png");
}

//�I������
void Help_Finalize() {
	//�摜�̉��
	DeleteGraph(mImageHandle);
}

//�X�V
void Help_Update() {
	if (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0) {//Esc�L�[��������Ă�����
		PlaySound("sounds/Back.mp3", DX_PLAYTYPE_BACK);
		SceneMgr_ChangeScene(eScene_Title);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Help_Draw() {
	DrawGraph(0, 0, mImageHandle, FALSE);
}