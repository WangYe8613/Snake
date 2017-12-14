#define _CRT_SECURE_NO_WARNINGS -1

#include "snake.h"


void SetPos(int x,int y)//设置光标位置
{
	//获取标准输出的句柄
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 0 };
	pos.X = x;
	pos.Y = y;
	//设置当前坐标为标准输出的句柄
	SetConsoleCursorPosition(handle, pos);
}

void DrawMap(void)//画背景
{
	int i;
	for (i = 0; i < 58;i += 2)
	{
		SetPos(i,0);
		printf(FOOD);
	}
	for (i = 0; i < 58; i += 2)
	{
		SetPos(i, 26);
		printf(FOOD);
	}
	for (i = 0; i < 26; i ++)
	{
		SetPos(0, i);
		printf(FOOD);
	}
	for (i = 0; i <= 26; i++)
	{
		SetPos(58, i);
		printf(FOOD);
	}
}

void InitSnake(pSnake ps)//初始化
{
	pSnakeNode cur = NULL;
	int i = 0;

	cur = (SnakeNode* )malloc(sizeof(SnakeNode));
	memset(cur, 0, sizeof(SnakeNode));

	cur->x = INIT_X;
	cur->y = INIT_Y;
	cur->next = NULL;

	for (i = 0; i < 4;i++)
	{
		ps->_pSnake = (SnakeNode*)malloc(sizeof(SnakeNode));
		ps->_pSnake->next = cur;
		ps->_pSnake->x = INIT_X + i * 2;
		ps->_pSnake->y = INIT_Y;
		cur=ps->_pSnake;
	}

	while (cur->next!=NULL)
	{
		SetPos(cur->x,cur->y);
		printf(FOOD);
		cur = cur->next;
	}

	ps->_SleepTime = 500;
	ps->_Status = OK;
	ps->_Dir = RIGHT;
}

void CreatFood(pSnake ps)//设置食物
{
	pSnakeNode cur = NULL;
	pSnakeNode food = NULL;

	food = (SnakeNode*)malloc(sizeof(SnakeNode));
flag:
	memset(food, 0, sizeof(SnakeNode));

	//随机产生食物出现的位置
	do
	{
		food->x = rand() % 56 + 2;
	}while (food->x % 2 != 0);

	food->y = rand() % 25 + 1;

	cur = ps->_pSnake;
	while (cur!=NULL)
	{
		if (cur->x == food->x&&cur->y == food->y)
		{
			goto flag;
		}
		cur = cur->next;
	}
	ps->_pFood = food;
	SetPos(food->x,food->y);
	printf(FOOD);
}

int NextIsFood(pSnake ps, pSnakeNode nNode)//判断当前位置是否是食物
{
	return ps->_pFood->x == nNode->x &&\
		ps->_pFood->y == nNode->y;
}

void EatFood(pSnake ps, pSnakeNode nNode)//有食物吃食物，增加结点
{
	pSnakeNode cur = ps->_pSnake;
	nNode->next = cur;
	ps->_pSnake= nNode;

	cur = ps->_pSnake;

	while (cur!=NULL)
	{
		SetPos(cur->x,cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	CreatFood(ps);
}

void NoFood(pSnake ps, pSnakeNode nNode)//无食物不吃
{
	pSnakeNode cur = ps->_pSnake;
	nNode->next = cur;
	ps->_pSnake = nNode;

	cur = ps->_pSnake;
	while (cur->next->next!=NULL)
	{
		SetPos(cur->x, cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	//倒数第二个可绘制可不绘制，它并未改变
	//SetPos(cur->x, cur->y);
	//printf("口");
	SetPos(cur->next->x,cur->next->y);
	printf("  ");
	free(cur->next);
	cur->next = NULL;
}

int KillBySelf(pSnake ps)//撞蛇身死亡
{
	pSnakeNode cur = ps->_pSnake->next;
	while (cur !=NULL)
	{
		if (ps->_pSnake->x == cur->x && ps->_pSnake->y == cur->y)
		{
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}
int KillByWall(pSnake ps)//撞墙死亡
{

	if (ps->_pSnake->x == 0 || ps->_pSnake->x == 58||\
		ps->_pSnake->y == 0 || ps->_pSnake->y == 26)
	{
		return 1;
	}
	return 0;
}

void SnakeMove(pSnake ps)//移动
{
	pSnakeNode nNode = NULL;
	nNode = (SnakeNode*)malloc(sizeof(SnakeNode));
	memset(nNode, 0, sizeof(SnakeNode));

	nNode->x = ps->_pSnake->x;
	nNode->y = ps->_pSnake->y;

	//判断方向
	switch (ps->_Dir)
	{
	case UP:
		nNode->y--;
		break;
	case DOWN:
		nNode->y++;
		break;
	case LEFT:
		nNode->x -= 2;
		break;
	case RIGHT:
		nNode->x += 2;
		break;
	default:
		break;
	}

	//如果下个位置有食物
	if (NextIsFood(ps,nNode))
	{
		EatFood(ps, nNode);
	}
	else
	{
		NoFood(ps, nNode);
	}
}

int SnakeRun(pSnake ps)//控制方向
{
	do
	{
		if (GetAsyncKeyState(VK_DOWN)&&ps->_Dir!=UP)
		{
			ps->_Dir = DOWN;
		}
		else if (GetAsyncKeyState(VK_UP) && ps->_Dir != DOWN)
		{
			ps->_Dir = UP;
		}
		else if (GetAsyncKeyState(VK_LEFT) && ps->_Dir !=RIGHT )
		{
			ps->_Dir = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && ps->_Dir != LEFT)
		{
			ps->_Dir = RIGHT;
		}

		SnakeMove(ps);

		//判断死否死亡
		if(KillBySelf(ps))//撞蛇身
		{
			ps->_Status = KILL_BY_SELF;
		}
		if (KillByWall(ps))//撞墙
		{
			ps->_Status = KILL_BY_WALL;
		}

		Sleep(ps->_SleepTime);
	} while (ps->_Status == OK);

	if (ps->_Status == KILL_BY_WALL)
	{
		SetPos(24,12);
		printf("你被撞死了！");
		return 1;
	}
	else if (ps->_Status == KILL_BY_SELF)
	{
		SetPos(24,12);
		printf("你被自己咬死了！");
		return 1;
	}
	return 0;
}
