#include "common.h"
#include "MainGimmick.h"
#include "bitmapText.h"
#pragma warning(disable:4996)

Maingmc mainGmc1[MAX_GRAPH];		// �u���b�N1
Maingmc mainGmc2[MAX_GRAPH];		// �u���b�N2
Maingmc mainGmcMap[MAP_Y][MAP_X];	// �ݒu��̃u���b�N
Maingmc backup;						// �u���b�N��������ւ��p
int blockImg[5];					//�u���b�N�摜
int blockBreakImg[5];				//�u���b�N����ꂽ���̉摜
int mapImg[9];						//�w�i�}�b�v�̉摜

//�w�i�}�b�v�z��
int map[MAP_Y][MAP_X] =
{
	{0,1,1,1,1,2},
	{3,4,4,4,4,5},
	{3,4,4,4,4,5},
	{3,4,4,4,4,5},
	{3,4,4,4,4,5},
	{3,4,4,4,4,5},
	{3,4,4,4,4,5},
	{3,4,4,4,4,5},
	{3,4,4,4,4,5},
	{3,4,4,4,4,5},
	{3,4,4,4,4,5},
	{6,7,7,7,7,8}
};

int blockcol[MAP_Y][MAP_X] = { 0 };	//�u���b�N�̎�ނ�ۑ�����z��
int pushkey = 0;					//�L�[�������Ă��邩���肷��
int pushkey2 = 0;					//�L�[�������Ă��邩���肷��2
int cntup = 0;						//�אڃ`�F�b�N�̊֐����ʂ��ꎞ�I�ɕۑ�����
int yh;								//y��h�����������l��ۑ�
int xw;								//x��w�����������l��ۑ�
bool loop = false;					//����������J��Ԃ����ǂ����̔���

BitmapText text;					// �e�L�X�g�p
//BitmapText textjp;

int stock = MAX_GRAPH * 2;			//�c��u���b�N�̃J�E���g

int scorecnt = 0;					//�X�R�A

int TitleImage;						//�^�C�g����ʂ̉摜
int ResultImg;						//���U���g��ʂ̉摜

void MaingmcInit()
{
	//�摜��ǂݍ���
	LoadDivGraph("image/test2.png", 5, 5, 1, 32, 32, blockImg);
	LoadDivGraph("image/test2break.png", 5, 5, 1, 32, 32, blockBreakImg);
	LoadDivGraph("image/mapchip.png", 9, 3, 3, 32, 32, mapImg);
	TitleImage = LoadGraph("image/testtitle2.png");
	ResultImg = LoadGraph("image/END.png");

	for (int i = 0; i < MAX_GRAPH; i++)
	{
		//0~4�������_���Ɏ擾
		mainGmc1[i].rad = GetRand(4);
		//�������W
		mainGmc1[i].x = 256;
		mainGmc1[i].y = 0;
		//�摜rad(0~4)��graph�ɓ����
		mainGmc1[i].graph = blockImg[mainGmc1[i].rad];
		mainGmc1[i].breakgraph = blockBreakImg[mainGmc1[i].rad];
		//�摜��H��W���擾
		GetGraphSize(mainGmc1[i].graph, &mainGmc1[i].w, &mainGmc1[i].h);
		//�u���b�N�̏�Ԃ����ׂđҋ@���(0)�ɂ���
		mainGmc1[i].fall = 0;
		//rad���O�ɂȂ�Ȃ��悤�ɂP�v���X����
		mainGmc1[i].rad++;
		//�`�悷�邩���Ȃ���
		mainGmc1[i].draw = false;
	}
	for (int i = 0; i < MAX_GRAPH; i++)
	{
		//0~4�������_���Ɏ擾
		mainGmc2[i].rad = GetRand(4);
		//�������W
		mainGmc2[i].x = 256;
		mainGmc2[i].y = -32;
		//�摜rad(0~4)��graph�ɓ����
		mainGmc2[i].graph = blockImg[mainGmc2[i].rad];
		mainGmc2[i].breakgraph = blockBreakImg[mainGmc2[i].rad];
		//�摜��H��W���擾
		GetGraphSize(mainGmc2[i].graph, &mainGmc2[i].w, &mainGmc2[i].h);
		//�u���b�N�̏�Ԃ����ׂđҋ@���(0)�ɂ���
		mainGmc2[i].fall = 0;
		//rad���O�ɂȂ�Ȃ��悤�ɂP�v���X����
		mainGmc2[i].rad++;
		//�`�悷�邩���Ȃ���
		mainGmc2[i].draw = false;
	}

	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			// ���ׂď�����
			blockcol[i][j] = 0 ;
			mainGmcMap[i][j].x = 0;
			mainGmcMap[i][j].y = 0;
			mainGmcMap[i][j].w = 0;
			mainGmcMap[i][j].h = 0;
			mainGmcMap[i][j].fall = 2;
			mainGmcMap[i][j].rad = 0;
			mainGmcMap[i][j].graph = 0;
			mainGmcMap[i][j].breakgraph = 0;
			mainGmcMap[i][j].draw = false;
			mainGmcMap[i][j].breakdraw = false;
		}
	}

	// �ŏ��̃u���b�N�𗎉��\��Ԃ�
	mainGmc1[0].fall = 1;
	mainGmc2[0].fall = 1;
	mainGmc1[0].draw = true;
	mainGmc2[0].draw = true;
	// �c��u���b�N���̏�����
	stock = MAX_GRAPH * 2 - 2;

	// �e�L�X�g�摜�ǂݍ���
	text.setFontImage(16, 6, "image/font.bmp");
	text.reMapText(" !\"#$%%'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\tabcdefghijklmnopqrstuvwxyz{|}\\");

}

void MaingmcUpdate()
{
	for (int i = 0; i < MAX_GRAPH; i++)
	{
		if (mainGmc1[i].fall == 1)
		{
			mainGmc1[i].y += grv;		// �u���b�N�𗎉�
		}
		if (mainGmc2[i].fall == 1)
		{
			mainGmc2[i].y += grv;		// �u���b�N�𗎉�
		}
		if (mainGmc1[i].fall == 1 && mainGmc2[i].fall == 1)
		{
			if (mainGmc1[i].fall == 1 && mainGmc2[i].fall == 1) 
			{
				// ���L�[�������Ă�����v���C���[���ړ�������
				if (CheckHitKey(KEY_INPUT_DOWN) == 1)
				{
					mainGmc1[i].y += grv;
					mainGmc2[i].y += grv;
				}
				if (CheckHitKey(KEY_INPUT_LEFT) == 1)
				{
					pushkey++;
					//���L�[�������ꂽ�u�Ԃ̂�
					if (pushkey == 1)
					{
						for (int j = 0; j < mainGmc1[i].w / moveSpd; j++)
						{
							mainGmc1[i].x -= moveSpd;
							mainGmc2[i].x -= moveSpd;
						}
					}
					//�������[�܂œ��B������
					if (mainGmc1[i].x <= leftMax)
					{
						mainGmc1[i].x = leftMax;
					}
					//�������[�܂œ��B������
					if (mainGmc2[i].x <= leftMax)
					{
						mainGmc2[i].x = leftMax;
					}
					//���������Ɋ��Ƀu���b�N����������
					if (blockcol[mainGmc1[i].y / mainGmc1[i].h][mainGmc1[i].x / mainGmc1[i].w] != 0)
					{
						mainGmc1[i].x = (mainGmc1[i].x / mainGmc1[i].w + 1) * mainGmc1[i].w;
					}
					//���������Ɋ��Ƀu���b�N����������
					if (blockcol[mainGmc2[i].y / mainGmc2[i].h][mainGmc2[i].x / mainGmc2[i].w] != 0)
					{
						mainGmc2[i].x = (mainGmc2[i].x / mainGmc2[i].w + 1) * mainGmc2[i].w;
					}
				}
				if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
				{
					pushkey++;
					//�E�L�[�������ꂽ�u�Ԃ̂�
					if (pushkey == 1)
					{
						for (int j = 0; j < mainGmc1[i].w / moveSpd; j++)
						{
							mainGmc1[i].x += moveSpd;
							mainGmc2[i].x += moveSpd;
						}
					}
					//�����E�[�܂œ��B������
					if (mainGmc1[i].x >= rightMax)
					{
						mainGmc1[i].x = rightMax;
					}
					//�����E�[�܂œ��B������
					if (mainGmc2[i].x >= rightMax)
					{
						mainGmc2[i].x = rightMax;
					}
					//�����E���Ɋ��Ƀu���b�N����������
					if (blockcol[mainGmc1[i].y / mainGmc1[i].h][mainGmc1[i].x / mainGmc1[i].w] != 0)
					{
						mainGmc1[i].x = (mainGmc1[i].x / mainGmc1[i].w - 1) * mainGmc1[i].w;
					}
					//�����E���Ɋ��Ƀu���b�N����������
					if (blockcol[mainGmc2[i].y / mainGmc2[i].h][mainGmc2[i].x / mainGmc2[i].w] != 0)
					{
						mainGmc2[i].x = (mainGmc2[i].x / mainGmc2[i].w - 1) * mainGmc2[i].w;
					}
				}
				else if (CheckHitKey(KEY_INPUT_LEFT) != 1 && CheckHitKey(KEY_INPUT_RIGHT) != 1)
				{
					// �ǂ���̃L�[��������Ă��Ȃ��ꍇ�Apushkey�����Z�b�g
					pushkey = 0;
				}

				if (CheckHitKey(KEY_INPUT_S) == 1)
				{
					// S�L�[��������Ă����
					pushkey2++;
					if (pushkey2 == 1)
					{
						// pushkey2��1�̏ꍇ�Ƀu���b�N�����ւ���
						Shuffle(&mainGmc1[i], &mainGmc2[i]);
					}
				}
				else
				{
					// S�L�[��������Ă��Ȃ���΃��Z�b�g
					pushkey2 = 0;
				}
				
			}
		}
	}
}

void MaingmcHitCheck()
{
	for (int i = 0; i < MAX_GRAPH; i++)
	{
		if (mainGmc1[i].fall == 1)
		{
			yh = mainGmc1[i].y / mainGmc1[i].h;					// �s�̐��l�ɕϊ�
			xw = (mainGmc1[i].x - leftMax) / mainGmc1[i].w;		// ��̐��l�ɕϊ�
			if (mainGmc1[i].y >= floor || blockcol[(mainGmc1[i].y + mainGmc1[i].h) / mainGmc1[i].h][(mainGmc1[i].x - leftMax + mainGmc1[i].w / 2) / mainGmc1[i].w] != 0)
			{	// �u���b�N���g�̈�ԉ��A�������̓u���b�N�����ɐݒu���Ă���ꏊ��œ��B�����Ƃ�
				mainGmc1[i].x = xw * mainGmc1[i].w + leftMax;	// X���W�̈ʒu���m��(��~�摜�̕�+���[�̐��l)
				mainGmc1[i].y = yh * mainGmc1[i].h;				// Y���W�̈ʒu���m��(�s�~�摜�̍���)
				mainGmc1[i].fall = 2;							// fall�̒l��2(�������Ȃ�)�ɕύX
				blockcol[yh][xw] = mainGmc1[i].rad;				// �u���b�N�̎�ނ�ۑ�
				mainGmc1[i].draw = false;						// mainGmc1��`�悵�Ȃ�

				stock--;										// �c��u���b�N�����炷

				// mainGmc1�̒��ɓ����Ă���ϐ������ׂĐݒu��̍\���̂֓����
				mainGmcMap[yh][xw].x = mainGmc1[i].x;
				mainGmcMap[yh][xw].y = mainGmc1[i].y;
				mainGmcMap[yh][xw].w = mainGmc1[i].w;
				mainGmcMap[yh][xw].h = mainGmc1[i].h;
				mainGmcMap[yh][xw].rad = mainGmc1[i].rad;
				mainGmcMap[yh][xw].graph = mainGmc1[i].graph;
				mainGmcMap[yh][xw].breakgraph = mainGmc1[i].breakgraph;
				mainGmcMap[yh][xw].draw = true;
				if(mainGmc2[i].fall == 2)
				{
					MaingmcDelete2();	// �����ɗ����Ă���u���b�N���ݒu�ς݂Ȃ����������s��
				}
			}
		}

		if (mainGmc2[i].fall == 1)
		{
			yh = mainGmc2[i].y / mainGmc2[i].h;					// �s�̐��l�ɕϊ�
			xw = (mainGmc2[i].x - leftMax) / mainGmc2[i].w;		// ��̐��l�ɕϊ�
			if (mainGmc2[i].y >= floor || blockcol[(mainGmc2[i].y + mainGmc2[i].h) / mainGmc2[i].h][(mainGmc2[i].x - leftMax + mainGmc2[i].w / 2) / mainGmc2[i].w] != 0)
			{	// �u���b�N���g�̈�ԉ��A�������̓u���b�N�����ɐݒu���Ă���ꏊ��œ��B�����Ƃ�
				mainGmc2[i].x = xw * mainGmc2[i].w + leftMax;	// X���W�̈ʒu���m��(��~�摜�̕�+���[�̐��l)
				mainGmc2[i].y = yh * mainGmc2[i].h;				// Y���W�̈ʒu���m��(�s�~�摜�̍���)
				mainGmc2[i].fall = 2;							// fall�̒l��2(�������Ȃ�)�ɕύX
				blockcol[yh][xw] = mainGmc2[i].rad;				// �u���b�N�̎�ނ�ۑ�
				mainGmc2[i].draw = false;						// mainGmc2��`�悵�Ȃ�

				stock--;										// �c��u���b�N�����炷

				// mainGmc2�̒��ɓ����Ă���ϐ������ׂĐݒu��̍\���̂֓����
				mainGmcMap[yh][xw].x = mainGmc2[i].x;
				mainGmcMap[yh][xw].y = mainGmc2[i].y;
				mainGmcMap[yh][xw].w = mainGmc2[i].w;
				mainGmcMap[yh][xw].h = mainGmc2[i].h;
				mainGmcMap[yh][xw].rad = mainGmc2[i].rad;
				mainGmcMap[yh][xw].graph = mainGmc2[i].graph;
				mainGmcMap[yh][xw].breakgraph = mainGmc2[i].breakgraph;
				mainGmcMap[yh][xw].draw = true;
				if(mainGmc1[i].fall == 2)
				{
					MaingmcDelete2();	// �����ɗ����Ă���u���b�N���ݒu�ς݂Ȃ����������s��
				}
			}
		}

		
	
		if ((mainGmc1[i].fall == 2 && mainGmc2[i].fall == 2) && (mainGmc1[i + 1].fall == 0 && mainGmc2[i + 1].fall == 0))
		{	// ���ݗ������Ă���u���b�N�̐ݒu���I�����A���̃u���b�N���ҋ@���Ȃ�A���̃u���b�N�𗎉�������
			mainGmc1[i + 1].fall = 1;
			mainGmc2[i + 1].fall = 1;
			mainGmc1[i + 1].draw = true;
			mainGmc2[i + 1].draw = true;
			break;
		}

	}
}

void MaingmcDraw()
{

	ClearDrawScreen();
	
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			DrawGraph(j * GRAPH_H + leftMax, i * GRAPH_H, mapImg[map[i][j]], TRUE);
		}
	}

	for (int i = 0; i < MAX_GRAPH; i++)
	{
		if (mainGmc1[i].draw == true)
		{
			DrawGraph(mainGmc1[i].x, mainGmc1[i].y, mainGmc1[i].graph, TRUE);
		}
		if (mainGmc2[i].draw == true)
		{
			DrawGraph(mainGmc2[i].x, mainGmc2[i].y, mainGmc2[i].graph, TRUE);
		}
	}

	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			if (mainGmcMap[i][j].draw == true)
			{
				DrawGraph(mainGmcMap[i][j].x, i * GRAPH_H, mainGmcMap[i][j].graph, TRUE);
			}
			if (mainGmcMap[i][j].breakdraw == true)
			{
				DrawGraph(mainGmcMap[i][j].x, i * GRAPH_H, mainGmcMap[i][j].breakgraph, TRUE);
			}
		}
	}


	TextDraw();	//�����̕`��

	ScreenFlip();
}

void MaingmcPause()
{
	while (1)
	{
		if (CheckHitKey(KEY_INPUT_W))
		{
			break;
		}
	}
}

void MaingmcDelete2()
{
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			if (blockcol[i][j] != 0)
			{	// �u���b�N���ݒu���Ă����
				if (cntup = CheckLinkRIGHT(j, i, blockcol) >= 3)
				{	// ����3�ȏ㓯���F�������
					mainGmcMap[i][j].draw = false;		// �ʏ�`������Ȃ�
					mainGmcMap[i][j].breakdraw = true;	// �j�󎞂̕`�������
				}
				if(cntup = CheckLinkUP(j, i, blockcol) >= 3)
				{	// �c��3�ȏ㓯���F�������
					mainGmcMap[i][j].draw = false;		// �ʏ�`������Ȃ�
					mainGmcMap[i][j].breakdraw = true;	// �j�󎞂̕`�������
				}
			}
		}
	}
	for (int i = MAP_Y - 1; i > 0 ; i--)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			if (mainGmcMap[i][j].draw == false)
			{
				blockcol[i][j] = 0;	// �ݒu����Ă��Ȃ��ꏊ������
			}
		}
	}

	MaingmcDraw();

	WaitTimer(300);

	loop = false;

	for (int i = MAP_Y - 1; i > 0; i--)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			if (mainGmcMap[i][j].draw == false)
			{	
				FallGraph(mainGmcMap, blockcol, i, j);		// �u���b�N�̉��ɋ󔒂�����Ή��ɗ��Ƃ�
				if (cntup = CheckLinkRIGHT(j, i, blockcol) >= 3 && blockcol[i][j] != 0)
				{	// ���Ƃ�����ɉ���3�ȏ�Ȃ����Ă���ꏊ�������
					loop = true;
				}
				if (cntup = CheckLinkUP(j, i, blockcol) >= 3 && blockcol[i][j] != 0)
				{	// ���Ƃ�����ɏc��3�ȏ�Ȃ����Ă���ꏊ�������
					loop = true;
				}
			}
		}
	}

	if (loop == true)
	{
		WaitTimer(300);
		MaingmcDelete2();	// ������x���̊֐�����
	}

	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			mainGmcMap[i][j].breakdraw = false;
		}
	}

}

void Shuffle(Maingmc *p, Maingmc *p2)
{
	// S�������ꂽ��㉺�̐F��ς���
	backup.rad = p->rad;
	backup.graph = blockImg[p->rad - 1];
	backup.breakgraph = blockBreakImg[p->rad - 1];

	p->rad = p2->rad;
	p->graph = blockImg[p2->rad - 1];
	p->breakgraph = blockBreakImg[p2->rad - 1];

	p2->rad = backup.rad;
	p2->graph = blockImg[backup.rad - 1];
	p2->breakgraph = blockBreakImg[backup.rad - 1];
}

void TextDraw()
{
	// �e�L�X�g�̕`��(���搶�̃e�L�X�g�`��֐������p)

	char buf[128];
	if(stock >= 0)
	{
		sprintf(buf, "stock : %d", stock);
	}
	else
	{
		sprintf(buf, "stock : %d", 0);
	}

	text.setFontColor(255, 0, 0);
	text.setFontColorShadow(0, 255, 0);
	text.setFontShadowOffset(3, 3);
	text.textDraw(20, 100, buf);

}


void GameTitle(int *check, int push)
{
	if (CheckHitKey(KEY_INPUT_ESCAPE))		// �d�r�b�L�[��������Ă����烋�[�v���甲����
	{
		*check = END;
	}
	if (ProcessMessage() != 0)
	{
		*check = END;
	}
	//�`�揉����
	ClearDrawScreen();

	DrawGraph(0, 0, TitleImage, TRUE);

	//text.setFontColor(255, 0, 0);
	//text.setFontColorShadow(0, 255, 0);
	//text.setFontShadowOffset(3, 3);
	//textjp.setFontColor(255, 255, 0);
	//textjp.textDraw(20, 100, "����������");
	//text.textDraw(20, 100, "enta-woositene");
	
	if (CheckHitKey(KEY_INPUT_RETURN) && push == 1)
	{
		//���^�[���L�[�ŊJ�n
		*check = PLAY;
	}

	//��ʍX�V����
	ScreenFlip();
}

void GamePlay(int * check)
{
	if (blockcol[0][2] != 0)
	{
		*check = RESULT;
	}
	if (stock < 0)
	{
		*check = RESULT;
	}
}

void GameEnd(int * check, int push)
{
	if (CheckHitKey(KEY_INPUT_ESCAPE))		// �d�r�b�L�[��������Ă����烋�[�v���甲����
	{
		*check = END;
	}
	if (ProcessMessage() != 0)
	{
		*check = END;
	}
	//�`�揉����
	ClearDrawScreen();

	if (stock > 0)
	{
		scorecnt = MAX_GRAPH * 2 - stock - 2;
	}
	else
	{
		scorecnt = MAX_GRAPH * 2;
	}

	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			if (blockcol[i][j] != 0)
			{
				scorecnt--;
			}
		}
	}

	DrawGraph(0, 0, ResultImg, TRUE);

	char buf[128];
	sprintf(buf, "score : %d", scorecnt * 100);

	text.setFontColor(255, 0, 0);
	text.setFontColorShadow(0, 255, 0);
	text.setFontShadowOffset(3, 3);
	text.textDraw(20, 100, buf);

	//text.setFontColor(0, 0, 255);
	//text.setFontColorShadow(255, 255, 255);
	//text.setFontShadowOffset(3, 3);
	//text.textDraw(20, 400, "enta-woositene");

	if (CheckHitKey(KEY_INPUT_RETURN) && push == 1)
	{
		//���^�[���L�[�ŊJ�n
		*check = TITLE;
	}

	//��ʍX�V����
	ScreenFlip();
}