#include "DxLib.h"
#include "Game.h"

int iOldKey;
int iNowKey;
int iKeyFlg;

int iMouseX;
int iMouseY;

//�L�[���͎擾�֐�
void InputKey(void) {
	//���̓L�[�擾
	iOldKey = iNowKey;
	iNowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	iKeyFlg = iNowKey & ~iOldKey;
}