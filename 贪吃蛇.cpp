#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:6385)
#pragma warning(disable:6054)
#pragma warning(disable:28182)
#pragma warning(disable:6011)
#pragma warning(disable:6308)
#pragma warning(disable:28183)
#pragma warning(disable:6387)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib."win.lib")
#define SNAKE_NUM 500//�ߵ�������
#define LeftWall 0
#define RightWall 700
#define UpWall 0
#define DownWall 500
int food_x;
int food_y;
int score,MaxScore;
FILE *fp;
enum direction
{
	UP,DOWN,LEFT,RIGHT
};

struct Coor
{
	float x;
	float y;
};
struct Snake
{
	int size;//�ߵĽ���
	int direction;//�ߵķ���
	int speed;//�ߵ��ٶ�
	struct Coor coor[SNAKE_NUM];
}snake;

int main();
void food();
void GameInit()//��Ϸ��ʼ��
{
	initgraph(RightWall,DownWall);//��ʼ������
	snake.size = 3;//�ߵĳ�ʼ������
	snake.direction = RIGHT;
	snake.speed = 10;
	for (int i = 0; i <= snake.size; i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
	}
}

void music()
{	
	mciSendString("close wjz", NULL, 0, NULL);
	mciSendString("open wjz.MP3 alias wjz", NULL, 0, NULL);
	mciSendString("play wjz", NULL, 0, NULL);
}

void GameDraw()
{
	char c[4];
	sprintf(c, "%d", score);
	BeginBatchDraw();//˫�����ֹ����
	FlushBatchDraw();
	IMAGE img,img2;//ͼƬ����
	loadimage(&img, "head.png", 10, 10);
	loadimage(&img2, "ground2.jpeg", 700, 500);
	cleardevice();
	settextcolor(RGB(163, 202, 88));//������ɫ
	settextstyle(20, 9, "����");
	putimage(0, 0, &img2);
    outtextxy(650, 30, c);//�������
	{
		setfillcolor(RGB(255, 63, 63));
		fillrectangle(0, 0, 700, 5);//���ƶ�ǽ
		fillrectangle(695, 0, 700, 500);//������ǽ
		fillrectangle(0, 495, 700, 500);//���Ƶ�ǽ
		fillrectangle(0, 0, 5, 500);//������ǽ
	}
	setfillcolor(RGB(56, 23, 57));
	for (int i = 0; i < snake.size; i++)//������
	{
		if (i == 0)
			putimage(snake.coor[i].x-5, snake.coor[i].y-5,&img);
		else
		{
			setfillcolor(RGB(1 + rand() % 300, 1 + rand() % 300, 1 + rand() % 300));
			solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
		}
	}
		setfillcolor(RGB(1+rand()%300, 1 + rand() % 300, 1 + rand() % 300));//ʳ�����ɫ
		solidcircle(food_x, food_y, 5);
	
	EndBatchDraw();
	Sleep(125);
}

void SnakeMove()//�ߵ��ƶ�
{
	for (int i = snake.size-1; i >0 ; i--)//�������ͷ�ƶ�
	{
		snake.coor[i].x = snake.coor[i - 1].x;
		snake.coor[i].y = snake.coor[i - 1].y;
	}
	
	switch (snake.direction)
	{
	case UP:snake.coor[0].y-= snake.speed;
		break;
	case DOWN:snake.coor[0].y+= snake.speed;
		break;
	case LEFT:snake.coor[0].x-= snake.speed;
		break;
	case RIGHT:snake.coor[0].x+= snake.speed;
		break;
	}

	if (snake.coor[0].x == food_x && snake.coor[0].y == food_y)//�жϳԵ�ʳ��
	{
			snake.size++;
			score += 10;
			music();
			food();
	}

	if (snake.coor[0].x < LeftWall+10 || snake.coor[0].x > RightWall-10 || snake.coor[0].y < UpWall+10 || snake.coor[0].y > DownWall-10)
		//�ж��Ƿ�ײǽ
	{
		GameDraw();
		mciSendString("close cxk", NULL, 0, NULL);
		mciSendString("open cxk.MP3 alias cxk", NULL, 0, NULL);
		mciSendString("play cxk", NULL, 0, NULL);
		
		fp = fopen("score.txt", "r");
		fscanf(fp, "%d", &MaxScore);
		fclose(fp);

		char c1[30] = "��߷�Ϊ��";
		char c2[30] = "��ϲ�㣬�¼�¼��";
		if (score <= MaxScore)
		{
			char c3[20];
			sprintf(c3, "%d", MaxScore);
			strcat(c1, c3);
			strcat(c1, "��");
			outtextxy(320, 220, "��Ϸ����");
			outtextxy(290, 245, c1);
			outtextxy(270, 270, "���س������¿�ʼ��Ϸ");
		}
		else
		{
		    char c3[20];
			sprintf(c3, "%d", score);
			strcat(c2, c3);
			strcat(c2, "��");
			outtextxy(320, 220, "��Ϸ����");
			outtextxy(270, 245, c2);
			outtextxy(270, 270, "���س������¿�ʼ��Ϸ");
			fp = fopen("score.txt", "w");
			fprintf(fp, "%d", score);
			fclose(fp);
		}
		int choose=0;
		while (choose != 13)
		{
			choose=_getch();
		}
		main();
	}
	
	for (int i = 1; i < snake.size; i++)//�ж��Ƿ�Ե��Լ�
	{
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y)
		{
			GameDraw();
			mciSendString("close cxk", NULL, 0, NULL);
			mciSendString("open cxk.MP3 alias cxk", NULL, 0, NULL);
			mciSendString("play cxk", NULL, 0, NULL);
			fp = fopen("score.txt", "r");
			fscanf(fp, "%d", &MaxScore);
			fclose(fp);

			char c1[30] = "��߷�Ϊ��";
			char c2[30] = "��ϲ�㣬�¼�¼��";
			if (score <= MaxScore)
			{
				char c3[20];
				sprintf(c3, "%d", MaxScore);
				strcat(c1, c3);
				strcat(c1, "��");
				outtextxy(320, 220, "��Ϸ����");
				outtextxy(290, 245, c1);
				outtextxy(270, 270, "���س������¿�ʼ��Ϸ");
			}
			else
			{
				char c3[20];
				sprintf(c3, "%d", score);
				strcat(c2, c3);
				strcat(c2, "��");
				outtextxy(320, 220, "��Ϸ����");
				outtextxy(270, 245, c2);
				outtextxy(270, 270, "���س������¿�ʼ��Ϸ");
				fp = fopen("score.txt", "w");
				fprintf(fp, "%d", score);
				fclose(fp);
			}
			int choose = 0;
			while (choose != 13)
			{
				choose = _getch();
			}
			main();
		}
	}
}

void KeyControl()
{
	//72 80 75 77�������Ҽ�ֵ
	if (_kbhit())
	{//�ж��Ƿ��а�����������򷵻�TRUE
		switch (_getch())
		{
		case 'w':
		case'W':
		case 72:
			if(snake.direction!=DOWN&&snake.direction!=UP)
			snake.direction = UP;
			break;
		case 's':
		case'S':
		case 80:
			if (snake.direction != UP && snake.direction != DOWN)
			snake.direction = DOWN;
			break;
		case 'a':
		case'A':
		case 75:
			if (snake.direction != RIGHT && snake.direction != LEFT)
			snake.direction = LEFT;
			break;
		case 'd':
		case'D':
		case 77:
			if (snake.direction != LEFT && snake.direction != RIGHT)
			snake.direction = RIGHT;
			break;
		}
	}
}

void food()
{
	srand((unsigned)time(NULL));
	 food_x = (1 + rand() % 69) * 10;
	 food_y = (1 + rand() % 49) * 10;
}

int main()
{
	GameInit();
	if ((fp = fopen("Score.txt", "r")) == NULL)
	{
		fp = fopen("Score.txt", "w");
		MaxScore = 0;
		fclose(fp);
	}
	else
	{
		fscanf(fp, "%d", &MaxScore);
		fclose(fp);
	}
	score = 0;
	food();
	GameDraw(); 
	outtextxy(285, 220, "���������ʼ��Ϸ");
	char c1[30] = "��ǰ��¼��";
	char c3[20];
	sprintf(c3, "%d", MaxScore);
	strcat(c1, c3);
	strcat(c1, "��");
	outtextxy(290, 245, c1);

	_getch();
	mciSendString("close bgm", NULL, 0, NULL);
	mciSendString("open bgm.MP3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
	while (1)
	{
		SnakeMove();
		GameDraw();
		KeyControl();
	}
}