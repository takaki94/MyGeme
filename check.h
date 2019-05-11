#pragma once
#include "MainGimmick.h"

int Check_Link(int x, int y, char* num[])
{
	int cnt = 0;
	if (num[y][x] == num[y][x + 1])
	{
		cnt++;
		Check_Link(y, x, num);
	}
	return cnt;
}