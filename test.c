#define _CRT_SECURE_NO_WARNINGS -1

#include "snake.h"

//进入游戏界面
void menu()
{
	system("mode con cols=100 lines=30");//设置控制台窗口的大小
	SetPos(40, 16);
	printf("欢迎使用贪吃蛇\n");
	SetPos(38, 18);
	printf("上下左右控制\n");
	getchar();
	system("cls");
}

void SnakeStart(pSnake s)//贪吃蛇开始准备阶段
{
	srand((unsigned int)time(NULL));

	system("mode con cols=100 lines=30");//设置控制台窗口的大小
	DrawMap();


	InitSnake(s);
	CreatFood(s);
}

int main()
{
	menu();
	Snake s;
	memset(&s, 0, sizeof(Snake));
	SnakeStart(&s);

	while (1)
	{
		SnakeMove(&s);
		Sleep(500);
		if(SnakeRun(&s))
		{
			break;
		}
	}

	getchar();
	//system("pause");
	return 0;
}