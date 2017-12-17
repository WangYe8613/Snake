#define _CRT_SECURE_NO_WARNINGS -1

#include "snake.h"

//进入游戏界面
void menu()
{
	system("mode con cols=100 lines=30");//设置控制台窗口的大小
	SetPos(40, 15);
	printf("欢迎使用贪吃蛇");
	SetPos(40, 17);
	printf("按任意键开始");
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

	SnakeRun(&s);

	getchar();
	//system("pause");
	return 0;
}