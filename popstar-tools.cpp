/*信04 2250268 楊懿德*/

#include "popstar.h"
#include "cmd_console_tools.h"
#include <iostream>
using namespace std;
void setaround(char map[16][30], int max_x, int max_y, int setx, int sety, int reset)
{
	int xx[4] = { -1, 0, 1, 0 }; // 上、右、下、左四个方向的偏移量
    int yy[4] = { 0, 1, 0, -1 };
	for (int k = 0; k < 4; k++)
	{
		int i = setx + xx[k];
		int j = sety + yy[k];
		if (i >= max_x || i < 0 || j >= max_y || j < 0)
			continue;
		else
		{
			if (reset == 1)
				map[i][j] = '0';
			else
				map[i][j] = '#';
		}
	}
}
//访问标记置1
void setflag_true(int flag[10][12])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
			flag[i][j] = 1;
	}
}
//flag置0
void setflag_false(int flag[10][12])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
			flag[i][j] = 0;
	}
}
//判断位置x是否合理
int judge_insx(char ch,int max_x)
{
	switch (max_x)
	{
	case 8:
		if (ch >= 'A' && ch <= 'H'|| ch >= 'a' && ch <= 'h')
			return 1;
		else return 0;
		break;
	case 9:
		if (ch >= 'A' && ch <= 'I'|| ch >= 'a' && ch <= 'i')
			return 1;
		else return 0;
		break;
	default:
		if (ch >= 'A' && ch <= 'G'|| ch >= 'a' && ch <= 'g')
			return 1;
		else return 0;
		break;
	}

}
//判断位置y是否合理
int judge_insy(char ch,int max_y)
{
	switch (max_y)
	{
	case 8:
		if (ch >= '0' && ch <= '7')
			return 1;
		else
			return 0;
		break;
	case 2:
		if (ch >= '0' && ch <= '8')
			return 1;
		else
			return 0;
		break;
	default:
		if (ch >= '0' && ch <= '9')
			return 1;
		else
			return 0;
		break;
	}

}

//查找与坐标相同的值
void open_map(int map[10][12], int flag[10][12], int max_x, int max_y, int openx, int openy)
{
    char target = map[openx][openy]; // 目标值
    flag[openx][openy] = 1; // 将当前位置标记为1
	int xx[4] = { -1, 0, 1, 0 }; // 上、右、下、左四个方向的偏移量
	int yy[4] = { 0, 1, 0, -1 };
    for (int i = 0; i < 4; i++)
    {
        int tempx = openx + xx[i];
        int tempy = openy + yy[i];
        if (tempx >= 0 && tempx < max_x && tempy >= 0 && tempy < max_y)
        {
            if (map[tempx][tempy] == target && flag[tempx][tempy] == 0)
            {
                open_map(map, flag, max_x, max_y, tempx, tempy);
                flag[tempx][tempy] = 1; // 将相同值的位置标记为1
            }
        }
    }
}
int findmerge(int map[10][12], char getrow, char getcol, int row, int col, int merge[10][12])
{
	int a[11][13] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
	int i = getrow - 'A' + 1, j = getcol - '0' + 1, x, y;
	bool k = true;
	merge[i][j] = 1;
	while (k)
	{
		k = false;
		for (x = 1; x <= row; x++)
		{
			for (y = 1; y <= col; y++)
			{
				if (merge[x][y] == 1)//此处可以向四周寻找
				{
					if (a[x][y] == a[x - 1][y] && merge[x - 1][y] != 1)
					{
						merge[x - 1][y] = 1;
						k = true;
					}
					if (a[x][y] == a[x + 1][y] && merge[x + 1][y] != 1)
					{
						merge[x + 1][y] = 1;
						k = true;
					}
					if (a[x][y] == a[x][y - 1] && merge[x][y - 1] != 1)
					{
						merge[x][y - 1] = 1;
						k = true;
					}
					if (a[x][y] == a[x][y + 1] && merge[x][y + 1] != 1)
					{
						merge[x][y + 1] = 1;
						k = true;
					}
				}
			}
		}
	}
	if (merge[i + 1][j] == 1 || merge[i - 1][j] == 1 || merge[i][j - 1] == 1 || merge[i][j + 1] == 1)
		return 1;
	else
	{
		merge[i][j] = 0;
		return 0;
	}
}
//判断周围有没有数字，如果只有它自己一个则重新输入
int judge(int map[10][12], int max_x, int max_y, int openx, int openy)
{
	int a=0;
	int xx[4] = { -1, 0, 1, 0 }; // 上、右、下、左四个方向的偏移量
	int yy[4] = { 0, 1, 0, -1 };
	for (int i = 0; i < 4; i++)
	{
		int tempx = openx + xx[i];
		int tempy = openy + yy[i];
		if (map[tempx][tempy] == map[openx][openy])
		{
			a++; // 将相同值的位置标记为1
		}
	}
	if (a == 0)
		return 0;
	else
		return 1;
}
int judge_f(int map[10][12], int max_x, int max_y, int openx, int openy)
{
	int b[11][13] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			b[i + 1][j + 1] = map[i][j];
		}
	}
	int a = 0;
	int xx[4] = { -1, 0, 1, 0 }; // 上、右、下、左四个方向的偏移量
	int yy[4] = { 0, 1, 0, -1 };
	for (int i = 0; i < 4; i++)
	{
		int tempx = openx + xx[i];
		int tempy = openy + yy[i];
		if (b[tempx][tempy] == b[openx][openy])
		{
			a++; // 将相同值的位置标记为1
		}
	}
	if (a == 0)
		return 0;
	else
		return 1;
}
//判断鼠标位置y合理
int estimatey_d(int max_y, int y, int& mousey)
{
	for (int i = 0; i < max_y; i++)
	{
		if (y >= 6* i + 4 && y <= 6* i + 8)
		{
			mousey = i;
			return 1;
		}
	}
	return 0;
}
//判断鼠标位置x合理
int estimatex_d(int max_x, int x, int& mousex)
{
	for (int i = 0; i < max_x; i++)
	{
		if (x >= 4 * i  && x <= 4 * i+4 )
		{
			mousex = i;
			return 1;
		}
	}
	return 0;
}
//判断鼠标合理
int locationmouse_d(int max_x,int max_y, int& mousex, int& mousey, int x, int y)
{
	if (!estimatex_d(max_x, y, mousex))
		return 0;
	if (!estimatey_d(max_y, x, mousey))
		return 0;
	return 1;
}
int round_star(int max_x,int max_y,int&mosuex,int &mousey,int x,int y)
{
	return 0;
}
//打印tip
void print_tip_d(int max_x,int max_y, int& mousex, int& mousey, int X, int Y)
{
	cct_gotoxy(0, 4 *max_x + 6);//打印位置不对哦
	cout << "[当前光标] ";
	if (locationmouse_d(max_x,max_y, mousex, mousey, X, Y))
		cout << char(mousex + 'A') << "行" << mousey << "列    ";
}

void light_d(int a[11][13], int rownow, int colnow, int glow,int max_x,int max_y)
{
	int basey = 3, basex = 4, x, y, n;
	x = basex + 6 * (colnow - 1);
	y = basey + 3 * (rownow - 1);
	int backcolor = 0;
	if (a[rownow][colnow] == 1)
		backcolor = COLOR_HBLUE;
	else if (a[rownow][colnow] == 2)
		backcolor = COLOR_HGREEN;
	else if (a[rownow][colnow] == 3)
		backcolor = COLOR_HCYAN;
	else if (a[rownow][colnow] == 4)
		backcolor = COLOR_HRED;
	else if (a[rownow][colnow] == 5)
		backcolor = COLOR_HPINK;
	//else if (a[rownow][colnow] == 0)
	//	backcolor = COLOR_WHITE;
	cct_setcolor(backcolor, glow);
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
	cct_setcolor(0, 7);
}
void light_e(int a[11][13], int rownow, int colnow, int glow, int max_x, int max_y)
{
	int basey = 3, basex = 4, x, y, n;
	x = basex + 8 * (colnow - 1);
	y = basey + 4 * (rownow - 1);
	int backcolor = 0;
	if (a[rownow][colnow] == 1)
		backcolor = COLOR_HBLUE;
	else if (a[rownow][colnow] == 2)
		backcolor = COLOR_HGREEN;
	else if (a[rownow][colnow] == 3)
		backcolor = COLOR_HCYAN;
	else if (a[rownow][colnow] == 4)
		backcolor = COLOR_HRED;
	else if (a[rownow][colnow] == 5)
		backcolor = COLOR_HPINK;
	else if (a[rownow][colnow] == 0)
		backcolor = COLOR_HWHITE;
	cct_setcolor(backcolor, glow);
	for (n = 0; n < 3; n++)
	{
		if (a[rownow][colnow] != 0)
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
	cct_setcolor(0, 7);
}
int judge_mouse_d(int map[10][12], int x, int y, int row, int col, int* rownow, int* colnow)
{
	int a[11][13]={0};
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
	int starow = *rownow, stacol = *colnow;//记录当前亮块位置
	x = x - 2;
	y = y - 2;//左上角第一个色块当成(0,0)
	if ((y % 3 != 0 && y <= row * 3 && y > 0) && (x % 6 != 0 && (x - 1) % 6 != 0 && x > 0 && x <= col * 6))
	{
		*rownow = y / 3 + 1;//相除之后，y的值一共可以有三个因为相除之后的余数是相同的
		*colnow = x / 6+ 1;//获取当前鼠标所在区域
		if (*rownow != starow || *colnow != stacol)//若鼠标区域发生变化
		{
			light_d(a, starow, stacol, COLOR_BLACK,row,col);
			light_d(a, *rownow, *colnow, COLOR_HWHITE,row,col);
			starow = *rownow;
			stacol = *colnow;
			cct_setcolor(0, 7);
			cct_gotoxy(0, row * 3 + 4);
			cout << "[当前鼠标] " << char('A' + *rownow - 1) << "行" << *colnow - 1 << "列                                          ";
		}
		else//若鼠标区域不发生变化
		{
			light_d(a, *rownow, *colnow, COLOR_HWHITE,row,col);
			cct_setcolor(0, 7);
			cct_gotoxy(0, row * 3 + 4);
			cout << "[当前鼠标] " << char('A' + *rownow - 1) << "行" << *colnow - 1 << "列                                         ";
		}
		return 1;
	}
	else
	{
		light_d(a, starow, stacol, COLOR_BLACK,row,col);
		cct_setcolor(0, 7);
		cct_gotoxy(0, row * 3 + 4);
		cout << "[当前鼠标] 位置非法                                                       ";
		return 0;
	}
}
int judge_mouse_e(int map[10][12], int x, int y, int row, int col, int* rownow, int* colnow)
{
	int a[11][13] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
	int starow = *rownow, stacol = *colnow;//记录当前亮块位置
	x = x - 2;
	y = y - 2;//左上角第一个色块当成(0,0)
	if ((y % 4 != 0 && y <= row * 4 && y > 0) && (x % 8 != 0 && (x - 1) % 8 != 0 && x > 0 && x <= col * 8))
	{
		*rownow = y / 4 + 1;//相除之后，y的值一共可以有三个因为相除之后的余数是相同的
		*colnow = x / 8 + 1;//获取当前鼠标所在区域
		if (*rownow != starow || *colnow != stacol)//若鼠标区域发生变化
		{
			light_e(a, starow, stacol, COLOR_BLACK, row, col);
			light_e(a, *rownow, *colnow, COLOR_HWHITE, row, col);
			starow = *rownow;
			stacol = *colnow;
			cct_setcolor(0, 7);
			cct_gotoxy(0, row * 4 + 4);
			cout << "[当前鼠标] " << char('A' + *rownow - 1) << "行" << *colnow - 1 << "列                                          ";
		}
		else//若鼠标区域不发生变化
		{
			light_e(a, *rownow, *colnow, COLOR_HWHITE, row, col);
			cct_setcolor(0, 7);
			cct_gotoxy(0, row * 4 + 4);
			cout << "[当前鼠标] " << char('A' + *rownow - 1) << "行" << *colnow - 1 << "列                                         ";
		}
		return 1;
	}
	else
	{
		light_e(a, starow, stacol, COLOR_BLACK, row, col);
		cct_setcolor(0, 7);
		cct_gotoxy(0, row * 4 + 4);
		cout << "[当前鼠标] 位置非法                                                       ";
		return 0;
	}

}
/***************************************************************************
  函数名称：judge_key
  功    能：根据键盘状态随时更新屏幕上的显示状态
  输入参数：
  返 回 值：不存在非法位置，永远返回1
  说    明：只断不读
***************************************************************************/
int judge_key_d(int map[10][12], int keycode1, int keycode2, int row, int col, int* rownow, int* colnow)
{
	int a[11][13] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
	int starow = *rownow, stacol = *colnow;//记录当前亮块位置
	int k = 0;
	if (keycode1 == 224)
	{
		if (keycode2 == KB_ARROW_UP)
		{
			k = *rownow == 1 ? 0 : 1;
			*rownow = *rownow + row - 1 - k * row;
			light_d(a, starow, stacol, COLOR_BLACK,row,col);
			starow = *rownow;
			light_d(a, starow, stacol, COLOR_HWHITE, row, col);
		}
		else if (keycode2 == KB_ARROW_DOWN)
		{
			k = *rownow == row ? 0 : 1;
			*rownow = *rownow - row + 1 + k * row;
			light_d(a, starow, stacol, COLOR_BLACK, row, col);
			starow = *rownow;
			light_d(a, starow, stacol, COLOR_HWHITE, row, col);
		}
		else if (keycode2 == KB_ARROW_RIGHT)
		{
			k = *colnow == col ? 0 : 1;
			*colnow = *colnow - col + 1 + k * col;
			light_d(a, starow, stacol, COLOR_BLACK, row, col);
			stacol = *colnow;
			light_d(a, starow, stacol, COLOR_HWHITE, row, col);
		}
		else if (keycode2 == KB_ARROW_LEFT)
		{
			k = *colnow == 1 ? 0 : 1;
			*colnow = *colnow + col - 1 - k * col;
			light_d(a, starow, stacol, COLOR_BLACK, row, col);
			stacol = *colnow;
			light_d(a, starow, stacol, COLOR_HWHITE, row, col);
		}
	}
	cct_setcolor(0, 7);
	cct_gotoxy(0, row * 4 + 4);
	cout << "[当前键盘] " << char('A' + *rownow - 1) << "行" << *colnow - 1 << "列                                   ";
	return 1;
}
int judge_key_e(int map[10][12], int keycode1, int keycode2, int row, int col, int* rownow, int* colnow)
{
	int a[11][13] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			a[i + 1][j + 1] = map[i][j];
		}
	}
	int starow = *rownow, stacol = *colnow;//记录当前亮块位置
	int k = 0;
	if (keycode1 == 224)
	{
		if (keycode2 == KB_ARROW_UP)
		{
			k = *rownow == 1 ? 0 : 1;
			*rownow = *rownow + row - 1 - k * row;
			light_e(a, starow, stacol, COLOR_BLACK, row, col);
			starow = *rownow;
			light_e(a, starow, stacol, COLOR_HWHITE, row, col);
		}
		else if (keycode2 == KB_ARROW_DOWN)
		{
			k = *rownow == row ? 0 : 1;
			*rownow = *rownow - row + 1 + k * row;
			light_e(a, starow, stacol, COLOR_BLACK, row, col);
			starow = *rownow;
			light_e(a, starow, stacol, COLOR_HWHITE, row, col);
		}
		else if (keycode2 == KB_ARROW_RIGHT)
		{
			k = *colnow == col ? 0 : 1;
			*colnow = *colnow - col + 1 + k * col;
			light_e(a, starow, stacol, COLOR_BLACK, row, col);
			stacol = *colnow;
			light_e(a, starow, stacol, COLOR_HWHITE, row, col);
		}
		else if (keycode2 == KB_ARROW_LEFT)
		{
			k = *colnow == 1 ? 0 : 1;
			*colnow = *colnow + col - 1 - k * col;
			light_e(a, starow, stacol, COLOR_BLACK, row, col);
			stacol = *colnow;
			light_e(a, starow, stacol, COLOR_HWHITE, row, col);
		}
	}
	cct_setcolor(0, 7);
	cct_gotoxy(0, row * 4 + 4);
	cout << "[当前键盘] " << char('A' + *rownow - 1) << "行" << *colnow - 1 << "列                                   ";
	return 1;
}
void keymouse_basecontrol_d(int map[10][12], int flag[10][12], int max_x, int max_y, int& mousex, int& mousey)
{
	int Xcoord=0, Ycoord=0;
	int ret, maction;
	int keycode1, keycode2=0;
	int k;
	int rownow=1, colnow=1;
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);
	int pre_x = mousex, pre_y = mousey; // 前一个鼠标坐标
	int new_mousex = mousex, new_mousey = mousey;
	while (1)
	{
		ret = cct_read_keyboard_and_mouse(Xcoord, Ycoord, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)//鼠标动了
		{
			k = judge_mouse_d(map, Xcoord, Ycoord, max_x, max_y, &rownow, &colnow);
		}
		else if (ret == CCT_KEYBOARD_EVENT)
		{
			k = judge_key_d(map, keycode1, keycode2, max_x, max_y, &rownow, &colnow);
		}
		else if (maction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == '\r')
		{
			rownow = Ycoord / 3 + 1;//相除之后，y的值一共可以有三个因为相除之后的余数是相同的
			colnow = Xcoord / 6 + 1;//获取当前鼠标所在区域
			cct_gotoxy(0, max_x * 3 + 4);
			cout << "选中了    " << char('A' + rownow - 1) << "行" << colnow - 1 << "列 ";
			break;
		}
		if (maction == MOUSE_RIGHT_BUTTON_CLICK || keycode1 == 'Q' || keycode1 == 'q')
		{
			break;
		}

	}
	cct_disable_mouse();                          //禁用鼠标
	cct_setcursor(CURSOR_VISIBLE_NORMAL);          //打开光标
}


int estimatey_e(int max_y, int y, int& mousey)
{
	for (int i = 0; i < max_y; i++)
	{
		if (y >= 8* i + 4 && y <=8 * i + 9)
		{
			mousey = i;
			return 1;
		}
	}
	return 0;
}
//判断鼠标位置x合理
int estimatex_e(int max_x, int x, int& mousex)
{
	for (int i = 0; i < max_x; i++)
	{
		if (x >= 4* i + 3 && x <= 4 * i + 6)
		{
			mousex = i;
			return 1;
		}
	}
	return 0;
}
//判断鼠标合理
int locationmouse_e(int max_x, int max_y, int& mousex, int& mousey, int x, int y)
{
	if (!estimatex_e(max_x, y, mousex))
		return 0;
	if (!estimatey_e(max_y, x, mousey))
		return 0;
	return 1;
}

void keymouse_basecontrol_e(int map[10][12], int flag[10][12], int max_x, int max_y)
{
	int Xcoord = 0, Ycoord = 0;
	int ret, maction;
	int keycode1, keycode2 = 0;
	int k;
	int rownow = 1, colnow = 1;
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);
	while (1)
	{
		ret = cct_read_keyboard_and_mouse(Xcoord, Ycoord, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)//鼠标动了
		{
			k = judge_mouse_e(map, Xcoord, Ycoord, max_x, max_y, &rownow, &colnow);
		}
		else if (ret == CCT_KEYBOARD_EVENT)
		{
			k = judge_key_e(map, keycode1, keycode2, max_x, max_y, &rownow, &colnow);
		}
		else if (maction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == '\r')
		{
			rownow = Ycoord / 4 + 1;//相除之后，y的值一共可以有三个因为相除之后的余数是相同的
			colnow = Xcoord / 8 + 1;//获取当前鼠标所在区域
			cct_gotoxy(0, max_x * 4 + 4);
			cout << "选中了    " << char('A' + rownow - 1) << "行" << colnow - 1 << "列 ";
			break;
		}
		if (maction == MOUSE_RIGHT_BUTTON_CLICK || keycode1 == 'Q' || keycode1 == 'q')
		{
			break;
		}

	}
	cct_disable_mouse();                          //禁用鼠标
	cct_setcursor(CURSOR_VISIBLE_NORMAL);          //打开光标
}
/***************************************************************************
  函数名称：scan
  功    能：将第一次选中位置将要消去的块依次点亮
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void scan(int map[10][12], int flag[10][12], int row, int col, int bw, int rownow = 0, int colnow = 0)
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
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (flag[i][j] == 1 && !(i == rownow && j == colnow))
			{
				light_d(a, i, j, bw,row,col);
			}
		}
	}


}
void scan_e(int map[10][12], int flag[10][12], int row, int col, int bw, int rownow = 0, int colnow = 0)
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
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (flag[i][j] == 1 && !(i == rownow && j == colnow))
			{
				light_e(a, i, j, bw, row, col);
			}
		}
	}


}
/***************************************************************************
  函数名称：range
  功    能：判断鼠标是否在正确位置内且没有放到非亮块上
  输入参数：
  返 回 值：正确返回1，错误返回0
  说    明：
***************************************************************************/
int range_d(int x, int y, int rownow, int colnow, int row, int col)
{
	x = x - 2;
	y = y - 2;//左上角第一个色块当成(0,0)
	if ((y % 3 != 0 && y <= row * 3 && y > 0) && (x % 6 != 0 && (x - 1) % 6 != 0 && x > 0 && x < col * 6))
	{//在正确范围内
		if (rownow == y / 3 + 1 && colnow == x / 6 + 1)
			return 1;
	}
	return 0;
}
int range_e(int x, int y, int rownow, int colnow, int row, int col)
{
	x = x - 2;
	y = y - 2;//左上角第一个色块当成(0,0)
	if ((y % 4 != 0 && y <= row * 4 && y > 0) && (x % 8 != 0 && (x - 1) % 8 != 0 && x > 0 && x < col * 8))
	{//在正确范围内
		if (rownow == y / 4 + 1 && colnow == x / 8 + 1)
			return 1;
	}
	return 0;
}
/***************************************************************************
  函数名称：diffent_choice
  功    能：不断读取键盘和鼠标状态，做出调用等具体步骤
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int different_choice(int map[10][12], int flag[10][12], int row, int col, int& rownow, int& colnow)
{
	int ret, maction;
	int keycode1=0, keycode2=0;
	int k = 0, judge_d = 0;
	int x = 0, y = 0, ev = 0;
	while (1)
	{
		mergeclear(flag);
		judge_d = 0;
		ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)//鼠标动了
		{
			k = judge_mouse_d(map, x, y, row, col, &rownow, &colnow);
		}
		else if (ret == CCT_KEYBOARD_EVENT)
		{
			k = judge_key_d(map, keycode1, keycode2, row, col, &rownow, &colnow);
		}
		//k=0什么也不做，k!=0再做
		ev = findmerge(map, rownow + 'A' - 1, colnow + '0' - 1, row, col, flag);//获取当前区域是否是可以合成的块
		if (k && ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
		{
			if (ev)//当前块可以合成
			{
				cct_gotoxy(0, row * 3 + 4);
				cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
				judge_d = 1;
			}
			else//当前块不能合成
			{
				cct_gotoxy(0, row * 3 + 4);
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "周围无相同值                                    ";
				judge_d = 2;
			}
		}
		else if (k && ret == CCT_KEYBOARD_EVENT && keycode1 == '\r' && keycode2 == 0)
		{
			if (ev)
			{
				cct_gotoxy(0, row * 3 + 4);
				cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
				judge_d = 1;
			}
			else
			{
				cct_gotoxy(0, row * 3 + 4);
				cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
				cout << "周围无相同值";
				judge_d = 2;
			}
		}
		if (judge_d == 1)//当前块可以合成时，点亮区域，等待二次确认
		{
			scan(map, flag, row, col, COLOR_WHITE, rownow, colnow);
			while (1)
			{
				ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
				if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)
				{
					if (!range_d(x, y, rownow, colnow, row, col))//位置变化
					{
						scan(map, flag, row, col, COLOR_BLACK);
						break;
					}
				}
				else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
				{
					return 1;
				}
				else if (ret == CCT_KEYBOARD_EVENT && keycode1 == '\r' && keycode2 == 0)
					return 1;
				else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 224 && (keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT || keycode2 == KB_ARROW_UP))
				{
					scan(map, flag, row, col, COLOR_BLACK);
					judge_key_d(map, keycode1, keycode2, row, col, &rownow, &colnow);
					break;
				}
			}
		}
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK)
			return 0;
		else if (ret == CCT_KEYBOARD_EVENT && (keycode1 == 'Q' || keycode1 == 'q') && keycode2 == 0)
			return 0;
		if (judge_d == 2)
		{
			while (1)
			{
				ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
				if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)
				{
					if (!range_d(x, y, rownow, colnow, row, col))
						break;
				}
				else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK)
					return 0;
				else if (ret == CCT_KEYBOARD_EVENT && (keycode1 == 'q' || keycode1 == 'Q') && keycode2 == 0)
					return 0;
				else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 224 && (keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT || keycode2 == KB_ARROW_UP))
				{
					judge_key_d(map, keycode1, keycode2, row, col, &rownow, &colnow);
					break;
				}
			}
		}
	}
}
int different_choice_g(int map[10][12], int flag[10][12], int row, int col, int& rownow, int& colnow)
{
	int ret, maction;
	int keycode1 = 0, keycode2 = 0;
	int k = 0, judge_e = 0;
	int x = 0, y = 0, ev = 0;
	while (1)
	{
		mergeclear(flag);
		judge_e = 0;
		ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)//鼠标动了
		{
			k = judge_mouse_e(map, x, y, row, col, &rownow, &colnow);
		}
		else if (ret == CCT_KEYBOARD_EVENT)
		{
			k = judge_key_e(map, keycode1, keycode2, row, col, &rownow, &colnow);
		}
		//k=0什么也不做，k!=0再做
		ev = findmerge(map, rownow + 'A' - 1, colnow + '0' - 1, row, col, flag);//获取当前区域是否是可以合成的块
		if (k && ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
		{
			if (ev)//当前块可以合成
			{
				cct_gotoxy(0, row * 4 + 4);
				cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
				judge_e = 1;
			}
			else//当前块不能合成
			{
				cct_gotoxy(0, row * 4 + 4);
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "周围无相同值                                    ";
				judge_e = 2;
			}
		}
		else if (k && ret == CCT_KEYBOARD_EVENT && keycode1 == '\r' && keycode2 == 0)
		{
			if (ev)
			{
				cct_gotoxy(0, row * 4 + 4);
				cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
				judge_e = 1;
			}
			else
			{
				cct_gotoxy(0, row * 4 + 4);
				cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
				cout << "周围无相同值";
				judge_e = 2;
			}
		}
		if (judge_e == 1)//当前块可以合成时，点亮区域，等待二次确认
		{
			scan_e(map, flag, row, col, COLOR_WHITE, rownow, colnow);
			while (1)
			{
				ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
				if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)
				{
					if (!range_e(x, y, rownow, colnow, row, col))//位置变化
					{
						scan_e(map, flag, row, col, COLOR_BLACK);
						break;
					}
				}
				else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
				{
					return 1;
				}
				else if (ret == CCT_KEYBOARD_EVENT && keycode1 == '\r' && keycode2 == 0)
					return 1;
				else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 224 && (keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT || keycode2 == KB_ARROW_UP))
				{
					scan_e(map, flag, row, col, COLOR_BLACK);
					judge_key_e(map, keycode1, keycode2, row, col, &rownow, &colnow);
					break;
				}
			}
		}
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK)
			return 0;
		else if (ret == CCT_KEYBOARD_EVENT && (keycode1 == 'Q' || keycode1 == 'q') && keycode2 == 0)
			return 0;
		if (judge_e == 2)
		{
			while (1)
			{
				ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
				if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)
				{
					if (!range_e(x, y, rownow, colnow, row, col))
						break;
				}
				else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK)
					return 0;
				else if (ret == CCT_KEYBOARD_EVENT && (keycode1 == 'q' || keycode1 == 'Q') && keycode2 == 0)
					return 0;
				else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 224 && (keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT || keycode2 == KB_ARROW_UP))
				{
					judge_key_e(map, keycode1, keycode2, row, col, &rownow, &colnow);
					break;
				}
			}
		}
	}
}

