#include "flyunderground.h"

int main()
{
    char c;
    char Fchoice;//���˵�ѡ��
    int updateRecordFlag;//�ļ������жϱ��
    FILE * recordFile = NULL;//���а��ļ�
    //�����������

    int score;//��Ϸ��������
    int changeMapType;//��ͼ��������ж�
    //��Ϸ��������


    char mapMatrix[MH][MW];//��ͼ����
    Player player[10];//top10�������
    Aero aero;//����������

    system("color 01");//�ڵ�����
    //������ɫ
    if((recordFile = fopen("top10.txt", "r"))!=NULL)
    {
        importRecord(recordFile, player);
        //�������а�����
    }
    else
    {
        for(int i=0; i<10; i++)
        {
            strcpy((player+i)->name, "δ����");
            (player+i)->score = 0;
        }
        //��ʼ�����а�
    }
    updateRecordFlag = 0;
    //��ʼ�����±�ǩ
    mciSendString("open D:\\bgm.mp3 alias BGM", NULL, 0, NULL);
    mciSendString("play BGM repeat", NULL, 0, NULL);
    do
    {
        printMenu();
        do
        {
            printf("\t\t\t   �������ѡ��");
            Fchoice = getchar();
            if(Fchoice!='\n')
            {
                while((c=getchar())!=EOF&&c!='\n');
            }
            if(Fchoice<'0'||Fchoice>'3')
            {
                printf("\t\t\t �������룬����������\n\n");
            }
        }while(Fchoice<'0'||Fchoice>'3');
        system("cls");
        printf("\n\n\n");
        //�����Ļ
        if(Fchoice=='0')
        {
            printf("\t\t ��Ϸ�������ǵ����У�ף��������죡\n\n\n");
            break;
            //�˳���Ϸ
        }
        else if(Fchoice=='1')
        {
            aero.image = F;
            aero.x = X;
            aero.y = MH-2;
            aero.upOrDown = 0;
            //��ʼ����������Ϣ
            score = 0;
            //��ʼ������
            changeMapType = 0;
            //��ʼ����������
            initMap(mapMatrix);
            //��ʼ����Ϸ��ͼ
            do
            {
                if(changeMapType==(BW-1))
                {
                    score++;
                    //��������
                }
                system("cls");
                printf("\n\n\n");
                //�����Ļ
                showMap(mapMatrix, &aero);
                //��ʾ��Ϸͼ��
                printf("\n\t\t\t ��ǰ������%d", score);
                //������ʾ
                Sleep(Speed);
                //����ͣ��
                changeAero(&aero);
                //���·�����
                changeMap(mapMatrix, changeMapType);
                //������Ϸͼ��
                changeMapType++;
                changeMapType %= BW;
                //��ͼ�������ͱ仯

                //��Ϸѭ��
            }while(gameOver(mapMatrix, &aero));
            system("cls");
            printf("\n\n\n");
            //�����Ļ
            if(score>player[9].score)
            {
                updateTop10(player, score);
                system("cls");
                printf("\n\n\n");
                //�����Ļ
                printTop10(player);
                updateRecordFlag = 1;//���Ը����ļ�
                //�������а�
            }
            else
            {
                printf("\t\t ������%3d\n", score);
                printf("\t\t �������ˣ��ٽ�������\n");
            }
            //��ʼ����Ϸ
        }
        else if(Fchoice=='2')
        {
            printTop10(player);
            //�鿴top10
        }
        else if(Fchoice=='3')
        {
            if(updateRecordFlag==1)
            {
                recordFile = fopen("top10.txt", "w");
                updateFile(recordFile, player);
                updateRecordFlag = 0;//���ܸ����ļ�
                printf("\t\t ���³ɹ���\n");
                //�ļ�����
            }
            else
            {
                printf("\t\t δ�����¼�¼�����ٽ�������\n");
                //���ܸ�������
            }
            //�������а��ļ�
        }
        printf("\t\t ");
        getch();
        //�¼�ͣ��
        system("cls");
        printf("\n\n\n");
        //�����Ļ
    }while(Fchoice>='1'&&Fchoice<='3');//�˵�����ѭ��
    mciSendString("stop BGM", NULL, 0, NULL);
    mciSendString("close BGM", NULL, 0, NULL);
    return 0;
}
