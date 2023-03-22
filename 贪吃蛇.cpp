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
	char vo[20];
	char res[260];
	char file1[100] = "setaudio wjz.mp3 volume to "; // to����һ��Ҫ�пո񣬲�Ȼ�ᱨ��
	mciSendString("status wjz.mp3 volume", res, 260, NULL);
	int volume = 0;
	volume = atoi(res); // ת�����
	volume += 400;
	itoa(volume, vo, 10); //ת�����
	strcat(file1, vo); // ��vo����file1����
	mciSendString(file1, NULL, 0, NULL); // �趨�ɹ�
	mciSendString("play wjz", NULL, 0, NULL);

	
}
void GameDraw()
{
	BeginBatchDraw();//˫�����ֹ����
	setbkcolor(RGB(28, 115, 119));//���ñ�����ɫ
	cleardevice();
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
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	setfillcolor(RGB(200, 26, 22));//ʳ�����ɫ
	solidcircle(food_x, food_y, 5);//����ʳ��
	EndBatchDraw();
		setfillcolor(RGB(200, 26, 22));//ʳ�����ɫ
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

	if (snake.coor[0].x < LeftWall+10 || snake.coor[0].x > RightWall-10 || snake.coor[0].y < UpWall+10 || snake.coor[0].y > DownWall-10)
		//�ж��Ƿ�ײǽ
	{
		GameDraw();
		mciSendString("close cxk", NULL, 0, NULL);
		mciSendString("open cxk.MP3 alias cxk", NULL, 0, NULL);
		mciSendString("play cxk", NULL, 0, NULL);
		printf("��Ϸ����");
		_getch();
		main();
	}
	if (snake.coor[0].x == food_x && snake.coor[0].y == food_y)//�жϳԵ�ʳ��
	{
		snake.size++;
		music();
		food();
	}
	for (int i = 1; i < snake.size; i++)//�ж��Ƿ�Ե��Լ�
	{
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y)
		{
			GameDraw();
			mciSendString("close cxk", NULL, 0, NULL);
			mciSendString("open cxk.MP3 alias cxk", NULL, 0, NULL);
			mciSendString("play cxk", NULL, 0, NULL);
			printf("��Ϸ����");
			_getch();
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
	food();
	GameDraw(); 
	printf("���������ʼ\n");
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