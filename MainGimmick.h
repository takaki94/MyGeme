#pragma once
#include "DxLib.h"
#include "common.h"

typedef struct Maingmc
{
	int x;
	int y;
	int w;
	int h;
	int graph;		// �u���b�N�摜
	int breakgraph;	// ��ꂽ�u���b�N�摜
	int fall;		// �u���b�N�̏�Ԃ��Ǘ�(0=�ҋ@,1=���s,2=�I��)
	int rad;		// �����_���Ȑ��l������
	bool draw;		// �`�悷�邩���Ȃ���
	bool breakdraw;	// ��ꂽ���̕`������邩���Ȃ���
}Maingmc;

//������
void Maingmc_Init();
//�A�b�v�f�[�g
void Maingmc_Update();
//�u���b�N�̏�ԍX�V
void Maingmc_HitCheck();
//�`��
void Maingmc_Draw();
//�|�[�Y�@�\
void Maingmc_Pause();
//�u���b�N�������@�\
void Maingmc_Delete2();

int Check_Link_RIGHT(int x, int y, int num[][MAP_X]);			//�E���̗אڔ���(1���)
int Check_Link_RIGHT2(int x, int y, int num[][MAP_X], int cnt);	//�E���̗אڔ���(2��ڈȍ~)
int Check_Link_LEFT(int x, int y, int num[][MAP_X], int cnt);	//�����̗אڔ���
//int Check_Link_UP(int x, int y, int num[][MAP_X], int cnt);
int Check_Link_UP(int x, int y, int num[][MAP_X]);				//��̗אڔ���(1���)
int	Check_Link_UP2(int x, int y, int num[][MAP_X], int cnt);	//��̗אڔ���(2��ڈȍ~)
int Check_Link_DOWN(int x, int y, int num[][MAP_X], int cnt);	//���̗אڔ���

void Fall_Graph(Maingmc p[][MAP_X], int num[][MAP_X], int y, int x);	//��������ɏ�̃u���b�N�𗎂Ƃ��֐�

void Shuffle(Maingmc *p, Maingmc *p2);	//S����������㉺�����ւ���֐�

void Text_Draw();	//�����̕`��


void Game_Title(int *check, int push);	//�^�C�g�����
void Game_Play(int *check);				//�v���C���̉��
void Game_End(int *check, int push);	//���U���g���

//void Test_Debug();