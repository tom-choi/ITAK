/*信04 2250268 楊懿德*/
#include<iostream>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include "popstar.h"
#include "cmd_console_tools.h"
using namespace std;

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int menu()
{
	cct_setconsoleborder(71, 41, 71, 41);
	char chose;
	while (1)
	{
		cout << "---------------------------------" << endl;
		cout << "A.命令行找出可消除项并标识" << endl;
		cout << "B.命令行完成一次消除（分步骤显示）" << endl;
		cout << "C.命令行完成一关（分步骤显示）" << endl;
		cout << "D.伪图形界面下用鼠标选择一个色块（无分隔线）" << endl;
		cout << "E.伪图形界面下用鼠标选择一个色块（有分隔线）" << endl;
		cout << "F.伪图形界面完成一次消除（分步骤）" << endl;
		cout << "G.伪图形界面完整版" << endl;
		cout << "Q.退出" << endl;
		cout << "---------------------------------" << endl;
		cout << "[请选择:]";
		chose = _getch();
		if (chose == 'A' || chose == 'a' || chose == 'B' || chose == 'b' || chose == 'C' || chose == 'c' || chose == 'D' || chose == 'd' || chose == 'E' || chose == 'e' || chose == 'F' || chose == 'f' || chose == 'G' || chose == 'g')
		{
			cout << chose<<endl;
			break;
		}
		else
		{
			cct_cls();
		}
	}
	return chose;
}

int set_x()
{
	int max_x;
	while (1)
	{
		cout << "请输入行数(8-10)：" << endl;
		cin >> max_x;
		while (getchar() != '\n')//当输入的字符不是回车就清空缓冲区，当有符合if语句就先执行if
		{
			cin.clear();
			continue;//清空缓冲区
		}
		if (max_x >= 8 && max_x <= 10)
			break;
	}
	return max_x;
}
int set_y()
{
	int max_y;
	while (1)
	{
		cout << "请输入列数(8-10)：" << endl;
		cin >> max_y;
		while (getchar() != '\n')//当输入的字符不是回车就清空缓冲区，当有符合if语句就先执行if
		{
			cin.clear();
			continue;//清空缓冲区
		}
		if (max_y >= 8 && max_y <= 10)
			break;
	}
	return max_y;
}
int main()
{
	cct_setconsoleborder(100, 30, 100, 30);
	char choice;

	while (1)
	{
		choice = menu();
		if (choice == 'A' || choice == 'a')
		{
			choice1();
		}
		else if (choice == 'B' || choice == 'b')
		{
			choice2();
		}
		else if (choice == 'C' || choice == 'c')
		{
			choice3();
		}
		else if (choice == 'D' || choice == 'd')
		{
			choice4();
		}
		else if (choice == 'E' || choice == 'e')
		{
			choice5();
		}
		else if (choice == 'F' || choice == 'f')
		{
			choice6();
		}
		else if (choice == 'G' || choice == 'g')
		{
			choice7();
		}
		cct_cls();
	}

	return 0;
}