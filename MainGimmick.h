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
void MaingmcInit();
//アップデート
void MaingmcUpdate();
//ブロックの状態更新
void MaingmcHitCheck();
//描画
void MaingmcDraw();
//ポーズ機能
void MaingmcPause();
//ブロックを消す機能
void MaingmcDelete2();

int CheckLinkRIGHT(int x, int y, int num[][MAP_X]);					//右側の隣接判定(1回目)
int CheckLinkRIGHT2(int x, int y, int num[][MAP_X], int cnt);		//右側の隣接判定(2回目以降)
int CheckLinkLEFT(int x, int y, int num[][MAP_X], int cnt);			//左側の隣接判定
//int CheckLinkUP(int x, int y, int num[][MAP_X], int cnt);
int CheckLinkUP(int x, int y, int num[][MAP_X]);					//上の隣接判定(1回目)
int	CheckLinkUP2(int x, int y, int num[][MAP_X], int cnt);			//上の隣接判定(2回目以降)
int CheckLinkDOWN(int x, int y, int num[][MAP_X], int cnt);			//下の隣接判定

void FallGraph(Maingmc p[][MAP_X], int num[][MAP_X], int y, int x);	//消した後に上のブロックを落とす関数

void Shuffle(Maingmc *p, Maingmc *p2);								//Sを押したら上下を入れ替える関数

void TextDraw();													//文字の描画


void GameTitle(int *check, int push);	//タイトル画面
void GamePlay(int *check);				//プレイ中の画面
void GameEnd(int *check, int push);		//リザルト画面

//void Test_Debug();