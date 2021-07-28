#include "DxLib.h"
#include "Game.h"

int iOldKey;
int iNowKey;
int iKeyFlg;

int iMouseX;
int iMouseY;

//キー入力取得関数
void InputKey(void) {
	//入力キー取得
	iOldKey = iNowKey;
	iNowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	iKeyFlg = iNowKey & ~iOldKey;
}