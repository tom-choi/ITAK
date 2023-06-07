void see_fall_g(int map[10][12], int max_x, int max_y, int rownow, int colnow) 
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
    switch(a)
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
        default :
            return 0;
    }
}

// 找到上方最近的非 0 單元,並下落
void moveBlockUp(int a[11][13], int rownow, int col)
{
    for (int i = rownow; i >= 2; i--)  
    {
        if (a[i][col] == 0) 
        {
            for (int n = i - 1; n >= 1; n--) 
            {
                if (a[n][col] != 0) break;
            }
            if (n != 0) 
            {
                anime_g(n, i, whatcolor(a[n][j]), col);
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
            anime_moveleft_g(colnow, targetCol, whatcolor(a[n][j]), i); 
            a[i][targetCol] = a[i][colnow];
            a[i][colnow] = 0;
        }
    }
}