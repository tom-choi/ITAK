#pragma once

//int xx[4] = { -1, 0, 1, 0 }; // 上、右、下、左四个方向的偏移量
//int yy[4] = { 0, 1, 0, -1 };

#define OK 1 
#define MAXQSIZE 100
#define LISTINCREMENT 20

int quit(char& ins1, char& ins2, char& ins3);
int quit2(char& ch);

//TOOLS
int judge_insx(char ch,int max_x);
int judge_insy(char ch,int max_y);
void setflag_false(int flag[10][12]);
void setflag_true(int flag[10][12]);
int judge(int map[10][12], int max_x, int max_y, int openx, int openy);
int judge_f(int map[10][12], int max_x, int max_y, int openx, int openy);
void keymouse_basecontrol_d(int map[10][12], int flag[10][12], int max_x, int max_y, int& mousex, int& mousey);
void keymouse_basecontrol_e(int map[10][12], int flag[10][12], int max_x, int max_y);
int different_choice(int map[10][12], int flag[10][12], int row, int col, int& rownow, int& colnow);
int different_choice_g(int map[10][12], int flag[10][12], int row, int col, int& rownow, int& colnow);
void light_d(int a[11][13], int rownow, int colnow, int glow, int max_x, int max_y);

//console
int judge_num(int i, int j, int map[10][12], int flag[10][12], int max_x, int max_y);
int nextstep(char& ch);
void Draw_border(int map[10][12], int flag[10][12], int choice, int max_x, int max_y);
void Draw_withoutborder(int map[10][12], int flag[10][12], int choice, int max_x, int max_y);
void drawstar(int xcoord, int ycoord, char starvalue, int star_mode);

//main
int menu();
int set_x();
int set_y();
void choice1();
void choice2();
void choice3();
void choice4();
void choice5();
void choice6();
void choice7();
void open_map( int map[10][12], int flag[10][12], int max_x, int max_y, int openx, int openy);

//base
void mergeclear(int flag[10][12]);
