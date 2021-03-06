// ConsoleApplication34.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>

  // 定义常量
#define NUM 10
#define	CMD_LEFT		1
#define	CMD_RIGHT		2
#define	CMD_QUIT		4


int player_x = 127;
int player_y = 380;

// 定义敌人位置的结构体
struct ene
{
	int x, y, v;
};



// 获取用户输入
int GetCommand()
{
	int c = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)		c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)	c |= CMD_QUIT;

	return c;
}

// 倒计时
int Time(int t)
{
	char strsec[10];
	int sec = 50 - (GetTickCount() - t) / 1000;
	
	return sec;
}



// 产生随机敌机
void ballRandom(ene enem[], int i)
{
	enem[i].x = rand() % 601;
	enem[i].y =  rand() % 32;
	enem[i].v = 1 + rand() % 5;
}

// 画敌机，并计算得分
void calculateScore(ene enem[], int &score)
{

	IMAGE enemy;
	IMAGE enemy0;
	IMAGE background;
	loadimage(&background, "test.jpg");
	loadimage(&enemy0, "ship0.jpg");
	loadimage(&enemy, "ship.jpg");

	for (int i = 0; i < NUM; i++)
	{
		putimage(enem[i].x, enem[i].y, &enemy0, SRCAND);
		putimage(enem[i].x, enem[i].y, &enemy, SRCPAINT);

		if (enem[i].y >= 472)
		{
			ballRandom(enem, i);
			continue;
		}
		if (player_x + 8 <= enem[i].x && enem[i].x <= player_x + 72 )
		{
			score++;
			setfillcolor(YELLOW);
			circle(enem[i].x+8, enem[i].y+8, 8);
			ballRandom(enem, i);
		}
	}
}

// 主函数
int main()
{

	    // 初始化
	initgraph(640, 480);
	int k = 0;
	char sco[30];
	IMAGE fighter;
	IMAGE fighter0;
	IMAGE background;
	bool flag = true;
	loadimage(&fighter, "Fighter.jpg");           //加载图片
	loadimage(&fighter0, "Fighter0.jpg");
	loadimage(&background, "test.jpg");
	srand((unsigned) time(NULL));
	BeginBatchDraw();
	putimage(0, 0, &background);
	setlinecolor(GREEN);
	setfillcolor(WHITE);


	ene enem[NUM];
	int dx, i, c, score = 0;
	int t = GetTickCount();
	for (i = 0; i<NUM; i++)
	{
		ballRandom(enem, i);
	}


	// 游戏主循环
	while (flag)
	{
		dx = 0;

		putimage(0, 0, &background);
		// 画敌机，并计算得分
		calculateScore(enem, score);
		
		// 画飞机
		
		putimage(player_x, player_y, &fighter0, SRCAND);
		putimage(player_x, player_y, &fighter, SRCPAINT);
		setlinecolor(YELLOW);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 8);
		line(player_x+60, player_y, player_x+60, 0);

		
		FlushBatchDraw();

		// 获取用户控制命令
		c = GetCommand();
		if (c & CMD_LEFT)	dx = -10;
		if (c & CMD_RIGHT)	dx = 10;
		if (!Time(t)) flag = false;

		// 延时
		Sleep(25);

		// 计算飞机的新坐标
		for (i = 0; i < NUM; i++)
		{
			enem[i].y += enem[i].v;
		}

		// 移动飞机
		player_x += dx;
		if (player_x < -50)   player_x =-50;
		if (player_x > 600) player_x = 600;
		SetWorkingImage(&background);
		k = Time(t);
		sprintf_s(sco, "得分：%d 倒计时:%d", score,k);// 显示得分
		outtextxy(0, 0,sco);
		SetWorkingImage();

	}




	EndBatchDraw();
	
	// 按任意键退出
	_getch();
	closegraph();

	return 0;
}