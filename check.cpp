#include "MainGimmick.h"

int checkmap[MAP_Y][MAP_X] = { 0 };


int Check_Link_RIGHT(int x, int y, int num[][MAP_X])
{
	int right = x + 1;
	int left = x - 1;
	int up = y - 1;
	int down = y + 1;

	int cnt = 1;
	checkmap[y][x] = 1;
	if (num[y][x] == num[y][right] && checkmap[y][right] == 0)
	{
		cnt++;
		cnt = Check_Link_RIGHT2(right, y, num, cnt);
	}
	if (num[y][x] == num[down][x] && checkmap[down][x] == 0)
	{
		cnt++;
		cnt = Check_Link_DOWN(x, down, num, cnt);
	}
	if (num[y][x] == num[up][x] && checkmap[up][x] == 0)
	{
		cnt++;
		cnt = Check_Link_UP(x, up, num, cnt);
	}
	if (num[y][x] == num[y][left] && checkmap[y][left] == 0)
	{
		cnt++;
		cnt = Check_Link_LEFT(left, y, num, cnt);
	}
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			checkmap[i][j] = 0;
		}
	}
	return cnt;
}

int Check_Link_RIGHT2(int x, int y, int num[][MAP_X], int cnt)
{
	int right = x + 1;
	int up = y - 1;
	int down = y + 1;

	checkmap[y][x] = 1;
	if (num[y][x] == num[y][right] && checkmap[y][right] == 0)
	{
		cnt++;
		cnt = Check_Link_RIGHT2(right, y, num, cnt);
	}
	if (num[y][x] == num[down][x] && checkmap[down][x] == 0)
	{
		cnt++;
		cnt = Check_Link_DOWN(x, down, num, cnt);
	}
	if (num[y][x] == num[up][x] && checkmap[up][x] == 0)
	{
		cnt++;
		cnt = Check_Link_UP(x, up, num, cnt);
	}
	return cnt;
}

int Check_Link_LEFT(int x, int y, int num[][MAP_X], int cnt)
{
	int left = x - 1;
	int up = y - 1;
	int down = y + 1;

	checkmap[y][x] = 1;
	if (num[y][x] == num[down][x] && checkmap[down][x] == 0)
	{
		cnt++;
		cnt = Check_Link_DOWN(x, down, num, cnt);
	}
	if (num[y][x] == num[up][x] && checkmap[up][x] == 0)
	{
		cnt++;
		cnt = Check_Link_UP(x, up, num, cnt);
	}
	if (num[y][x] == num[y][left] && checkmap[y][left] == 0)
	{
		cnt++;
		cnt = Check_Link_LEFT(left, y, num, cnt);
	}
	return cnt;
}

int Check_Link_UP(int x, int y, int num[][MAP_X], int cnt)
{
	int right = x + 1;
	int left = x - 1;
	int up = y - 1;

	checkmap[y][x] = 1;
	if (num[y][x] == num[y][right] && checkmap[y][right] == 0)
	{
		cnt++;
		cnt = Check_Link_RIGHT2(right, y, num, cnt);
	}
	if (num[y][x] == num[up][x] && checkmap[up][x] == 0)
	{
		cnt++;
		cnt = Check_Link_UP(x, up, num, cnt);
	}
	if (num[y][x] == num[y][left] && checkmap[y][left] == 0)
	{
		cnt++;
		cnt = Check_Link_LEFT(left, y, num, cnt);
	}
	return cnt;
}

int Check_Link_DOWN(int x, int y, int num[][MAP_X], int cnt)
{
	int right = x + 1;
	int left = x - 1;
	int down = y + 1;

	checkmap[y][x] = 1;
	if (num[y][x] == num[y][right] && checkmap[y][right] == 0)
	{
		cnt++;
		cnt = Check_Link_RIGHT2(right, y, num, cnt);
	}
	if (num[y][x] == num[down][x] && checkmap[down][x] == 0)
	{
		cnt++;
		cnt = Check_Link_DOWN(x, down, num, cnt);
	}
	if (num[y][x] == num[y][left] && checkmap[y][left] == 0)
	{
		cnt++;
		cnt = Check_Link_LEFT(left, y, num, cnt);
	}
	return cnt;
}

