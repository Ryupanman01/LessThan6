#include "DxLib.h"
#include "Help.h"
#include "Game.h"
#include "Game1.h"
#include "Game2.h"
#include "Game3.h"
#include "Title.h"
#include "End.h"
#include "SceneMgr.h"
#include "Stage.h"
#include "Stage1.h"
#include "Mode.h"

static eScene mScene = eScene_Title;			//�V�[���Ǘ��ϐ�
static eScene mNextScene = eScene_None;		//���̃V�[���Ǘ��ϐ�

static void SceneMgr_InitializeModule(eScene scene);//�w�胂�W���[��������������
static void SceneMgr_FinalizeModule(eScene scene);	//�w�胂�W���[���̏I���������s��

//������
void SceneMgr_Initialize() {
	SceneMgr_InitializeModule(mScene);
}

//�I������
void SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(mScene);
}

//�X�V
void SceneMgr_Update() {
	if (mNextScene != eScene_None) {			//���̃V�[�����Z�b�g����Ă�����
		SceneMgr_FinalizeModule(mScene);		//���݂̃V�[���̏I�����������s
		mScene = mNextScene;					//���̃V�[�������݂̃V�[���Z�b�g
		mNextScene = eScene_None;				//���̃V�[�������N���A
		SceneMgr_InitializeModule(mScene);		//���݂̃V�[����������
	}
	switch (mScene) {							//�V�[���ɂ���ď����𕪊�
	case eScene_Title:							//���݂̉�ʂ����j���[�Ȃ�
		Menu_Update();						//���j���[��ʂ̍X�V����������
		break;
	case eScene_Game:	//���݂̉�ʂ������`Nomal.ver�Ȃ�
		Game_Update();
		break;
	case eScene_Game1:  //���݂̉�ʂ������`LessThan.ver�Ȃ�
		Game1_Update();
		break;
	case eScene_Game2:  //���݂̉�ʂ��Ђ��`Nomal.ver�Ȃ�
		Game2_Update();
		break;
	case eScene_Game3:	//���݂̉�ʂ��Ђ��`LessThan.ver�Ȃ�
		Game3_Update();
		break;
	case eScene_Mode:	//���݂̉�ʂ����[�h��ʂȂ�
		Mode_Update();
		break;
	case eScene_Stage:	//���݂̉�ʂ������`�X�e�[�W�Ȃ�
		Stage_Update();
		break;

	case eScene_Stage1:	//���݂̉�ʂ��Ђ��`�X�e�[�W�Ȃ�
		Stage1_Update();
		break;

	case eScene_Help:	//���݂̉�ʂ��w���v��ʂȂ�
		Help_Update();
		break;
	case eScene_End:	//���݂̉�ʂ��G���h��ʂȂ�
		break;
	}
}

//�`��
void SceneMgr_Draw() {
	switch (mScene) {
	case eScene_Title:	//���݂̉�ʂ��^�C�g����ʂȂ�
		Menu_Draw();
		break;
	case eScene_Game:	//���݂̉�ʂ������`Nomal.ver�Ȃ�
		Game_Draw();
		break;
	case eScene_Game1:  //���݂̉�ʂ������`LessThan.ver�Ȃ�
		Game1_Draw();
		break;
	case eScene_Game2:	//���݂̉�ʂ��Ђ��`Nomal.ver�Ȃ�
		Game2_Draw();
		break;
	case eScene_Game3:	//���݂̉�ʂ��Ђ��`LessThan.ver�Ȃ�
		Game3_Draw();
		break;
	case eScene_Mode:	//���݂̉�ʂ����[�h��ʂȂ�
		Mode_Draw();
		break;
	case eScene_Stage:	//���݂̉�ʂ������`�X�e�[�W�Ȃ�
		Stage_Draw();
		break;
	case eScene_Stage1:	//���݂̉�ʂ��Ђ��`�X�e�[�W�Ȃ�
		Stage1_Draw();
		break;
	case eScene_Help:	//���݂̉�ʂ��w���v��ʂȂ�
		Help_Draw();
		break;
	case eScene_End:	//���݂̉�ʂ��G���h��ʂȂ�
		End_Draw();
		break;
	}
}

// ���� nextScene �ɃV�[����ύX����
void SceneMgr_ChangeScene(eScene NextScene) {
	mNextScene = NextScene; //���̃V�[�����Z�b�g����
}

//����scene���W���[��������������
static void SceneMgr_InitializeModule(eScene scene) {
	switch (scene) {
	case eScene_Title:	//���݂̉�ʂ��^�C�g����ʂȂ�
		Menu_Initialize();
		break;
	case eScene_Game:	//���݂̉�ʂ������`Nomal.ver�Ȃ�
		Game_Initialize();
		break;
	case eScene_Game1:  //���݂̉�ʂ������`LessThan.ver�Ȃ�
		Game1_Initialize();
		break;
	case eScene_Game2:	//���݂̉�ʂ��Ђ��`Nomal.ver�Ȃ�
		Game2_Initialize();
		break;
	case eScene_Game3:	//���݂̉�ʂ��Ђ��`LessThan.ver�Ȃ�
		Game3_Initialize();
		break;
	case eScene_Mode:	//���݂̉�ʂ����[�h��ʂȂ�
		Mode_Initialize();
		break;
	case eScene_Stage:	//���݂̉�ʂ������`�X�e�[�W�Ȃ�
		Stage_Initialize();
		break;
	case eScene_Stage1:	//���݂̉�ʂ��Ђ��`�X�e�[�W�Ȃ�
		Stage1_Initialize();
		break;
	case eScene_Help:	//���݂̉�ʂ��w���v��ʂȂ�
		Help_Initialize();
		break;
	case eScene_End:	//���݂̉�ʂ��G���h��ʂȂ�
		End_Initialize();
		break;
	}
}

//����scene���W���[���̏I���������s��
static void SceneMgr_FinalizeModule(eScene scene) {
	switch (scene) {
	case eScene_Title:	//���݂̉�ʂ��^�C�g����ʂȂ�
		Menu_Finalize();
		break;
	case eScene_Game:	//���݂̉�ʂ������`Nomal.ver�Ȃ�
		Game_Finalize();
		break;
	case eScene_Game1:  //���݂̉�ʂ������`LessThan.ver�Ȃ�
		Game1_Finalize();
		break;
	case eScene_Game2:	//���݂̉�ʂ��Ђ��`Nomal.ver�Ȃ�
		Game2_Finalize();
		break;
	case eScene_Game3:	//���݂̉�ʂ��Ђ��`LessThan.ver�Ȃ�
		Game3_Finalize();
		break;
	case eScene_Mode:	//���݂̉�ʂ����[�h��ʂȂ�
		Mode_Finalize();
		break;
	case eScene_Stage:	//���݂̉�ʂ������`�X�e�[�W�Ȃ�
		Stage_Finalize();
		break;

	case eScene_Stage1:	//���݂̉�ʂ��Ђ��`�X�e�[�W�Ȃ�
		Stage1_Finalize();
		break;

	case eScene_Help:	//���݂̉�ʂ��w���v��ʂȂ�
		Help_Finalize();
		break;
	case eScene_End:	//���݂̉�ʂ��G���h��ʂȂ�
		End_Finalize();
		break;
	}
}

//���j���[��"�Q�[���G���h"���I�����ꂽ���ǂ�����Ԃ�
int SceneMgr_GameEnd_Status() {
	if (mScene == eScene_Stop) {	//�Q�[�����~�߂�
		return 1;
	}
	else {
		return 0;
	}
}