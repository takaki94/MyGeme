#include "common.h"
#include "MainGimmick.h"
#include "bitmapText.h"
#pragma warning(disable:4996)

Maingmc mainGmc1[MAX_GRAPH];		// ブロック1
Maingmc mainGmc2[MAX_GRAPH];		// ブロック2
Maingmc mainGmcMap[MAP_Y][MAP_X];	// 設置後のブロック
Maingmc backup;						// ブロック順序入れ替え用
int blockImg[5];					//ブロック画像
int blockBreakImg[5];				//ブロックが壊れた時の画像
int mapImg[9];						//背景マップの画像

//背景マップ配列
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

int blockcol[MAP_Y][MAP_X] = { 0 };	//ブロックの種類を保存する配列
int pushkey = 0;					//キーを押しているか判定する
int pushkey2 = 0;					//キーを押しているか判定する2
int cntup = 0;						//隣接チェックの関数結果を一時的に保存する
int yh;								//yとhをかけた数値を保存
int xw;								//xとwをかけた数値を保存
bool loop = false;					//消す判定を繰り返すかどうかの判定

BitmapText text;					// テキスト用
//BitmapText textjp;

int stock = MAX_GRAPH * 2;			//残りブロックのカウント

int scorecnt = 0;					//スコア

int TitleImage;						//タイトル画面の画像
int ResultImg;						//リザルト画面の画像

void MaingmcInit()
{
	//画像を読み込み
	LoadDivGraph("image/test2.png", 5, 5, 1, 32, 32, blockImg);
	LoadDivGraph("image/test2break.png", 5, 5, 1, 32, 32, blockBreakImg);
	LoadDivGraph("image/mapchip.png", 9, 3, 3, 32, 32, mapImg);
	TitleImage = LoadGraph("image/testtitle2.png");
	ResultImg = LoadGraph("image/END.png");

	for (int i = 0; i < MAX_GRAPH; i++)
	{
		//0~4をランダムに取得
		mainGmc1[i].rad = GetRand(4);
		//初期座標
		mainGmc1[i].x = 256;
		mainGmc1[i].y = 0;
		//画像rad(0~4)をgraphに入れる
		mainGmc1[i].graph = blockImg[mainGmc1[i].rad];
		mainGmc1[i].breakgraph = blockBreakImg[mainGmc1[i].rad];
		//画像のHとWを取得
		GetGraphSize(mainGmc1[i].graph, &mainGmc1[i].w, &mainGmc1[i].h);
		//ブロックの状態をすべて待機状態(0)にする
		mainGmc1[i].fall = 0;
		//radが０にならないように１プラスする
		mainGmc1[i].rad++;
		//描画するかしないか
		mainGmc1[i].draw = false;
	}
	for (int i = 0; i < MAX_GRAPH; i++)
	{
		//0~4をランダムに取得
		mainGmc2[i].rad = GetRand(4);
		//初期座標
		mainGmc2[i].x = 256;
		mainGmc2[i].y = -32;
		//画像rad(0~4)をgraphに入れる
		mainGmc2[i].graph = blockImg[mainGmc2[i].rad];
		mainGmc2[i].breakgraph = blockBreakImg[mainGmc2[i].rad];
		//画像のHとWを取得
		GetGraphSize(mainGmc2[i].graph, &mainGmc2[i].w, &mainGmc2[i].h);
		//ブロックの状態をすべて待機状態(0)にする
		mainGmc2[i].fall = 0;
		//radが０にならないように１プラスする
		mainGmc2[i].rad++;
		//描画するかしないか
		mainGmc2[i].draw = false;
	}

	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			// すべて初期化
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

	// 最初のブロックを落下可能状態に
	mainGmc1[0].fall = 1;
	mainGmc2[0].fall = 1;
	mainGmc1[0].draw = true;
	mainGmc2[0].draw = true;
	// 残りブロック数の初期化
	stock = MAX_GRAPH * 2 - 2;

	// テキスト画像読み込み
	text.setFontImage(16, 6, "image/font.bmp");
	text.reMapText(" !\"#$%%'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\tabcdefghijklmnopqrstuvwxyz{|}\\");

}

void MaingmcUpdate()
{
	for (int i = 0; i < MAX_GRAPH; i++)
	{
		if (mainGmc1[i].fall == 1)
		{
			mainGmc1[i].y += grv;		// ブロックを落下
		}
		if (mainGmc2[i].fall == 1)
		{
			mainGmc2[i].y += grv;		// ブロックを落下
		}
		if (mainGmc1[i].fall == 1 && mainGmc2[i].fall == 1)
		{
			if (mainGmc1[i].fall == 1 && mainGmc2[i].fall == 1) 
			{
				// 矢印キーを押していたらプレイヤーを移動させる
				if (CheckHitKey(KEY_INPUT_DOWN) == 1)
				{
					mainGmc1[i].y += grv;
					mainGmc2[i].y += grv;
				}
				if (CheckHitKey(KEY_INPUT_LEFT) == 1)
				{
					pushkey++;
					//左キーを押された瞬間のみ
					if (pushkey == 1)
					{
						for (int j = 0; j < mainGmc1[i].w / moveSpd; j++)
						{
							mainGmc1[i].x -= moveSpd;
							mainGmc2[i].x -= moveSpd;
						}
					}
					//もし左端まで到達したら
					if (mainGmc1[i].x <= leftMax)
					{
						mainGmc1[i].x = leftMax;
					}
					//もし左端まで到達したら
					if (mainGmc2[i].x <= leftMax)
					{
						mainGmc2[i].x = leftMax;
					}
					//もし左側に既にブロックがあったら
					if (blockcol[mainGmc1[i].y / mainGmc1[i].h][mainGmc1[i].x / mainGmc1[i].w] != 0)
					{
						mainGmc1[i].x = (mainGmc1[i].x / mainGmc1[i].w + 1) * mainGmc1[i].w;
					}
					//もし左側に既にブロックがあったら
					if (blockcol[mainGmc2[i].y / mainGmc2[i].h][mainGmc2[i].x / mainGmc2[i].w] != 0)
					{
						mainGmc2[i].x = (mainGmc2[i].x / mainGmc2[i].w + 1) * mainGmc2[i].w;
					}
				}
				if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
				{
					pushkey++;
					//右キーを押された瞬間のみ
					if (pushkey == 1)
					{
						for (int j = 0; j < mainGmc1[i].w / moveSpd; j++)
						{
							mainGmc1[i].x += moveSpd;
							mainGmc2[i].x += moveSpd;
						}
					}
					//もし右端まで到達したら
					if (mainGmc1[i].x >= rightMax)
					{
						mainGmc1[i].x = rightMax;
					}
					//もし右端まで到達したら
					if (mainGmc2[i].x >= rightMax)
					{
						mainGmc2[i].x = rightMax;
					}
					//もし右側に既にブロックがあったら
					if (blockcol[mainGmc1[i].y / mainGmc1[i].h][mainGmc1[i].x / mainGmc1[i].w] != 0)
					{
						mainGmc1[i].x = (mainGmc1[i].x / mainGmc1[i].w - 1) * mainGmc1[i].w;
					}
					//もし右側に既にブロックがあったら
					if (blockcol[mainGmc2[i].y / mainGmc2[i].h][mainGmc2[i].x / mainGmc2[i].w] != 0)
					{
						mainGmc2[i].x = (mainGmc2[i].x / mainGmc2[i].w - 1) * mainGmc2[i].w;
					}
				}
				else if (CheckHitKey(KEY_INPUT_LEFT) != 1 && CheckHitKey(KEY_INPUT_RIGHT) != 1)
				{
					// どちらのキーも押されていない場合、pushkeyをリセット
					pushkey = 0;
				}

				if (CheckHitKey(KEY_INPUT_S) == 1)
				{
					// Sキーが押されていれば
					pushkey2++;
					if (pushkey2 == 1)
					{
						// pushkey2が1の場合にブロックを入れ替える
						Shuffle(&mainGmc1[i], &mainGmc2[i]);
					}
				}
				else
				{
					// Sキーが押されていなければリセット
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
			yh = mainGmc1[i].y / mainGmc1[i].h;					// 行の数値に変換
			xw = (mainGmc1[i].x - leftMax) / mainGmc1[i].w;		// 列の数値に変換
			if (mainGmc1[i].y >= floor || blockcol[(mainGmc1[i].y + mainGmc1[i].h) / mainGmc1[i].h][(mainGmc1[i].x - leftMax + mainGmc1[i].w / 2) / mainGmc1[i].w] != 0)
			{	// ブロックが枠の一番下、もしくはブロックが既に設置してある場所場で到達したとき
				mainGmc1[i].x = xw * mainGmc1[i].w + leftMax;	// X座標の位置を確定(列×画像の幅+左端の数値)
				mainGmc1[i].y = yh * mainGmc1[i].h;				// Y座標の位置を確定(行×画像の高さ)
				mainGmc1[i].fall = 2;							// fallの値を2(落下しない)に変更
				blockcol[yh][xw] = mainGmc1[i].rad;				// ブロックの種類を保存
				mainGmc1[i].draw = false;						// mainGmc1を描画しない

				stock--;										// 残りブロックを減らす

				// mainGmc1の中に入っている変数をすべて設置後の構造体へ入れる
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
					MaingmcDelete2();	// 同時に落ちているブロックも設置済みなら消去判定を行う
				}
			}
		}

		if (mainGmc2[i].fall == 1)
		{
			yh = mainGmc2[i].y / mainGmc2[i].h;					// 行の数値に変換
			xw = (mainGmc2[i].x - leftMax) / mainGmc2[i].w;		// 列の数値に変換
			if (mainGmc2[i].y >= floor || blockcol[(mainGmc2[i].y + mainGmc2[i].h) / mainGmc2[i].h][(mainGmc2[i].x - leftMax + mainGmc2[i].w / 2) / mainGmc2[i].w] != 0)
			{	// ブロックが枠の一番下、もしくはブロックが既に設置してある場所場で到達したとき
				mainGmc2[i].x = xw * mainGmc2[i].w + leftMax;	// X座標の位置を確定(列×画像の幅+左端の数値)
				mainGmc2[i].y = yh * mainGmc2[i].h;				// Y座標の位置を確定(行×画像の高さ)
				mainGmc2[i].fall = 2;							// fallの値を2(落下しない)に変更
				blockcol[yh][xw] = mainGmc2[i].rad;				// ブロックの種類を保存
				mainGmc2[i].draw = false;						// mainGmc2を描画しない

				stock--;										// 残りブロックを減らす

				// mainGmc2の中に入っている変数をすべて設置後の構造体へ入れる
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
					MaingmcDelete2();	// 同時に落ちているブロックも設置済みなら消去判定を行う
				}
			}
		}

		
	
		if ((mainGmc1[i].fall == 2 && mainGmc2[i].fall == 2) && (mainGmc1[i + 1].fall == 0 && mainGmc2[i + 1].fall == 0))
		{	// 現在落下しているブロックの設置が終了し、次のブロックが待機中なら、次のブロックを落下させる
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


	TextDraw();	//文字の描画

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
			{	// ブロックが設置してあれば
				if (cntup = CheckLinkRIGHT(j, i, blockcol) >= 3)
				{	// 横に3個以上同じ色があれば
					mainGmcMap[i][j].draw = false;		// 通常描画をしない
					mainGmcMap[i][j].breakdraw = true;	// 破壊時の描画をする
				}
				if(cntup = CheckLinkUP(j, i, blockcol) >= 3)
				{	// 縦に3個以上同じ色があれば
					mainGmcMap[i][j].draw = false;		// 通常描画をしない
					mainGmcMap[i][j].breakdraw = true;	// 破壊時の描画をする
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
				blockcol[i][j] = 0;	// 設置されていない場所を消去
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
				FallGraph(mainGmcMap, blockcol, i, j);		// ブロックの下に空白があれば下に落とす
				if (cntup = CheckLinkRIGHT(j, i, blockcol) >= 3 && blockcol[i][j] != 0)
				{	// 落とした後に横に3個以上つながっている場所があれば
					loop = true;
				}
				if (cntup = CheckLinkUP(j, i, blockcol) >= 3 && blockcol[i][j] != 0)
				{	// 落とした後に縦に3個以上つながっている場所があれば
					loop = true;
				}
			}
		}
	}

	if (loop == true)
	{
		WaitTimer(300);
		MaingmcDelete2();	// もう一度この関数を回す
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
	// Sが押されたら上下の色を変える
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
	// テキストの描画(矢野先生のテキスト描画関数を引用)

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
	if (CheckHitKey(KEY_INPUT_ESCAPE))		// ＥＳＣキーが押されていたらループから抜ける
	{
		*check = END;
	}
	if (ProcessMessage() != 0)
	{
		*check = END;
	}
	//描画初期化
	ClearDrawScreen();

	DrawGraph(0, 0, TitleImage, TRUE);

	//text.setFontColor(255, 0, 0);
	//text.setFontColorShadow(0, 255, 0);
	//text.setFontShadowOffset(3, 3);
	//textjp.setFontColor(255, 255, 0);
	//textjp.textDraw(20, 100, "あいうえお");
	//text.textDraw(20, 100, "enta-woositene");
	
	if (CheckHitKey(KEY_INPUT_RETURN) && push == 1)
	{
		//リターンキーで開始
		*check = PLAY;
	}

	//画面更新処理
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
	if (CheckHitKey(KEY_INPUT_ESCAPE))		// ＥＳＣキーが押されていたらループから抜ける
	{
		*check = END;
	}
	if (ProcessMessage() != 0)
	{
		*check = END;
	}
	//描画初期化
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
		//リターンキーで開始
		*check = TITLE;
	}

	//画面更新処理
	ScreenFlip();
}