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
void MaingmcInit();
//�A�b�v�f�[�g
void MaingmcUpdate();
//�u���b�N�̏�ԍX�V
void MaingmcHitCheck();
//�`��
void MaingmcDraw();
//�|�[�Y�@�\
void MaingmcPause();
//�u���b�N�������@�\
void MaingmcDelete2();

int CheckLinkRIGHT(int x, int y, int num[][MAP_X]);					//�E���̗אڔ���(1���)
int CheckLinkRIGHT2(int x, int y, int num[][MAP_X], int cnt);		//�E���̗אڔ���(2��ڈȍ~)
int CheckLinkLEFT(int x, int y, int num[][MAP_X], int cnt);			//�����̗אڔ���
//int CheckLinkUP(int x, int y, int num[][MAP_X], int cnt);
int CheckLinkUP(int x, int y, int num[][MAP_X]);					//��̗אڔ���(1���)
int	CheckLinkUP2(int x, int y, int num[][MAP_X], int cnt);			//��̗אڔ���(2��ڈȍ~)
int CheckLinkDOWN(int x, int y, int num[][MAP_X], int cnt);			//���̗אڔ���

void FallGraph(Maingmc p[][MAP_X], int num[][MAP_X], int y, int x);	//��������ɏ�̃u���b�N�𗎂Ƃ��֐�

void Shuffle(Maingmc *p, Maingmc *p2);								//S����������㉺�����ւ���֐�

void TextDraw();													//�����̕`��


void GameTitle(int *check, int push);	//�^�C�g�����
void GamePlay(int *check);				//�v���C���̉��
void GameEnd(int *check, int push);		//���U���g���

//void Test_Debug();