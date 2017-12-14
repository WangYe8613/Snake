#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define FOOD "口"
#define INIT_X 24
#define INIT_Y 4

//蛇结点
typedef struct node
{
	int x;
	int y;
	struct node *next;
}SnakeNode, *pSnakeNode;

//蛇本身
typedef struct snake
{
	pSnakeNode _pSnake;//蛇头指针
	pSnakeNode _pFood;//食物
	enum DIRECTION _Dir;//行走方向
	enum Status _Status;//当前状态
	int _SleepTime;//每走一步停留的时间
	//补充分数和加速
}Snake, *pSnake;

//蛇的状态
enum Status
{
	OK,
	KILL_BY_SELF,
	KILL_BY_WALL
};

//方向
enum DIRECTION
{
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};


void SetPos(int x, int y);//设置光标位置
void DrawMap(void);//画地图
void InitSnake(pSnake ps);//初始化
void CreatFood(pSnake ps);//设置食物
void SnakeMove(pSnake ps);//移动
int NextIsFood(pSnake ps, pSnakeNode nNode);//判断当前位置是否是食物
void EatFood(pSnake ps, pSnakeNode nNode);//有食物吃食物，增加结点
void NoFood(pSnake ps, pSnakeNode nNode);//无食物不吃
int SnakeRun(pSnake ps);//控制方向
int KillBySelf(pSnake ps);//撞蛇身死亡
int KillByWall(pSnake ps);//撞墙死亡
