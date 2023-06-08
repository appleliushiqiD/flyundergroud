#include "flyunderground.h"

int main()
{
    char c;
    char Fchoice;//主菜单选择
    int updateRecordFlag;//文件更新判断标记
    FILE * recordFile = NULL;//排行榜文件
    //主体变量申明

    int score;//游戏分数计算
    int changeMapType;//地图更新类别判断
    //游戏变量申明


    char mapMatrix[MH][MW];//地图数组
    Player player[10];//top10玩家数组
    Aero aero;//飞行器变量

    system("color 01");//黑底蓝字
    //设置颜色
    if((recordFile = fopen("top10.txt", "r"))!=NULL)
    {
        importRecord(recordFile, player);
        //导入排行榜数据
    }
    else
    {
        for(int i=0; i<10; i++)
        {
            strcpy((player+i)->name, "未命名");
            (player+i)->score = 0;
        }
        //初始化排行榜
    }
    updateRecordFlag = 0;
    //初始化更新标签
    mciSendString("open D:\\bgm.mp3 alias BGM", NULL, 0, NULL);
    mciSendString("play BGM repeat", NULL, 0, NULL);
    do
    {
        printMenu();
        do
        {
            printf("\t\t\t   输入你的选择：");
            Fchoice = getchar();
            if(Fchoice!='\n')
            {
                while((c=getchar())!=EOF&&c!='\n');
            }
            if(Fchoice<'0'||Fchoice>'3')
            {
                printf("\t\t\t 错误输入，请重新输入\n\n");
            }
        }while(Fchoice<'0'||Fchoice>'3');
        system("cls");
        printf("\n\n\n");
        //清空屏幕
        if(Fchoice=='0')
        {
            printf("\t\t 游戏不是我们的所有，祝你生活愉快！\n\n\n");
            break;
            //退出游戏
        }
        else if(Fchoice=='1')
        {
            aero.image = F;
            aero.x = X;
            aero.y = MH-2;
            aero.upOrDown = 0;
            //初始化飞行器信息
            score = 0;
            //初始化分数
            changeMapType = 0;
            //初始化更新类型
            initMap(mapMatrix);
            //初始化游戏地图
            do
            {
                if(changeMapType==(BW-1))
                {
                    score++;
                    //分数增加
                }
                system("cls");
                printf("\n\n\n");
                //清空屏幕
                showMap(mapMatrix, &aero);
                //显示游戏图像
                printf("\n\t\t\t 当前分数：%d", score);
                //分数显示
                Sleep(Speed);
                //更新停顿
                changeAero(&aero);
                //更新飞行器
                changeMap(mapMatrix, changeMapType);
                //更新游戏图像
                changeMapType++;
                changeMapType %= BW;
                //地图更新类型变化

                //游戏循环
            }while(gameOver(mapMatrix, &aero));
            system("cls");
            printf("\n\n\n");
            //清空屏幕
            if(score>player[9].score)
            {
                updateTop10(player, score);
                system("cls");
                printf("\n\n\n");
                //清空屏幕
                printTop10(player);
                updateRecordFlag = 1;//可以更新文件
                //更新排行榜
            }
            else
            {
                printf("\t\t 分数：%3d\n", score);
                printf("\t\t 很厉害了，再接再厉！\n");
            }
            //开始新游戏
        }
        else if(Fchoice=='2')
        {
            printTop10(player);
            //查看top10
        }
        else if(Fchoice=='3')
        {
            if(updateRecordFlag==1)
            {
                recordFile = fopen("top10.txt", "w");
                updateFile(recordFile, player);
                updateRecordFlag = 0;//不能更新文件
                printf("\t\t 更新成功！\n");
                //文件更新
            }
            else
            {
                printf("\t\t 未产生新纪录，请再接再厉！\n");
                //不能更新提醒
            }
            //更新排行榜文件
        }
        printf("\t\t ");
        getch();
        //事件停顿
        system("cls");
        printf("\n\n\n");
        //清空屏幕
    }while(Fchoice>='1'&&Fchoice<='3');//菜单功能循环
    mciSendString("stop BGM", NULL, 0, NULL);
    mciSendString("close BGM", NULL, 0, NULL);
    return 0;
}
