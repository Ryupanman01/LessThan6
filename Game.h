#pragma once

void Game_Initialize();	//������
void Game_Finalize();	//�I������
void Game_Update();		//�X�V
void Game_Draw();		//�`��

static void KomaDraw();		//��`��
static void Put();
static void checkWinner();
static void CheckKoma();
static void Turn();