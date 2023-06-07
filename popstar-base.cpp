/*��04 2250268 ��ܲ��*/
#include<iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include "cmd_console_tools.h"
#include "popstar.h"
using namespace std;

//�����ڲ�����
void creatarr(int a[10][12], int row, int col, int setx, int sety, int draw)
{
	int i, j;
	srand(unsigned(time(0)));

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (a[i][j] == 0) {
				int randomValue = 1 + rand() % 5; // Generate random number from 1 to 5
				a[i][j] = randomValue;
			}
		}
	}
	if (draw ==1)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				int Xcoord = 4+6 * j;
				int Ycoord = 3+3 * i;
				drawstar(Xcoord, Ycoord,a[i][j],1);
			}
		}
	}
	if (draw == 2)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				int Xcoord = 4 + 8 * j;
				int Ycoord = 3 + 4 * i;
				drawstar(Xcoord, Ycoord, a[i][j], 1);
			}
		}
	}
}

//���,�ڹ������λ�ô�ӡ
void print_start(int max_y)
{
	switch (max_y)
	{
	case 8:
		cout << "  |  0  1  2  3  4  5  6  7" << endl;
		cout << "--+-------------------------" << endl;
		break;
	case 9:
		cout << "  |  0  1  2  3  4  5  6  7  8" << endl;
		cout << "--+----------------------------" << endl;
		break;
	case 10:
		cout << "  |  0  1  2  3  4  5  6  7  8  9" << endl;
		cout << "--+-------------------------------" << endl;
		break;
	}
}
//��ӡ�ڲ�
void print_internal(int choice, int map[10][12], int flag[10][12], int max_x, int max_y)
{
	print_start(max_y);
	for (int i = 0; i < max_x; i++)
	{
		cout << char('A' + i) << " |  ";
		for (int j = 0; j < max_y; j++)
		{
			if (flag[i][j] == 1)
			{
				if (map[i][j] == 0)
				{
					cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
					cout << map[i][j];
				}
				else
				{
					if (choice == 2)
					{
						cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
						cout << map[i][j];
						cct_setcolor();
					}
					else if (choice == 3)
					{
						cout << "*";
						cct_setcolor();
					}
					else
					{
						if (map[i][j] == 0)
						{
							cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
							cout << map[i][j];
						}
						else
						{
							cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
							cout << map[i][j];
						}
					}
				}
			}
			else
			{
				if (choice == 3)
				{
					cout << '0';
				}
				else
				{
					cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
					cout << map[i][j];
				}
			}
			cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
			cout << "  ";
		}
		cout << endl;
	}
}
void fall_down(int map[10][12], int max_x, int max_y,int *emptyCount)//�����������
{
	char tmp[16][30]{};
	for (int j = 0; j < max_y; j++)
	{
		*emptyCount = 0; // ��¼��λ������
		for (int i = max_x - 1; i >= 0; i--)
		{
			if (map[i][j] == 0)
			{
				(* emptyCount)++; // ��λ������1
			}
			else if (*emptyCount > 0)
			{
				// ����ǰλ�õ������ƶ�����λ��
				tmp[i][j]=map[i + *emptyCount][j];
				map[i + *emptyCount][j] = map[i][j];
				map[i][j] = tmp[i][j];
			}
		}
	}
	return;
}
bool canMoveLeft(int map[10][12], int max_x, int max_y) {
	bool needShift = false; // ����Ƿ���Ҫ����

	for (int col = max_x - 1; col >= 0; col--) {
		bool hasStar = false; // ��Ǹ����Ƿ�������

		// ��鵱ǰ���Ƿ�������
		for (int row = 0; row < max_y; row++) {
			if (map[row][col] != 0) {
				hasStar = true;
				break;
			}
		}

		// �����ǰ��û�����ǣ����Ҳ���һ��ȫ�㣬����Ҫ����
		if (!hasStar && col != 0) {
			needShift = true;
			break;
		}
	}

	return needShift;
}

void moveLeft(int a[10][12], int row, int col, int x, int y) {
	if (y == 0) {
		return; // ��ǰλ���Ѿ���������У��޷������ƶ�
	}

	if (a[x][y - 1] == 0) {
		// �������λ��Ϊ�գ����������ƶ�
		a[x][y - 1] = a[x][y]; // ����ǰ���������ƶ�
		a[x][y] = 0; // ����ǰλ����Ϊ��
	}
	else {
		// ���±����ҵ��������λ��Ϊ�յ�λ��
		for (int i = x + 1; i < row; i++) {
			if (a[i][y - 1] == 0) {
				// �ҵ��������λ��Ϊ�յ�λ�ã����������ƶ�
				a[i][y - 1] = a[x][y]; // ����ǰ���������ƶ�
				a[x][y] = 0; // ����ǰλ����Ϊ��
				break;
			}
		}
	}
}

int score(int flag[10][12], int max_x, int max_y)
{
	int num = 0; // ͳ��ֵΪ0�ĸ���

	for (int i = 0; i < max_x; i++)
	{
		for (int j = 0; j < max_y; j++)
		{
			if (flag[i][j] == 1)
			{
				num++; //ͳ����ͬ�ĸ���
			}
		}
	}

	return num*num*5;
}
/***************************************************************************
  �������ƣ�mergeclear
  ��    �ܣ�����merge��������ͬ������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mergeclear(int flag[10][12])
{
	int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 12; j++)
		{
			flag[i][j] = 0;
		}
	}
}
void afterarr(int map[10][12], int flag[10][12], int max_x, int max_y,int change,int *emptyCount)
{
	print_start(max_y);
	for (int i = 0; i < max_x; i++)
	{
		cout << char('A' + i) << " |  ";
		for (int j = 0; j < max_y; j++)
		{
			if (flag[i][j] == 1)
			{
				if (map[i][j] == 0)
				{
					cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
					cout << map[i][j];
				}
				else
				{
					if (!change)
					{
						map[i][j] = 0;
						cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
						cout << map[i][j];
					}
					else
					{
						cout << map[i][j];
					}
					cct_setcolor();
				}
			}
			else
			{
				if (map[i][j] == 0)
				{
					cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
					cout << map[i][j];
				}
				else
				{
					cout << map[i][j];
				}
			}
			cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
			cout << "  ";
		}
		cout << endl;
	}
}
int inputchoice3(char& ins1, char& ins2,int max_x,int max_y)
{
	char ch1, ch2;
	int type = 0;
	while (1)
	{
		ch1 = _getch();
		if (ch1 == 'q' || ch1 == 'Q')
		{
			ins1 = 'q';
			cout << ch1 << endl;
			return 1;
		}
		else if (judge_insx(ch1,max_x))
		{
			ins1 = ch1;
			cout << ch1;
			break;
		}
	}
	while (1)
	{
		ch2 = _getch();
		if (judge_insy(ch2,max_y))
		{
			ins2 = ch2;
			cout << ch2;
			break;
		}
	}
	cout << endl;
	return type;
}
int convertx(char ins)
{
	if(ins>='A' && ins <= 'Z')
		return ins - 'A';
	if (ins >= 'a' && ins <= 'z')
		return ins - 'a';
	return 0;
}

int converty(char ins)
{
	if (ins <= '9')
		return ins-'0';
	return 0;

}
void choice1()
{
	cct_setconsoleborder(71, 41, 71, 41);
	int map[10][12]={0};
	int flag[10][12];
	char ch1, ch2;
	char end1, end2, end3;
	cct_cls();
	int max_x = set_x();
	int max_y = set_y();
	cout << "��ǰ���飺" << endl;
	creatarr( map, max_x, max_y, 0, 0, -1);
	setflag_true(flag);
	print_internal(1, map, flag,max_x, max_y);
	cout << endl;
	cout << "������ĸ+������ʽ[����c2]����������꣺";
	inputchoice3(ch1, ch2,max_x,max_y);
	cout << "����Ϊ" << ch1 << "��" << ch2 << "��" << endl;
	cout << endl;
	int x = convertx(ch1);
	int y = converty(ch2);
	cout << "��ǰ����(��ͬɫ��ʶ)��" << endl;
	setflag_false(flag);
	open_map(map, flag, max_x, max_y, x, y);
	print_internal(3, map, flag, max_x, max_y);
	cout << endl;
	cout << "��ǰ����(��ͬɫ��ʶ)��" << endl;
	setflag_false(flag);
	open_map(map, flag, max_x, max_y, x, y);
	print_internal(2, map, flag, max_x, max_y);
	quit(end1,end2,end3);
	return;
}

void choice2()
{
	cct_setconsoleborder(71, 41, 71, 41);
	int map[10][12]={0};
	int flag[10][12];
	char ch1, ch2;
	cct_cls();
	int max_x = set_x();
	int max_y = set_y();
	cout << "��ǰ���飺" << endl;
	creatarr(map, max_x, max_y, 0, 0, -1);
	setflag_true(flag);
	print_internal(1, map, flag, max_x, max_y);
	cout << endl;
	while (1)
	{
		cout << "������ĸ+������ʽ[����c2]����������꣺";
		inputchoice3(ch1, ch2, max_x, max_y);
		cout << "����Ϊ" << ch1 << "��" << ch2 << "��" << endl;
		cout << endl;
		int x = convertx(ch1);
		int y = converty(ch2);
		open_map(map, flag, max_x, max_y, x, y);
		if (!judge(map, max_x, max_y, x, y))
		{
			cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
			continue;
		}
		cout << "��ǰ����(��ͬɫ��ʶ)��" << endl;
		setflag_false(flag);
		open_map(map, flag, max_x, max_y, x, y);
		print_internal(3, map, flag, max_x, max_y);
		cout << endl;
		cout << "��ǰ����(��ͬɫ��ʶ)��" << endl;
		setflag_false(flag);
		open_map(map, flag, max_x, max_y, x, y);
		int point = score(flag, max_x, max_y);
		print_internal(2, map, flag, max_x, max_y);
		cout << endl;
		char ch;
		cout << "��ȷ���Ƿ��C1����Χ����ֵͬ����(Y/N/Q)��";
		int a = nextstep(ch);
		cout << endl;
		if (a == 1)
		{
			int num = 0;
			afterarr(map, flag, max_x, max_y, 0, 0);
			num += point;
			cout << "���ε÷֣�" << point << "  �ܵ÷֣�" << num << endl;
		}
		char end1, end2, end3;
		cout << "���س������������������...";
		quit2(end1);
		int emptyCount;
		cout << endl;
		fall_down(map, max_x, max_y, &emptyCount);
		afterarr(map, flag, max_x, max_y, 1, &emptyCount);
		quit(end1, end2, end3);
		break;
	}
}
int judge_break(int arr[12][12], int column, int line)
{
	if ((arr[line][1] == 0 || arr[line][1] != arr[line][2] && arr[line][1] != arr[line - 1][1])
		&& (arr[line][column] == 0 || arr[line][column] != arr[line][column - 1] && arr[line][column] != arr[line - 1][column])) {
		int flag = 0;
		for (int i = 2; i < line; i++)
			for (int j = 2; j < column; j++) {
				if (arr[j][i] != arr[j - 1][i] && arr[j][i] != arr[j + 1][i] && arr[j][i] != arr[j][i - 1] && arr[j][i] != arr[j][i + 1]) {
					flag = 1;
				}
				else if (arr[j][i] == 0) {
					continue;
				}
				else
					return 0;

			}
		return flag;
	}
	return 0;
}
void choice3()
{
	int num = 0;
	cct_setconsoleborder(71, 41, 71, 41);
	int map[10][12]={0};
	int flag[10][12];
	char ch1, ch2;
	cct_cls();
	int max_x = set_x();
	int max_y = set_y();
	creatarr(map, max_x, max_y, 0, 0, -1);
	while (1)
	{
		cout << "��ǰ���飺" << endl;
		setflag_true(flag);
		print_internal(1, map, flag, max_x, max_y);
		cout << endl;
		cout << "������ĸ+������ʽ[����c2]����������꣺";
		inputchoice3(ch1, ch2, max_x, max_y);
		cout << "����Ϊ" << ch1 << "��" << ch2 << "��" << endl;
		cout << endl;
		int x = convertx(ch1);
		int y = converty(ch2);
		open_map(map, flag, max_x, max_y, x, y);
		if (!judge(map, max_x, max_y, x, y))
		{
			cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
			continue;
		}
		cout << "��ǰ����(��ͬɫ��ʶ)��" << endl;
		setflag_false(flag);
		open_map(map, flag, max_x, max_y, x, y);
		print_internal(3, map, flag, max_x, max_y);
		cout << endl;
		cout << "��ֵͬ���ع�������(��ͬɫ��ʶ)��" << endl;
		setflag_false(flag);
		open_map(map, flag, max_x, max_y, x, y);
		int point = score(flag, max_x, max_y);
		print_internal(2, map, flag, max_x, max_y);
		cout << endl;
		char ch;
		cout << "��ȷ���Ƿ��C1����Χ����ֵͬ����(Y/N/Q)��";
		int a = nextstep(ch);
		cout << endl;
		if (a == 1)
		{
			afterarr(map, flag, max_x, max_y, 0, 0);
			num += point;
			cout << "���ε÷֣�" << point << "  �ܵ÷֣�" << num << endl;
		}
		char end1;
		cout << "���س������������������...";
		quit2(end1);
		int emptyCount;
		cout << endl;
		fall_down(map, max_x, max_y, &emptyCount);
		if (canMoveLeft(map, max_x, max_y))
		{
			moveLeft(map, max_x, max_y, 0, 0);
		}
		if (judge_break(map, max_x, max_y))
		{
			cout << "\n�޿ɺϲ������Ϸ������                ";
			break;
		}
		afterarr(map, flag, max_x, max_y, 1, &emptyCount);
		cout << "�����������������س��������µ�һ������...";
		quit2(end1);
		cout << endl << endl;
	}
	char end1, end2, end3;
	quit(end1, end2, end3);
}
void choice4()
{
	cct_setconsoleborder(71, 41,71,41);
	int map[10][12]={0};
	int flag[10][12];
	setflag_false(flag);
	cct_cls();
	//������Ļ
	int max_x = set_x();
	int max_y = set_y();
	cct_cls();
	creatarr(map, max_x, max_y, 0, 0, -1);
	cct_setconsoleborder(max_x * 9,max_y*5);
	Draw_withoutborder(map, flag, 7, max_x, max_y);
	/*drawstar(3);*/
	int mousex, mousey;
	keymouse_basecontrol_d(map, flag, max_x,max_y, mousex, mousey);
	cout << endl;
	char end1, end2, end3;
	quit(end1, end2, end3);
	return;
}
void choice5()
{
	cct_setconsoleborder(71, 41, 71, 41);
	int map[10][12]={0};
	int flag[10][12];
	setflag_false(flag);
	cct_cls();
	//������Ļ
	int max_x = set_x();
	int max_y = set_y();
	cct_cls();
	creatarr(map, max_x, max_y, 0, 0, -1);
	cct_setconsoleborder(max_x * 9, max_y * 5);
	Draw_border(map, flag, 7, max_x, max_y);
	keymouse_basecontrol_e(map, flag, max_x, max_y);
	cout << endl;
	char end1, end2, end3;
	quit(end1, end2, end3);
	return;
}
void disappear(int map[10][12], int row, int col, int rownow, int colnow, int merge[10][12])
{
	int a[11][13] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
	int i, j, n;
	cct_setcolor(15, 15);
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (!(i == rownow && j == colnow) && merge[i][j] == 1)
			{
				a[i][j] = 0;
				for (n = 0; n < 3; n++)
				{
					cct_gotoxy(4 + (j - 1) * 6, 3 + 3 * (i - 1) + n);
					cout << "      ";
				}
			}
			else if (i == rownow && j == colnow)
			{
				a[i][j] = 0;
				for (n = 0; n < 3; n++)
				{
					cct_gotoxy(4 + (j - 1) * 6, 3 + 3 * (i - 1) + n);
					cout << "      ";
				}
				cct_setcolor(15, 15);
			}
		}
	}
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 13; j++)
		{
			map[i-1][j-1]=a[i][j];
		}
	}
}

void disappear_g(int map[10][12], int row, int col, int rownow, int colnow, int merge[10][12])
{
	int a[11][13] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
	int i, j, n;
	cct_setcolor(15, 15);
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (!(i == rownow && j == colnow) && merge[i][j] == 1)
			{
				a[i][j] = 0;
				for (n = 0; n < 3; n++)
				{
					cct_gotoxy(4 + (j - 1) * 8, 3 + 4 * (i - 1) + n);
					cout << "      ";
				}
			}
			else if (i == rownow && j == colnow)
			{
				a[i][j] = 0;
				for (n = 0; n < 3; n++)
				{
					cct_gotoxy(4 + (j - 1) * 8, 3 + 4 * (i - 1) + n);
					cout << "      ";
				}
				cct_setcolor(15, 15);
			}
		}
	}
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 13; j++)
		{
			map[i - 1][j - 1] = a[i][j];
		}
	}
}
void anime(int n, int i, int color, int colnow)
{//�ӵ�n���䵽��i�У���ɫΪcolor
	int times, j;
	for (times = (i - n) * 3; times > 0; times--)//һ��Ҫ���ش�ӡ������Щ����
	{
		cct_setcolor(15, 15);
		for (j = 0; j < 3; j++)
		{
			cct_gotoxy(4 + (colnow - 1) * 6, 3 + (i - 1) * 3 - times + j);
			cout << "      ";
		}

		cct_setcolor(color, 0);
		for (j = 0; j < 3; j++)
		{
			cct_gotoxy(4 + (colnow - 1) * 6, 4 + (i - 1) * 3 - times + j);
			if (j == 0)
				cout << "��" << "��" << "��";
			else if (j == 1)
				cout << "��" << "��"  << "��";
			else
				cout << "��" << "��" << "��";
		}
		/*if ((times - 1) % 4 == 0)
		{
			cct_setcolor(15, 0);
			cct_gotoxy(4 + (colnow - 1) * 6, 3 + (i - 1) * 3 - times);
			cout << "��" << "��" << "��";
		}*/
		Sleep(1);
	}
	Sleep(1);
}
//void anime_g(int n, int i, int color, int colnow)
//{//�ӵ�n���䵽��i�У���ɫΪcolor
//	int times, j;
//	for (times = (i - n) * 4; times > 0; times--)//һ��Ҫ���ش�ӡ������Щ����
//	{
//		cct_setcolor(15, 15);
//		for (j = 0; j < 3; j++)
//		{
//			cct_gotoxy(4 + (colnow - 1) * 8, 3 + (i - 1) * 4 - times + j);
//			cout << "      ";
//		}
//
//		cct_setcolor(color, 0);
//		for (j = 0; j < 3; j++)
//		{
//			cct_gotoxy(4 + (colnow - 1) * 8, 4 + (i - 1) * 4 - times + j);
//			if (j == 0)
//				cout << "��" << "��" << "��";
//			else if (j == 1)
//				cout << "��" << "��" << "��";
//			else
//				cout << "��" << "��" << "��";
//		}
//		if ((times - 1) % 4 == 0)
//		{
//			cct_setcolor(15, 0);
//			cct_gotoxy(4 + (colnow - 1) * 8, 3 + (i - 1) * 4 - times);
//			cout << "��" << "��" << "��";
//		}
//		Sleep(1);
//	}
//	Sleep(1);
//}
//void anime_moveleft_g(int n, int j, int color, int rownow)
//{//�ӵ�n���ƶ�����j�У���ɫΪcolor
//	int times, i;
//	for (times = (j - n) * 8; times > 0; times--)//һ��Ҫ���ش�ӡ�ƶ���Щ����
//	{
//		cct_setcolor(15, 15);
//		for (i = 0; i < 3; i++)
//		{
//			cct_gotoxy(4 + (n - 1) * 8 - times, 4 + (rownow - 1) * 4 + i);
//			cout << "        ";
//		}
//
//		cct_setcolor(color, 0);
//		for (i = 0; i < 3; i++)
//		{
//			cct_gotoxy(4 + (j - 1) * 8 - times, 4 + (rownow - 1) * 4 + i);
//			if (i == 0)
//				cout << "��" << "��������" << "��";
//			else if (i == 1)
//				cout << "��" << "  ��   " << "��";
//			else
//				cout << "��" << "��������" << "��";
//		}
//
//		Sleep(1);
//	}
//	Sleep(1);
//}

void anime_g(int n, int i, int color, int colnow)
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
				cout << "��" << "��" << "��";
			else if (j == 1)
				cout << "��" << "��" << "��";
			else
				cout << "��" << "��" << "��";
		}
		if ((times - 1) % 4 == 0)
		{
			cct_setcolor(15, 0);
			cct_gotoxy(4 + (colnow - 1) * 8, 3 + (i - 1) * 4 - times);
			cout << "������";
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
				cout << "��" << "������" << "��";
			else if (i == 1)
				cout << "��" << "  ��   " << "��";
			else
				cout << "��" << "������" << "��";
		}


		Sleep(1);
	}
	Sleep(1);
}

/***************************************************************************
  �������ƣ�see_fall
  ��    �ܣ���ʾ������Ķ���Ч��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void see_fall(int map[10][12], int row, int col, int rownow, int colnow)
{
	int a[11][13] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
	int i, j, n;
	int backcolor = 0;
	for (j = 1; j <= col; j++)//���ҵ��б���
	{
		for (i = row; i >= 2; i--)//���������ң���һ�������Ҳ����������
		{
			if (a[i][j] == 0)
			{
				for (n = i; n >= 1; n--)
				{
					if (a[n][j] != 0)
						break;
				}
				if (n != 0)
				{
					if (a[n][j] == 1)
						backcolor = COLOR_HBLUE;
					else if (a[n][j] == 2)
						backcolor = COLOR_HGREEN;
					else if (a[n][j] == 3)
						backcolor = COLOR_HCYAN;
					else if (a[n][j] == 4)
						backcolor = COLOR_HRED;
					else if (a[n][j] == 5)
						backcolor = COLOR_HPINK;
					anime(n, i, backcolor, j);
					a[i][j] = a[n][j];
					a[n][j] = 0;
				}
			}
		}
	}
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 13; j++)
		{
			map[i - 1][j - 1] = a[i][j];
		}
	}
}
void see_fall_g(int map[10][12], int row, int col, int rownow, int colnow)
{
	int a[11][13] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
	int i, j, n;
	int backcolor = 0;
	for (j = 1; j <= col; j++) // �����ҵ��б���
	{
		for (i = rownow; i >= 2; i--) // ���������ң���һ�������Ҳ����������
		{
			if (a[i][j] == 0)
			{
				for (n = i - 1; n >= 1; n--)
				{
					if (a[n][j] != 0)
						break;
				}
				if (n != 0)
				{
					if (a[n][j] == 1)
						backcolor = COLOR_HBLUE;
					else if (a[n][j] == 2)
						backcolor = COLOR_HGREEN;
					else if (a[n][j] == 3)
						backcolor = COLOR_HCYAN;
					else if (a[n][j] == 4)
						backcolor = COLOR_HRED;
					else if (a[n][j] == 5)
						backcolor = COLOR_HPINK;
					anime_g(n, i, backcolor, j);
					a[i][j] = a[n][j];
					a[n][j] = 0;
				}
			}
		}


		// �������Ƿ��п��У�����п��У�������н�������
		if (a[row][colnow - 1] == 0)
		{
			for (i = 1; i <= row; i++)
			{
				if (a[i][colnow] != 0)
				{
					if (a[i][colnow] == 1)
						backcolor = COLOR_HBLUE;
					else if (a[i][colnow] == 2)
						backcolor = COLOR_HGREEN;
					else if (a[i][colnow] == 3)
						backcolor = COLOR_HCYAN;
					else if (a[i][colnow] == 4)
						backcolor = COLOR_HRED;
					else if (a[i][colnow] == 5)
						backcolor = COLOR_HPINK;
					anime_moveleft_g(colnow, colnow - 1, backcolor, i);
					a[i][colnow - 1] = a[i][colnow];
					a[i][colnow] = 0;
				}
			}
		}
	}
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 13; j++)
		{
			map[i - 1][j - 1] = a[i][j];
		}
	}
}

void wait()
{
	int ret, x, y, maction, keycode1, keycode2;
	while (1)
	{
		ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
			return;
		else if (ret == CCT_KEYBOARD_EVENT && keycode1 == '\r' && keycode2 == 0)
			return;
	}
	return;
}
void calc(int map[10][12], int merge[10][12], int getrow, int getcol)
{
	int a[11][13] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
	int i, j;
	a[getrow - 'A'+1][getcol - '0'+1]++;
	for (i = 1; a[i][1] != 0; i++)
	{
		for (j = 1; a[i][j] != 0; j++)
		{
			if (merge[i][j] == 1 && !(i == getrow - 'A' && j == getcol - '0'))
				a[i][j] = 0;
		}
	}
}
void choice6()
{
	cct_setconsoleborder(71, 41, 71, 41);
	int map[10][12] = { 0 };
	int flag[10][12]={0};
	char ch1 = 0, ch2 = 0;
	int judge=0,rownow=1,colnow=1;
	setflag_false(flag);
	cct_cls();
	//������Ļ
	int max_x = set_x();
	int max_y = set_y();
	cct_cls();
	creatarr(map, max_x, max_y, 0, 0, -1);
	cct_setconsoleborder(max_x * 9, max_y * 5);
	cct_enable_mouse();
	Draw_withoutborder(map, flag, 7, max_x, max_y);
	judge = different_choice(map, flag, max_x, max_y, rownow, colnow);
	if (judge)
	{
		disappear(map, max_x, max_y, rownow, colnow, flag);//Ƭ������
		cct_setcolor(0, 15);
		map[rownow][colnow]--;
		int point = score(flag, max_x,max_y);
		map[rownow][colnow]++;
		cct_gotoxy(0, 0);
		cout << "���ε÷�:" << point << " �ܷ�:" << point << " �ϳ�Ŀ��:" << 5 << "           ";
		cct_gotoxy(0, max_x * 3 + 4);
		cout << "�ϳ���ɣ��س���/�����������                                                                ";
		wait();
		calc(map, flag, rownow + 'A' - 1, colnow + '0' - 1);//��ʱa�����Ǻϳɵ�δ����״̬
		map[rownow][colnow]--;
		see_fall(map, max_x, max_y, rownow, colnow);//������
		cct_gotoxy(0,  max_x*3 + 4);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << "���κϳ���ɣ���c�򵥻����������һ�β���                                                ";
		wait();
	}
	char end1, end2, end3;
	quit(end1, end2, end3);
	return;
}

void choice7()
{
	cct_cls();
	cct_setcursor(3);


	cct_setconsoleborder(71, 41, 71, 41);
	int map[10][12] = { 0 };
	int flag[10][12] = { 0 };
	char ch1 = 0, ch2 = 0;
	int judge = 1, rownow = 1, colnow = 1;
	setflag_false(flag);
	cct_cls();
	//������Ļ
	int max_x = set_x();
	int max_y = set_y();
	cct_cls();
	creatarr(map, max_x, max_y, 0, 0, -1);
	cct_setconsoleborder(max_x * 9, max_y * 5);
	Draw_border(map, flag, 7, max_x, max_y);
	cct_enable_mouse();
	int sum = 0;
	while (judge)
	{
		mergeclear(flag);
		judge = different_choice_g(map, flag, max_x, max_y, rownow, colnow);
		if (judge)
		{
			disappear_g(map, max_x, max_y, rownow, colnow, flag);//Ƭ������
			cct_setcolor(0, 15);
			map[rownow][colnow]--;
			int point = score(flag, max_x, max_y);
			sum += point;
			map[rownow][colnow]++;
			cct_gotoxy(0, 0);
			cout << "���ε÷�:" << point << " �ܷ�:" << sum << " �ϳ�Ŀ��:" << 5 << "           ";
			cct_gotoxy(0, max_x * 4 + 4);
			cout << "�ϳ���ɣ��س���/�����������                                                                ";
			wait();
			calc(map, flag, rownow + 'A' - 1, colnow + '0' - 1);//��ʱa�����Ǻϳɵ�δ����״̬
			map[rownow][colnow]--;
			see_fall_g(map, max_x, max_y, rownow, colnow);//������
			cct_gotoxy(0, max_x * 4 + 4);
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cout << "���κϳ���ɣ���c�򵥻����������һ�β���                                                ";
			/*wait();*/
			if (judge_break(map, max_x, max_y))
			{
				int count = (int)sqrt((score(map, max_x, max_y) / 5));
				cct_gotoxy(0, max_x * 4 + 4);
				cout << "ʣ��" << count << "���ǣ��޿�����������ؽ������س�������һ��";
				char end1, end2, end3;
				quit(end1, end2, end3);
			}
		}
	}


	//cct_setcursor(2);
	//cct_gotoxy(0, max_x * 4 + 4);
	//char end1, end2, end3;
	//quit(end1, end2, end3);
}