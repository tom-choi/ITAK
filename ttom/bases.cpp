void anime_g(int a[11][13],int n, int i, int color, int colnow)
{
	int times, j;
	for (times = (i - n) * 4; times > 0; times--)
	{
		cct_setcolor(15, 15);
		for (j = 0; j < 3; j++)
		{
			cct_gotoxy(4 + (colnow - 1) * 8, 3 + (i - 1) * 4 - times + j);
			cout << "      ";
		}

		cct_setcolor(color, 0);
		for (j = 0; j < 3; j++)
		{
			cct_gotoxy(4 + (colnow - 1) * 8, 4 + (i - 1) * 4 - times + j);
			if (j == 0)
				cout << "┏" << "━" << "┓";
			else if (j == 1)
				cout << "┃" << /*"★"*/a[i][colnow] << "┃";
			else
				cout << "┗" << "━" << "┛";
		}
		if ((times - 1) % 4 == 0)
		{
			cct_setcolor(15, 0);
			cct_gotoxy(4 + (colnow - 1) * 8, 3 + (i - 1) * 4 - times);
			cout << "━━━";
		}
		Sleep(1);
	}
	Sleep(1);
}

void anime_moveleft_g(int n, int j, int color, int rownow)
{
	int times, i;
	for (times = (j - n) * 8; times > 0; times--)
	{
		cct_setcolor(15, 15);
		cct_setcolor(15, 0);
for (i = 0; i < 3; i++)
{
    cct_gotoxy(4 + (n - 1) * 8 - times + 8, 4 + (rownow - 1) * 4 + i);
    cout << "        ";
}

		for (i = 0; i < 3; i++)
		{
			cct_gotoxy(4 + (n - 1) * 8 - times, 4 + (rownow - 1) * 4 + i);
			cout << "        ";
		}

		for (i = 0; i < 3; i++)
		{
			cct_setcolor(color, 0);
			cct_gotoxy(4 + (j - 1) * 8 - times, 4 + (rownow - 1) * 4 + i);
			if (i == 0)
				cout << "┏" << "━━━" << "┓";
			else if (i == 1)
				cout << "┃" << "  ★   " << "┃";
			else
				cout << "┗" << "━━━" << "┛";
		}


		Sleep(1);
	}
	Sleep(1);
}
// 將 map 數據拷貝到 a 陣列
void copyMapToArray(int map[10][12], int a[11][13])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
}

// 將 a 陣列中的數據拷貝回 map
void copyArrayToMap(int a[11][13], int map[10][12])
{
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 13; j++)
		{
			map[i - 1][j - 1] = a[i][j];
		}
	}
}

// 判斷顏色
int whatcolor(int a)
{
	switch (a)
	{
	case 1:
		return COLOR_HBLUE;
	case 2:
		return COLOR_HGREEN;
	case 3:
		return COLOR_HCYAN;
	case 4:
		return COLOR_HRED;
	case 5:
		return COLOR_HPINK;
	default:
		return 0;
	}
}

// 找到上方最近的非 0 單元,並下落
void moveBlockUp(int a[11][13], int rownow, int col)
{
	int n;
	for (int i = rownow; i >= 2; i--)
	{
		if (a[i][col] == 0)
		{
			for (n = i - 1; n >= 1; n--)
			{
				if (a[n][col] != 0) break;
			}
			if (n != 0)
			{
				anime_g(a,n, i, whatcolor(a[n][col]), col);
				a[i][col] = a[n][col];
				a[n][col] = 0;
			}
		}
	}
}

// 判斷左側是否有空列
bool isLeftColumnEmpty(int a[11][13], int row, int colnow)
{
	return a[row][colnow - 1] == 0;
}

// 對左側整列進行左移
void moveLeftColumn(int a[11][13], int row, int colnow, int targetCol)
{
	for (int i = 1; i <= row; i++)
	{
		if (a[i][colnow] != 0)
		{
			anime_moveleft_g(colnow, targetCol, whatcolor(a[row][colnow]), i);
			a[i][targetCol] = a[i][colnow];
			a[i][colnow] = 0;
		}
	}
}
void see_fall_g(int map[10][12], int row, int col, int rownow, int colnow)
{
	int a[11][13] = { 0 };

	copyMapToArray(map, a);
	for (int j = 1; j <= col; j++)
	{
		moveBlockUp(a, rownow, j);

		if (isLeftColumnEmpty(a, row, colnow - 1))
		{
			moveLeftColumn(a, row, colnow, colnow - 1);
		}
	}
	copyArrayToMap(a, map);
}
