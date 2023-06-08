#ifndef FLYUNDERGROUND_H_INCLUDED
#define FLYUNDERGROUND_H_INCLUDED

/**
 *头文件包含
 */
#include <stdio.h>
#include <stdlib.h>//rand() && srand()
#include <time.h>//time()
#include <string.h>
#include <Windows.h>//system() && mciSendString()
#include <conio.h>//kbhit() && getch()
#include <mmsystem.h>//mciSendString()

/**
 *宏定义
 */
#define MW 35//游戏地形宽度 实际宽度W-1
#define MH 5//游戏地形高度 实际高度H-1
#define BW 10//障碍间距
#define Speed 50//游戏刷新速度

#define G 61//游戏地面 '='
#define B 91//未通过障碍 '['
#define Bgo 40//通过的障碍 '('
#define F 63//飞行器图形 '?'

#define X 16//飞行器横坐标

#define NL 13//玩家名称长度 实际长度：中文(N-1)/2||英文N-1


/**
 *玩家、飞行器结构体
 */
typedef struct player{
    char name[NL];//玩家名称
    int score;//分数
}Player;//玩家
typedef struct aero{
    char image;//图形
    int x;//横坐标
    int y;//纵坐标
    int upOrDown;//上升(0)或下降(1)状态
}Aero;//飞行器


/**
 *主菜单函数申明
 */
//数据导入
void importRecord(FILE * recordFile, Player * player);
//菜单显示
void printMenu();
//排行榜显示
void printTop10(Player * player);
//top10排行榜文件更新
void updateFile(FILE * recordFile, Player * player);


/**
 *游戏运行函数申明
 */
//初始化游戏地图
void initMap(char mapMatrix[][MW]);
//显示游戏界面
void showMap(char mapMatrix[][MW], Aero * aero);
//更新飞行器
void changeAero(Aero * aero);
//更新地图
void changeMap(char mapMatrix[][MW], int changeMapType);
//游戏结束判断
int gameOver(char mapMatrix[][MW], Aero * aero);
//更新排行榜
void updateTop10(Player * player, int score);



/**
 *主菜单函数定义
 */
//数据导入
void importRecord(FILE * recordFile, Player * player)
{
    int i;
    //循环变量
    fgetc(recordFile);
    if(feof(recordFile))
    {
        for(i=0; i<10; i++)
        {
            strcpy((player+i)->name, "未命名");
            (player+i)->score = 0;
        }
        //初始化排行榜
    }//空文件判断
    else
    {
        rewind(recordFile);
        fread(player, sizeof(Player), 10, recordFile);
        //玩家数据读取
    }
    fclose(recordFile);
    //关闭文件
}
//菜单打印
void printMenu()
{
    printf("\n\n\n");
    printf("\t\t\t   1. 新游戏\n");
    Sleep(50);
    printf("\t\t\t   2. Top10排行榜查看\n");
    Sleep(50);
    printf("\t\t\t   3. 更新排行榜记录文件\n");
    Sleep(50);
    printf("\t\t\t   0. 退出\n\n");
    Sleep(50);
    printf("\t\t 游戏提示：仅空格键进行跳跃，支持二级跳跃！\n");
    Sleep(50);
    printf("\t\t 温馨提示：建议调节窗口位置与大小后进行游戏\n");
    printf("\n\n");
}
//排行榜显示
void printTop10(Player * player)
{
    int i;
    for(i=0; i<10; i++)
    {
        printf("\t\t 第 %2d 名：%12s  得分：%3d\n", i+1, (player+i)->name, (player+i)->score);
    }
}
//top10排行榜文件更新
void updateFile(FILE * recordFile, Player * player)
{
    fwrite(player, sizeof(Player), 10, recordFile);
}


/**
 *游戏运行函数定义
 */
//初始化游戏地图
void initMap(char mapMatrix[][MW])
{
    int i, j;
    for(i=0; i<MH; i++)
    {
        for(j=0; j<MW; j++)
        {
            if(j==MW-1)
            {
                mapMatrix[i][j] = '\0';
            }
            else if(i==MH-1)
            {
                mapMatrix[i][j] = G;
            }
            else
            {
                mapMatrix[i][j] = ' ';
            }
        }
    }
}
//显示游戏界面
void showMap(char mapMatrix[][MW], Aero * aero)
{
    int i;
    char c;
    c = mapMatrix[aero->y][aero->x];
    mapMatrix[aero->y][aero->x] = aero->image;
    //更换飞行器坐标对应字符
    for(i=0;i<MH;i++)
    {
        printf("\t\t %d%s\n", MH-i-1, mapMatrix[i]);
    }//显示结果
    mapMatrix[aero->y][aero->x] = c;
    //恢复地图字符
}
//更新飞行器
void changeAero(Aero * aero)
{
    char c;
    if(kbhit())
    {
        c = getch();
    }
    //敲击键盘
    else
    {
        c = 'c';
    }
    if(c==' '&&aero->upOrDown==0)
    {
        if(aero->y==(MH-2))
        {
            aero->y -= 2;
        }
        else if(aero->y==MH-4)
        {
            aero->y -= 1;
        }
        else
        {
            aero->upOrDown = 1;
            //下次下降
        }
        //进行跳跃
    }
    else
    {
        if(aero->y<MH-2 && aero->upOrDown== 0)
        {
            aero->upOrDown = 1;
            //下一次下降
        }
        else if(aero->y==MH-2)
        {
            aero->upOrDown = 0;
        }
        else
        {
            aero->y++;
            if(aero->y==MH-2)
            {
                aero->upOrDown = 0;
                //触底，下一次可进行跳跃
            }
        }
        //不能跳跃
    }
}
//更新地图
void changeMap(char mapMatrix[][MW], int changeMapType)
{
    int i, j;
    int randType;
    //随机障碍变量

    for(i=0; i<MW-2; i++)
    {
        for(j=0; j<MH-1; j++)
        {
            mapMatrix[j][i] = mapMatrix[j][i+1];
            if(i<X)
            {
                if(mapMatrix[j][i]==B)
                {
                    mapMatrix[j][i] = Bgo;
                }
            }
        }
    }//地图左移一位
    if(changeMapType!=0)
    {
        for(j=0; j<MH-1; j++)
        {
            mapMatrix[j][MW-2] = ' ';
        }
    }//最后一列更新
    else if(changeMapType==0)
    {
        srand(rand()+rand());
        randType = rand()%3;
        if(randType==0)
        {
            mapMatrix[0][MW-2] = ' ';
            mapMatrix[1][MW-2] = ' ';
            mapMatrix[2][MW-2] = B;
            mapMatrix[3][MW-2] = ' ';
        }
        else if(randType==1)
        {
            mapMatrix[0][MW-2] = ' ';
            mapMatrix[1][MW-2] = ' ';
            mapMatrix[2][MW-2] = ' ';
            mapMatrix[3][MW-2] = B;
        }
        else if(randType==2)
        {
            mapMatrix[0][MW-2] = ' ';
            mapMatrix[1][MW-2] = ' ';
            mapMatrix[2][MW-2] = B;
            mapMatrix[3][MW-2] = B;
        }
    }//最后一列更新
}
//游戏结束判断
int gameOver(char mapMatrix[][MW], Aero * aero)
{
    if(mapMatrix[aero->y][aero->x]!=' ')
    {
        return 0;//游戏结束
    }
    else
    {
        return 1;//游戏继续
    }
}
//更新排行榜
void updateTop10(Player * player, int score)
{
    int i;
    char c;
    Player tempPlayer;
    printf("\t\t 恭喜你，以%3d分刷新了排行榜记录！\n", score);
    printf("\t\t 请输入你的名字：");
    fgets(tempPlayer.name, NL, stdin);
    if(tempPlayer.name[0]=='\n')
    {
        strcpy(tempPlayer.name, "未命名");
    }
    else if(tempPlayer.name[strlen(tempPlayer.name)-1]=='\n')
    {
        tempPlayer.name[strlen(tempPlayer.name)-1] = '\0';
    }
    else
    {
        while((c=getchar())!=EOF&&c!='\n');
    }
    //格式化输入检查与修正
    tempPlayer.score = score;
    *(player+9) = tempPlayer;
    //替换第10名，便于循环更新排名
    for(i=9; i>0; i--)
    {
        if((player+i)->score>(player+i-1)->score)
        {
            tempPlayer = *(player+i);
            *(player+i) = *(player+i-1);
            *(player+i-1) = tempPlayer;
        }
    }//查找合适位置，一次冒泡结束排序
}



#endif // FLYUNDERGROUND_H_INCLUDED
