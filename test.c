#define _CRT_SECURE_NO_WARNINGS -1

#include "snake.h"

//������Ϸ����
void menu()
{
	system("mode con cols=100 lines=30");//���ÿ���̨���ڵĴ�С
	SetPos(40, 16);
	printf("��ӭʹ��̰����\n");
	SetPos(38, 18);
	printf("�������ҿ���\n");
	getchar();
	system("cls");
}

void SnakeStart(pSnake s)//̰���߿�ʼ׼���׶�
{
	srand((unsigned int)time(NULL));

	system("mode con cols=100 lines=30");//���ÿ���̨���ڵĴ�С
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