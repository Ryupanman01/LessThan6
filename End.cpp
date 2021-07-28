#include "End.h"
#include "SceneMgr.h"
#include "DxLib.h"

//�摜
static int mImageHandle;
//�G���h��ʕ\������
static int StopTime;

//������
void End_Initialize() {
	//BGM
	PlayMusic("sounds/End.mp3", DX_PLAYTYPE_BACK);
	//�摜
	mImageHandle = LoadGraph("images/End.png");
	//�~�߂邽�߂̎���
	StopTime = 0;
}

//�I������
void End_Finalize() {
	//�摜
	DeleteGraph(mImageHandle);
	//BGM
	StopMusic();
}

//�`��
void End_Draw() {
	//�摜
	DrawGraph(0, 0, mImageHandle, FALSE);

	//�^�C���̉��Z����&�I���i3�b��j
	if (++StopTime > 180) {
		SceneMgr_ChangeScene(eScene_Stop);  //�V�[�����Q�[����ʂɕύX
	}
}