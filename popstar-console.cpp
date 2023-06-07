/*信04 2250268 楊懿德*/
#include<iostream>
#include <iomanip>
#include <tchar.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "cmd_console_tools.h"
#include "popstar.h"
using namespace std;



////判断周围有没有相同的值
//int judge(int i, int j, char a[16][30], int max_x, int max_y)
//{
//	if (i >= max_x || i < 0 || j >= max_y || j < 0)
//		return 0;
//	else if (a[i][j] == '*')
//		return 1;
//	else
//		return 0;
//}

int judge_num(int i, int j, int map[16][30], int flag[16][30], int max_x, int max_y)
{
	if (i >= max_x || i < 0 || j >= max_y || j < 0)
		return 0;
	else if (!flag[i][j] && map[i][j] >= 0 && map[i][j] <= 5)
		return 1;
	else
		return 0;
}
//结束函数
int end1(char ch1)
{
	if (ch1 == 'E' || ch1 == 'e')
		return 1;
	else return 0;
}
int end2(char ch2)
{
	if (ch2 == 'N' || ch2 == 'n')
		return 1;
	else return 0;
}
int end3(char ch3)
{
	if (ch3 == 'd' || ch3 == 'D')
		return 1;
	else return 0;
}
int end4(char ch4)
{
	if (ch4 == '\r')
		return 1;
	else 
		return 0;
}
int YNQ(char ch)
{
	if (ch == 'Y' || ch == 'y')
		return 1;
	if (ch == 'N' || ch == 'n')
		return 2;
	if (ch == 'q' || ch == 'Q')
		return 3;
	else return 0;
}
int quit(char& ins1, char& ins2,char& ins3)
{
	char ch1, ch2, ch3,ch4;
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cout << endl;
	cout << "输入End继续...";
	while (1)
	{
		ch1 = _getch();
		if (end1(ch1))
		{
			ins1 = ch1;
			cout << ch1;
			break;
		}
	}
	while (1)
	{
		ch2 = _getch();
		if (end2(ch2))
		{
			ins2 = ch2;
			cout << ch2;
			break;
		}
	}
	while (1)
	{
		ch3 = _getch();
		if (end3( ch3))
		{
			ins3 = ch3;
			cout << ch3;
			break;
		}
	}
	while (1)
	{
		ch4 = _getch();
		if (ch4 == '\r')
			break;
	}
	return 0;
}
int quit2(char& ch)
{
	while (1)
	{
		ch = _getch();
		if (end4(ch)>0)
		{
			ch = _getch();
			if (ch == '\r')
				break;
		}
	}
	return 0;
}
int nextstep(char &ch)
{
	char ch1;
	while (1)
	{
		ch = _getch();
		if (YNQ(ch)>0)
		{
			if (YNQ(ch) == 1)
			{
				cout << ch;
				return 1;
			}
			else if (YNQ(ch) == 2)
			{
				cout << ch;
					return 2;
			}
			else
			{
				cout << ch;
				return 0;
			}
		}
	}
	quit2(ch1);
	return 0;
}
////判断游戏成功
//int allflag(char map[16][30], int flag[16][30], int hard)
//{
//	int num = borderx(hard) * bordery(hard) - boomnumber(hard);
//	for (int i = 0; i < borderx(hard); i++)
//	{
//		for (int j = 0; j < bordery(hard); j++)
//		{
//			if (flag[i][j] == 1)
//				num--;
//		}
//	}
//	return num;
//}
void show_downline(int max_x, int max_y)
{
	cout << "╚";
	for (int i = 0; i < max_y; i++)
	{
		cout << "═══";
		if (i + 1 != max_y)
		{
			cout << "╩";
		}
	}
	cout << "╝";
}

void show_upline(int max_x, int max_y)
{
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cout << endl;
	cout << "  ";
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "╔";
	for (int i = 0; i < max_y; i++)
	{
		cout << "═══";
		if (i + 1 != max_y)
		{
			cout << "╦";
		}
	}
	cout << "╗" << endl;
}
void show_cross(int s, int max_x, int max_y)
{
	if (s + 1 != max_x)
	{

		cout << "╠";
		for (int i = 0; i < max_y; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				cout << "═";
			}
			if (i + 1 != max_y)
			{
				cout << "╬";
			}
		}
		cout << "╣" << endl;
	}
}
void show_part(int  map[10][12], int  flag[10][12], int s, int i)
{
	cout << " ";
	for (int j = 1; j <= 2; j++)
	{
		if (flag[s][i] == 1)
		{
			if (j == 2)
			{
				cct_setcolor(COLOR_WHITE, COLOR_WHITE);//右下角
				cout << "   ";
			}
		}
		else
		{
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "  ";
		}
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	}
}
void Draw_border(int map[10][12], int flag[10][12], int choice,int max_x, int max_y)
{
	int a[11][13] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
	cct_gotoxy(1, 1);
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	for (int i = 0; i < max_y; i++)
		cout << setw(8) << i;
	show_upline(max_x, max_y);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	for (int s = 0; s < max_x; s++)
	{
		for (int t = 1; t <= 3; t++)
		{
			if (t == 2)
			{
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << char('A' + s) << ' ';
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			}
			else
			{
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "  ";
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);

			}
			cout << "║";
			for (int i = 0; i < max_y; i++)
			{
				{
					show_part(map, flag, s, i);
				}
				if (i + 1 != max_y)
					cout << " ║";
				/*Sleep(50);*/
			}
			cout << " ║" << endl;
		}
		cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		show_cross(s, max_x, max_y);
	}
	show_downline(max_x, max_y);
	//底板
	int basey = 3, basex = 4, x, y, n;
	int backcolor = 0;
	for (int i = 1; i <= max_x; i++)
	{
		for (int j = 1; j <= max_y; j++)//打印该元素元素块
		{
			x = basex + 8 * (j - 1);
			y = basey + 4 * (i - 1);
			if (a[i][j] == 1)
				backcolor = COLOR_HBLUE;
			else if (a[i][j] == 2)
				backcolor = COLOR_HGREEN;
			else if (a[i][j] == 3)
				backcolor = COLOR_HCYAN;
			else if (a[i][j] == 4)
				backcolor = COLOR_HRED;
			else if (a[i][j] == 5)
				backcolor = COLOR_HPINK;
			cct_setcolor(backcolor, 0);
			for (n = 0; n < 3; n++)
			{
				cct_gotoxy(x, y + n);
				if (n == 0)
					cout << "┏━┓";
				else if (n == 1)
					cout << "┃" << "★" << "┃";
				else
					cout << "┗━┛";
			}

		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
}
void show_withoutupline(int max_x, int max_y)
{
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cout << endl;
	cout << "  ";
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "╔═";
	for (int i = 0; i < max_y; i++)
	{
		cout << "══";
		if (i + 1 != max_y)
		{
			cout << "═";
		}
	}
	cout << "╗" << endl;
}
void show_withoutdownline(int max_x, int max_y)
{
	cout << "╚═";
	for (int i = 0; i < max_y; i++)
	{
		cout << "══";
		if (i + 1 != max_y)
		{
			cout << "═";
		}
	}
	cout << "╝";
}
void show_withoutcross(int s, int max_x, int max_y)
{
	if (s + 1 != max_x)
	{

		cout << "║  ";
		for (int i = 0; i < max_y; i++)
		{
			for (int j = 1; j <= 2; j++)
			{
				cout << "  ";
			}
			if (i + 1 != max_y)
			{
				cout << "  ";
			}
		}
		cout << "║" << endl;
	}
}
void Draw_withoutborder(int map[10][12], int flag[10][12], int choice, int max_x, int max_y)
{
	int a[11][13] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
	cout << "当前屏幕设置为：" << 5 * max_y + 2 << "行" << 8 * (max_x + 1) << "列                  " << endl;
	cct_gotoxy(1, 1);
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	for (int i = 0; i < max_y; i++)
		cout << setw(6) << i;
	show_withoutupline(max_x, max_y);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	for (int s = 0; s < max_x; s++)
	{
		for (int t = 1; t <= 2; t++)
		{
			if (t == 2)
			{
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << char('A' + s) << ' ';
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			}
			else
			{
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "  ";
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);

			}
			cout << "║ ";
			for (int i = 0; i < max_y; i++)
			{
				{
					show_part(map, flag, s, i);
				}
				if (i + 1 != max_y)
					cout << " ";
				/*Sleep(50);*/
			}
			cout << "║" << endl;
		}
		cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		show_withoutcross(s, max_x, max_y);
	}
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "║";
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 1; j <= max_y; j++)
		{
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << "  ";
			 cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		}
		/*Sleep(50);*/
	}
	cout << "║" << endl;
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cout<< "  ";
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	show_withoutdownline(max_x, max_y);
	int backcolor=0;
	int basey = 3, basex = 4, x, y, n;
	for (int i = 1; i <= max_x; i++)
	{
		for (int j = 1; j <= max_y; j++)//打印该元素元素块
		{
			x = basex + 6 * (j - 1);
			y = basey + 3 * (i - 1);
			if (a[i][j] == 1)
				backcolor = COLOR_HBLUE;
			else if (a[i][j] == 2)
				backcolor = COLOR_HGREEN;
			else if (a[i][j] == 3)
				backcolor = COLOR_HCYAN;
			else if (a[i][j] == 4)
				backcolor = COLOR_HRED;
			else if (a[i][j] == 5)
				backcolor = COLOR_HPINK;
			cct_setcolor(backcolor, 0);
			for (n = 0; n < 3; n++)
			{
				cct_gotoxy(x, y + n);
				if (n == 0)
					cout << "┏━┓";
				else if (n == 1)
					cout << "┃" << "★" << "┃";
				else
					cout << "┗━┛";
			}

		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
}
void drawstar(int xcoord, int ycoord, char starvalue, int star_mode)
{
	int basey = 3, basex = 4, x, y;
	x = basex + 8 * (xcoord - 1);
	y = basey + 4 * (ycoord - 1);
	int frontcolor = COLOR_BLACK, backcolor = COLOR_HWHITE;
	if (star_mode == 3)
	{
		cct_gotoxy(xcoord, ycoord);
		cct_setcolor(backcolor, frontcolor);
		cout << "        ";
		cct_gotoxy(xcoord, ycoord + 1);
		cout << "        ";
		cct_gotoxy(xcoord, ycoord + 2);
		cout << "        ";
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	}
	if (starvalue == '1')
		backcolor = COLOR_HBLUE;
	else if (starvalue == '2')
		backcolor = COLOR_HGREEN;
	else if (starvalue == '3')
		backcolor = COLOR_HCYAN;
	else if (starvalue == '4')
		backcolor = COLOR_HRED;
	else if (starvalue == '5')
		backcolor = COLOR_HPINK;
	if (star_mode == 1)
		frontcolor = COLOR_BLACK;
	else if (star_mode == 2)
		frontcolor = COLOR_HWHITE;
	cct_gotoxy(xcoord, ycoord);
	cct_setcolor(backcolor, frontcolor);
	cout << "╔═╗";
	cct_gotoxy(xcoord, ycoord + 1);
	cout << "║★║";
	cct_gotoxy(xcoord, ycoord + 2);
	cout << "╚═╝";
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}