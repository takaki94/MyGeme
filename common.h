#pragma once
#include "DxLib.h"

#define MAX_GRAPH	36	//ブロック配列の最大量
#define GRAPH_H		32	//画像の高さ
#define GRAPH_W		32	//画像の幅
#define MAP_X		 6	//マップX軸の数
#define MAP_Y		12	//マップY軸の数


const int grv = 1;			//基本重力
const int moveSpd = 2;		//左右移動時の速さ
const int leftmax = 192;	//左端
const int rightmax = 352;	//右端

enum { TITLE, PLAY, RESULT, END };