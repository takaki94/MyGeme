#pragma once
#include "DxLib.h"
#include "common.h"

typedef struct Maingmc
{
	int x;
	int y;
	int w;
	int h;
	int graph;		// ブロック画像
	int breakgraph;	// 壊れたブロック画像
	int fall;		// ブロックの状態を管理(0=待機,1=実行,2=終了)
	int rad;		// ランダムな数値を入れる
	bool draw;		// 描画するかしないか
	bool breakdraw;	// 壊れた時の描画をするかしないか
}Maingmc;

//初期化
void Maingmc_Init();
//アップデート
void Maingmc_Update();
//ブロックの状態更新
void Maingmc_HitCheck();
//描画
void Maingmc_Draw();
//ポーズ機能
void Maingmc_Pause();
//ブロックを消す機能
void Maingmc_Delete2();

int Check_Link_RIGHT(int x, int y, int num[][MAP_X]);			//右側の隣接判定(1回目)
int Check_Link_RIGHT2(int x, int y, int num[][MAP_X], int cnt);	//右側の隣接判定(2回目以降)
int Check_Link_LEFT(int x, int y, int num[][MAP_X], int cnt);	//左側の隣接判定
//int Check_Link_UP(int x, int y, int num[][MAP_X], int cnt);
int Check_Link_UP(int x, int y, int num[][MAP_X]);				//上の隣接判定(1回目)
int	Check_Link_UP2(int x, int y, int num[][MAP_X], int cnt);	//上の隣接判定(2回目以降)
int Check_Link_DOWN(int x, int y, int num[][MAP_X], int cnt);	//下の隣接判定

void Fall_Graph(Maingmc p[][MAP_X], int num[][MAP_X], int y, int x);	//消した後に上のブロックを落とす関数

void Shuffle(Maingmc *p, Maingmc *p2);	//Sを押したら上下を入れ替える関数

void Text_Draw();	//文字の描画


void Game_Title(int *check, int push);	//タイトル画面
void Game_Play(int *check);				//プレイ中の画面
void Game_End(int *check, int push);	//リザルト画面

//void Test_Debug();