/*��04 2250268 ��ܲ��*/
#include<iostream>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include "popstar.h"
#include "cmd_console_tools.h"
using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int menu()
{
	cct_setconsoleborder(71, 41, 71, 41);
	char chose;
	while (1)
	{
		cout << "---------------------------------" << endl;
		cout << "A.�������ҳ����������ʶ" << endl;
		cout << "B.���������һ���������ֲ�����ʾ��" << endl;
		cout << "C.���������һ�أ��ֲ�����ʾ��" << endl;
		cout << "D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�" << endl;
		cout << "E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�" << endl;
		cout << "F.αͼ�ν������һ���������ֲ��裩" << endl;
		cout << "G.αͼ�ν���������" << endl;
		cout << "Q.�˳�" << endl;
		cout << "---------------------------------" << endl;
		cout << "[��ѡ��:]";
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
		cout << "����������(8-10)��" << endl;
		cin >> max_x;
		while (getchar() != '\n')//��������ַ����ǻس�����ջ����������з���if������ִ��if
		{
			cin.clear();
			continue;//��ջ�����
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
		cout << "����������(8-10)��" << endl;
		cin >> max_y;
		while (getchar() != '\n')//��������ַ����ǻس�����ջ����������з���if������ִ��if
		{
			cin.clear();
			continue;//��ջ�����
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