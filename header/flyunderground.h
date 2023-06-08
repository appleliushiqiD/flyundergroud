#ifndef FLYUNDERGROUND_H_INCLUDED
#define FLYUNDERGROUND_H_INCLUDED

/**
 *ͷ�ļ�����
 */
#include <stdio.h>
#include <stdlib.h>//rand() && srand()
#include <time.h>//time()
#include <string.h>
#include <Windows.h>//system() && mciSendString()
#include <conio.h>//kbhit() && getch()
#include <mmsystem.h>//mciSendString()

/**
 *�궨��
 */
#define MW 35//��Ϸ���ο�� ʵ�ʿ��W-1
#define MH 5//��Ϸ���θ߶� ʵ�ʸ߶�H-1
#define BW 10//�ϰ����
#define Speed 50//��Ϸˢ���ٶ�

#define G 61//��Ϸ���� '='
#define B 91//δͨ���ϰ� '['
#define Bgo 40//ͨ�����ϰ� '('
#define F 63//������ͼ�� '?'

#define X 16//������������

#define NL 13//������Ƴ��� ʵ�ʳ��ȣ�����(N-1)/2||Ӣ��N-1


/**
 *��ҡ��������ṹ��
 */
typedef struct player{
    char name[NL];//�������
    int score;//����
}Player;//���
typedef struct aero{
    char image;//ͼ��
    int x;//������
    int y;//������
    int upOrDown;//����(0)���½�(1)״̬
}Aero;//������


/**
 *���˵���������
 */
//���ݵ���
void importRecord(FILE * recordFile, Player * player);
//�˵���ʾ
void printMenu();
//���а���ʾ
void printTop10(Player * player);
//top10���а��ļ�����
void updateFile(FILE * recordFile, Player * player);


/**
 *��Ϸ���к�������
 */
//��ʼ����Ϸ��ͼ
void initMap(char mapMatrix[][MW]);
//��ʾ��Ϸ����
void showMap(char mapMatrix[][MW], Aero * aero);
//���·�����
void changeAero(Aero * aero);
//���µ�ͼ
void changeMap(char mapMatrix[][MW], int changeMapType);
//��Ϸ�����ж�
int gameOver(char mapMatrix[][MW], Aero * aero);
//�������а�
void updateTop10(Player * player, int score);



/**
 *���˵���������
 */
//���ݵ���
void importRecord(FILE * recordFile, Player * player)
{
    int i;
    //ѭ������
    fgetc(recordFile);
    if(feof(recordFile))
    {
        for(i=0; i<10; i++)
        {
            strcpy((player+i)->name, "δ����");
            (player+i)->score = 0;
        }
        //��ʼ�����а�
    }//���ļ��ж�
    else
    {
        rewind(recordFile);
        fread(player, sizeof(Player), 10, recordFile);
        //������ݶ�ȡ
    }
    fclose(recordFile);
    //�ر��ļ�
}
//�˵���ӡ
void printMenu()
{
    printf("\n\n\n");
    printf("\t\t\t   1. ����Ϸ\n");
    Sleep(50);
    printf("\t\t\t   2. Top10���а�鿴\n");
    Sleep(50);
    printf("\t\t\t   3. �������а��¼�ļ�\n");
    Sleep(50);
    printf("\t\t\t   0. �˳�\n\n");
    Sleep(50);
    printf("\t\t ��Ϸ��ʾ�����ո��������Ծ��֧�ֶ�����Ծ��\n");
    Sleep(50);
    printf("\t\t ��ܰ��ʾ��������ڴ���λ�����С�������Ϸ\n");
    printf("\n\n");
}
//���а���ʾ
void printTop10(Player * player)
{
    int i;
    for(i=0; i<10; i++)
    {
        printf("\t\t �� %2d ����%12s  �÷֣�%3d\n", i+1, (player+i)->name, (player+i)->score);
    }
}
//top10���а��ļ�����
void updateFile(FILE * recordFile, Player * player)
{
    fwrite(player, sizeof(Player), 10, recordFile);
}


/**
 *��Ϸ���к�������
 */
//��ʼ����Ϸ��ͼ
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
//��ʾ��Ϸ����
void showMap(char mapMatrix[][MW], Aero * aero)
{
    int i;
    char c;
    c = mapMatrix[aero->y][aero->x];
    mapMatrix[aero->y][aero->x] = aero->image;
    //���������������Ӧ�ַ�
    for(i=0;i<MH;i++)
    {
        printf("\t\t %d%s\n", MH-i-1, mapMatrix[i]);
    }//��ʾ���
    mapMatrix[aero->y][aero->x] = c;
    //�ָ���ͼ�ַ�
}
//���·�����
void changeAero(Aero * aero)
{
    char c;
    if(kbhit())
    {
        c = getch();
    }
    //�û�����
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
            //�´��½�
        }
        //������Ծ
    }
    else
    {
        if(aero->y<MH-2 && aero->upOrDown== 0)
        {
            aero->upOrDown = 1;
            //��һ���½�
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
                //���ף���һ�οɽ�����Ծ
            }
        }
        //������Ծ
    }
}
//���µ�ͼ
void changeMap(char mapMatrix[][MW], int changeMapType)
{
    int i, j;
    int randType;
    //����ϰ�����

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
    }//��ͼ����һλ
    if(changeMapType!=0)
    {
        for(j=0; j<MH-1; j++)
        {
            mapMatrix[j][MW-2] = ' ';
        }
    }//���һ�и���
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
    }//���һ�и���
}
//��Ϸ�����ж�
int gameOver(char mapMatrix[][MW], Aero * aero)
{
    if(mapMatrix[aero->y][aero->x]!=' ')
    {
        return 0;//��Ϸ����
    }
    else
    {
        return 1;//��Ϸ����
    }
}
//�������а�
void updateTop10(Player * player, int score)
{
    int i;
    char c;
    Player tempPlayer;
    printf("\t\t ��ϲ�㣬��%3d��ˢ�������а��¼��\n", score);
    printf("\t\t ������������֣�");
    fgets(tempPlayer.name, NL, stdin);
    if(tempPlayer.name[0]=='\n')
    {
        strcpy(tempPlayer.name, "δ����");
    }
    else if(tempPlayer.name[strlen(tempPlayer.name)-1]=='\n')
    {
        tempPlayer.name[strlen(tempPlayer.name)-1] = '\0';
    }
    else
    {
        while((c=getchar())!=EOF&&c!='\n');
    }
    //��ʽ��������������
    tempPlayer.score = score;
    *(player+9) = tempPlayer;
    //�滻��10��������ѭ����������
    for(i=9; i>0; i--)
    {
        if((player+i)->score>(player+i-1)->score)
        {
            tempPlayer = *(player+i);
            *(player+i) = *(player+i-1);
            *(player+i-1) = tempPlayer;
        }
    }//���Һ���λ�ã�һ��ð�ݽ�������
}



#endif // FLYUNDERGROUND_H_INCLUDED
