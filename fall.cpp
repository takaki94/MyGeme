#include "MainGimmick.h"

void FallGraph(Maingmc p[][MAP_X], int num[][MAP_X], int y, int x)
{
	int cnt = 0;
	int yi = 0;
	while (yi < y && num[y - yi][x] == 0)
	{
		cnt++;
		yi++;
	}

	num[y][x] = num[y - yi][x];
	num[y - yi][x] = 0;
	p[y][x].x = p[y - yi][x].x;
	p[y][x].y = p[y - yi][x].y + p[y - yi][x].h;
	p[y][x].w = p[y - yi][x].w;
	p[y][x].h = p[y - yi][x].h;
	p[y][x].fall = p[y - yi][x].fall;
	p[y][x].rad = p[y - yi][x].rad;
	p[y][x].graph = p[y - yi][x].graph;
	p[y][x].breakgraph = p[y - yi][x].breakgraph;
	p[y][x].draw = p[y - yi][x].draw;
	p[y][x].breakdraw = p[y - yi][x].breakdraw;

	p[y - yi][x].x = 0;
	p[y - yi][x].y = 0;
	p[y - yi][x].w = 0;
	p[y - yi][x].h = 0;
	p[y - yi][x].fall = 2;
	p[y - yi][x].rad = 0;
	p[y - yi][x].graph = 0;
	p[y - yi][x].breakgraph = 0;
	p[y - yi][x].draw = false;
	p[y - yi][x].breakdraw = false;
}