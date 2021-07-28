#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);			//�E�B���h�E���[�h�ύX
	SetGraphMode(480, 480, 32);
	DxLib_Init();					//DX���C�u����������
	SetDrawScreen(DX_SCREEN_BACK);	//����ʐݒ�
	
	SceneMgr_Initialize();			//������

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {	//��ʍX�V & ���b�Z�[�W���� & ��ʏ���

		if (SceneMgr_GameEnd_Status()) {//���j���[������ʂ��I�����ꂽ��
			break;
		}
		ClearDrawScreen();			//��ʏ���

		InputKey();					//����

		SceneMgr_Update();			//�X�V
		SceneMgr_Draw();			//�`��

		ScreenFlip();				//��ʍX�V
	}

	SceneMgr_Finalize();			//�I������

	DxLib_End();
	return 0;
}