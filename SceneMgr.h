#pragma once

typedef enum {
	eScene_Title,	//�^�C�g�����
	eScene_Game,	//�����`Nomal.ver
	eScene_Game1,   //�����`Lessthan.ver
	eScene_Game2,	//�Ђ��`Nomal.ver
	eScene_Game3,	//�Ђ��`Lessthan.ver
	eScene_Help,	//�w���v���
	eScene_End,		//�G���h���
	eScene_Stop,	//�X�g�b�v
	eScene_Stage,	//�����`�X�e�[�W
	eScene_Stage1,  //�Ђ��`�X�e�[�W
	eScene_Mode,	//���[�h���
	eScene_None,
}eScene;

void SceneMgr_Initialize();
void SceneMgr_Finalize();
void SceneMgr_Update();
void SceneMgr_Draw();

//����nextScene�ɃV�[����ύX����
void  SceneMgr_ChangeScene(eScene nextScene);

//�Q�[���I�����j���[���I�����ꂽ���ǂ�����Ԃ�
int SceneMgr_GameEnd_Status();