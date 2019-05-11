#include "DxLib.h"
#include "common.h"
#include "MainGimmick.h"
#include "bitmapText.h"

int status = TITLE;
int push;

// �����`���[(Launcher.exe)�Ăяo���֐� 
// path�ɂ�Launcher.exe�ւ̑��΃p�X�ւ̕����������
void runLauncher(const char* path)
{

	char fullPathexe[512];
#pragma warning (disable:4996)
	sprintf(fullPathexe, "%s%s", path, "Launcher.exe");

	// �v���Z�X�N������
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);

	CreateProcess(fullPathexe, (LPSTR)"" , NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, path, &si, &pi);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	bool gameloop = true;		//�Q�[�����s��Ԃ��Ǘ�(1=�Q�[�����s���A0=�Q�[���I��)

	SetDrawScreen(DX_SCREEN_BACK);		// �`���𗠉�ʂɐݒ�

	while (gameloop)
	{

		Maingmc_Init();	//�u���b�N���̏�����

		//Test_Debug();

		
		while (status == TITLE)
		{

			if (CheckHitKey(KEY_INPUT_RETURN))
			{
				push++;
			}
			else
			{
				push = 0;
			}

			Game_Title(&status, push);
		}
		

		while (status == PLAY)
		{
			if (CheckHitKey(KEY_INPUT_ESCAPE))		// �d�r�b�L�[��������Ă����烋�[�v���甲����
			{
				status = END;
			}

			if (ProcessMessage() != 0)
			{
				status = END;
			}

			if (CheckHitKey(KEY_INPUT_P))			// �o��������Ă������~�i�v�ŉ����j
			{
				Maingmc_Pause();
			}

			Maingmc_Update();	// �u���b�N���̍X�V

			Maingmc_HitCheck();	//�u���b�N���m�̓����蔻��


			Maingmc_Draw();	//�u���b�N�̕`��

			//Maingmc_Delete();

			Game_Play(&status);
		}

		while (status == RESULT)
		{

			if (CheckHitKey(KEY_INPUT_RETURN))
			{
				push++;
			}
			else
			{
				push = 0;
			}

			Game_End(&status, push);
		}

		if (status == END)
		{
			break;
		}
	}
		DxLib_End();				// �c�w���C�u�����g�p�̏I������
		runLauncher("../../");
	return 0;				// �\�t�g�̏I�� 
}