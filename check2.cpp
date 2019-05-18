#include "MainGimmick.h"

int checkmap[MAP_Y][MAP_X] = { 0 };


int CheckLinkRIGHT(int x, int y, int num[][MAP_X])
{
	int right = x + 1;
	int left = x - 1;

	int cnt = 1;
	checkmap[y][x] = 1;
	if (right < MAP_X)
	{
		if (num[y][x] == num[y][right] && checkmap[y][right] == 0)
		{
			cnt++;
			cnt = CheckLinkRIGHT2(right, y, num, cnt);
		}
	}
	if (left >= 0)
	if (num[y][x] == num[y][left] && checkmap[y][left] == 0)
	{
		cnt++;
		cnt = CheckLinkLEFT(left, y, num, cnt);
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

int CheckLinkRIGHT2(int x, int y, int num[][MAP_X], int cnt)
{
	int right = x + 1;

	checkmap[y][x] = 1;
	if (right < MAP_X)
	{
		if (num[y][x] == num[y][right] && checkmap[y][right] == 0)
		{
			cnt++;
			cnt = CheckLinkRIGHT2(right, y, num, cnt);
		}
	}
	return cnt;
}

int CheckLinkLEFT(int x, int y, int num[][MAP_X], int cnt)
{
	int left = x - 1;

	checkmap[y][x] = 1;
	if (left >= 0)
	{
		if (num[y][x] == num[y][left] && checkmap[y][left] == 0)
		{
			cnt++;
			cnt = CheckLinkLEFT(left, y, num, cnt);
		}
	}
	return cnt;
}


int CheckLinkUP(int x, int y, int num[][MAP_X])
{
	int cnt = 1;

	int up = y - 1;
	int down = y + 1;

	checkmap[y][x] = 1;
	if (up >= 0)
	{
		if (num[y][x] == num[up][x] && checkmap[up][x] == 0)
		{
			cnt++;
			cnt = CheckLinkUP2(x, up, num, cnt);
		}
	}
	if (down < MAP_Y)
	{
		if (num[y][x] == num[down][x] && checkmap[down][x] == 0)
		{
			cnt++;
			cnt = CheckLinkDOWN(x, down, num, cnt);
		}
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

int CheckLinkUP2(int x, int y, int num[][MAP_X], int cnt)
{
	int up = y - 1;

	checkmap[y][x] = 1;
	if (up >= 0)
	{
		if (num[y][x] == num[up][x] && checkmap[up][x] == 0)
		{
			cnt++;
			cnt = CheckLinkUP2(x, up, num, cnt);
		}
	}

	return cnt;
}

int CheckLinkDOWN(int x, int y, int num[][MAP_X], int cnt)
{
	int down = y + 1;

	checkmap[y][x] = 1;
	if (down < MAP_Y)
	{
		if (num[y][x] == num[down][x] && checkmap[down][x] == 0)
		{
			cnt++;
			cnt = CheckLinkDOWN(x, down, num, cnt);
		}
	}

	return cnt;
}

