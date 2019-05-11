#include "DxLib.h"
#include "common.h"
#include "MainGimmick.h"
#include "bitmapText.h"

int status = TITLE;	// statusをTITLEに設定(TITLE,PLAY,RESLT,END)
int push;			// ボタンを押したらカウントする変数

//// ランチャー(Launcher.exe)呼び出し関数 
//// pathにはLauncher.exeへの相対パスへの文字列を入れる
//void runLauncher(const char* path)
//{
//
//	char fullPathexe[512];
//#pragma warning (disable:4996)
//	sprintf(fullPathexe, "%s%s", path, "Launcher.exe");
//
//	// プロセス起動準備
//	PROCESS_INFORMATION pi = { 0 };
//	STARTUPINFO si = { 0 };
//	si.cb = sizeof(STARTUPINFO);
//
//	CreateProcess(fullPathexe, (LPSTR)"" , NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, path, &si, &pi);
//}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(FALSE);		// フルスクリーン

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	bool gameloop = true;		//ゲーム実行状態を管理(1=ゲーム実行中、0=ゲーム終了)

	SetDrawScreen(DX_SCREEN_BACK);		// 描画先を裏画面に設定

	while (gameloop)
	{

		Maingmc_Init();	//ブロック情報の初期化

		//Test_Debug();

		
		while (status == TITLE)		//statusがTITLEなら実行
		{

			if (CheckHitKey(KEY_INPUT_RETURN))
			{
				push++;		// エンターを押したらpushに1を足す
			}
			else
			{
				push = 0;	// エンターを押していなければ0にする
			}

			Game_Title(&status, push);
			// ゲームタイトル読み込み、エンターを押しているか押していないかを渡す
		}
		

		while (status == PLAY)
		{
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				status = END;		// ＥＳＣキーが押されていたらループから抜ける
			}

			if (ProcessMessage() != 0)
			{
				status = END;
			}

			if (CheckHitKey(KEY_INPUT_P))			// Ｐが押されていたら停止（Ｗで解除）
			{
				Maingmc_Pause();
			}

			Maingmc_Update();	// ブロック情報の更新

			Maingmc_HitCheck();	//ブロック同士の当たり判定


			Maingmc_Draw();	//ブロックの描画

			//Maingmc_Delete();

			Game_Play(&status);	// ゲームステータス判定
		}

		while (status == RESULT)
		{

			if (CheckHitKey(KEY_INPUT_RETURN))
			{
				push++;		// エンターを押したらpushに1を足す
			}
			else
			{
				push = 0;	// エンターを押していなければ0にする
			}

			Game_End(&status, push);
			// リザルト画面読み込み、エンターを押しているか押していないかを渡す
		}

		if (status == END)
		{
			break;		// statusがENDなら、ゲームループを抜ける
		}
	}
		DxLib_End();				// ＤＸライブラリ使用の終了処理
		//runLauncher("../../");
	return 0;				// ソフトの終了 
}