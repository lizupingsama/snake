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
float ScoreCounter;//���������ı��ٶ���
int count;//��¼�������ٵĴ���
struct tm t1;
time_t now1;
FILE *fp;
enum direction
{
	UP,DOWN,LEFT,RIGHT
};

struct Coor//ÿ���ߵ�����
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
	snake.speed = 125;
	ScoreCounter = 0;
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
	sprintf(c, "%d", score);//������ת��Ϊ�ַ��洢������c��
	BeginBatchDraw();//˫�����ֹ����
	FlushBatchDraw();
	IMAGE img,img2,img3;//ͼƬ����
	loadimage(&img, _T("IMAGE"), _T("head1"), 15, 15);
	loadimage(&img3, _T("IMAGE"), _T("head2"), 15, 15);
	loadimage(&img2, _T("IMAGE"), _T("background"),700,500);
	settextcolor(RGB(163, 202, 88));//������ɫ
	settextstyle(20, 9, "����");

	cleardevice();
	putimage(0, 0, &img2);//����ͼƬ
    outtextxy(650, 30, c);//�������
	{
		setfillcolor(RGB(255, 63, 63));//ǽ����ɫ
		fillrectangle(0, 0, 700, 5);//���ƶ�ǽ
		fillrectangle(695, 0, 700, 500);//������ǽ
		fillrectangle(0, 495, 700, 500);//���Ƶ�ǽ
		fillrectangle(0, 0, 5, 500);//������ǽ
	}

	for (int i = 0; i < snake.size; i++)//������
	{
		if (i == 0)
		{
			putimage(snake.coor[i].x - 8, snake.coor[i].y - 8, 15, 15, &img, 0, 0, SRCAND);//�ü���ͼƬ����ʾͷ��
			putimage(snake.coor[i].x - 8, snake.coor[i].y - 8, 15, 15, &img3, 0, 0, SRCPAINT);
		}
		else
		{
			setfillcolor(RGB(1 + rand() % 300, 1 + rand() % 300, 1 + rand() % 300));//��������������ɫ
			solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
		}
	}
		setfillcolor(RGB(1+rand()%300, 1 + rand() % 300, 1 + rand() % 300));//ʳ�����ɫ
		solidcircle(food_x, food_y, 5);//�滭ʳ��
	
	if (ScoreCounter == 100)//������ÿ�õ�100��,��������1.25��
	{
		snake.speed *= 0.85;
		ScoreCounter = 0;//��������������¿�ʼ����
		count++;
		mciSendString("close level", NULL, 0, NULL);
		mciSendString("open level.wav alias level", NULL, 0, NULL);
		mciSendString("play level", NULL, 0, NULL);
		time(&now1);
		localtime_s(&t1, &now1);
	}

	struct tm t2;
	time_t now2;
	time(&now2);
	localtime_s(&t2, &now2);
	int before = t1.tm_min * 60 + t1.tm_sec;
	int now = t2.tm_min * 60 + t2.tm_sec;
	if (count > 0 && now - before <= 3)//����59��ʱ��ʼ��Ϸ���ܻ����Level UP����ʧ��bug
	{
		outtextxy(330, 230, "Level UP");//��������
		//printf("t1=%d\nt2=%d", before,now);
	}
		

	EndBatchDraw();
	Sleep(snake.speed);//�ӳ�ʱ�䣬�����ߵ��ٶ�
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
	case UP:snake.coor[0].y-= 10;
		break;
	case DOWN:snake.coor[0].y += 10;
		break;
	case LEFT:snake.coor[0].x-= 10;
		break;
	case RIGHT:snake.coor[0].x+= 10;
		break;
	}

	if (snake.coor[0].x == food_x && snake.coor[0].y == food_y)//�жϳԵ�ʳ��
	{
			snake.size++;
			score += 10;
			ScoreCounter += 10;
			if(ScoreCounter!=100)
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
		fscanf(fp, "%d", &MaxScore);//��¼��߷ֵ��ļ���
		fclose(fp);

		//����ҳ���ַ�
		char c1[30] = "��߷�Ϊ��";
		char c2[30] = "��ϲ�㣬�¼�¼��";
		char c4[30] = "��ĵ÷�Ϊ��";
		if (score <= MaxScore)
		{
			char c3[20];
			char c5[20];
			sprintf(c5, "%d", score);
			sprintf(c3, "%d", MaxScore);
			strcat(c1, c3);
			strcat(c1, "��");
			strcat(c4, c5);
			strcat(c4, "��");
			outtextxy(320, 220, "��Ϸ����");
			outtextxy(290, 245, c4);
			outtextxy(290, 270, c1);
			outtextxy(270, 295, "���س������¿�ʼ��Ϸ");
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
			char c4[30] = "��ĵ÷�Ϊ��";
			if (score <= MaxScore)
			{
				char c3[20];
				char c5[20];
				sprintf(c5, "%d", score);
				sprintf(c3, "%d", MaxScore);
				strcat(c1, c3);
				strcat(c1, "��");
				strcat(c4, c5);
				strcat(c4, "��");
				outtextxy(320, 220, "��Ϸ����");
				outtextxy(290, 245, c4);
				outtextxy(290, 270, c1);
				outtextxy(270, 295, "���س������¿�ʼ��Ϸ");
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

void food()//�������ʳ�������
{
	srand((unsigned)time(NULL));
	food_x = (1 + rand() % 69) * 10;//X��[10,690]
	food_y = (1 + rand() % 49) * 10;//Y��[10,490]
}

void button(int x, int y, TCHAR*text)//��ť�滭
{
	int width = textwidth(text);
	int hight = textheight(text);
	fillrectangle(x, y, x + width + 6, y + hight + 6);
	outtextxy(x + 3, y + 3 , text);
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
	count = 0;
	food();
	GameDraw(); 
	//��ʼ����
	ExMessage m;//���ṹ�����
	bool mouse = true;
	TCHAR text[30] = "��ʼ��Ϸ";
	settextstyle(35, 13, text);
	setbkmode(TRANSPARENT);
		int width = textwidth(text);
		int hight = textheight(text);
	while (mouse)
	{
		settextcolor(RGB(255, 63, 63));
		settextstyle(35, 13, text);
		m = getmessage(EX_MOUSE);//��ȡ���״̬��m
		
		if (310 < m.x && m.x < 310 + width + 6 && 230 < m.y && m.y < 230 + hight + 6)//�ж�����Ƿ��ڰ�ť��
		{
			setfillcolor(RGB(185, 228, 228));
			button(310, 230, text);
			m = getmessage(EX_MOUSE);
			if (m.lbutton == true)//�ж�����Ƿ���
				mouse = false;
		}
		else
		{
			setfillcolor(RGB(105, 193, 193));//��ť������ɫЧ��
			button(310, 230, text);
		}
			char c1[30] = "��ǰ��¼��";
			char c3[20];
			sprintf(c3, "%d", MaxScore);
			strcat(c1, c3);
			strcat(c1, "��");
			settextstyle(24, 9, c1);
			settextcolor(RGB(146, 228, 146));
			outtextxy(300, 230 + hight + 20, c1);
	}

	mciSendString("close bgm", NULL, 0, NULL);
	mciSendString("open bgm.mp3 alias bgm", 0, NULL, 0);//BGM����
	mciSendString("play bgm repeat", NULL, 0, NULL);

	while (1)
	{
		SnakeMove();
		GameDraw();
		KeyControl();
	}
}