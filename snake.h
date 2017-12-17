#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define FOOD "口"	//墙和蛇身图案
#define INIT_X 24	//蛇出发的起始横坐标
#define INIT_Y 4	//蛇出发的起始纵坐标

#define MIN_SPEED 500	//蛇最小（起始）速度
#define MAX_SPEED 100	//蛇最大速度
#define ADD_SPEED 50	//每次加速改变50
//蛇的速度是靠Sleep函数实现的，Sleep函数控制在屏幕上打印蛇的时间间隔
//当Sleep(int x)中的数值越小，打印时间间隔越短，速度就越快

//蛇结点
typedef struct node
{
	int x;	//蛇结点横坐标
	int y;	//蛇结点纵坐标
	struct node *next;	//蛇结点指针（指向下一结点）
}SnakeNode, *pSnakeNode;

//蛇本身
typedef struct snake
{
	pSnakeNode _pSnake;	//蛇头指针
	pSnakeNode _pFood;	//食物
	enum DIRECTION _Dir;	//行走方向
	enum Status _Status;	//当前状态
	int _SleepTime;	//每走一步停留的时间
	int _Mark;	//分数
}Snake, *pSnake;

//蛇的状态
enum Status
{
	OK,	//活着
	KILL_BY_SELF,	//被自己咬死
	KILL_BY_WALL	//撞墙死
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
void DrawMap(void);//画背景
void InitSnake(pSnake ps);//初始化
void CreatFood(pSnake ps);//设置食物
void SnakeMove(pSnake ps);//移动
int NextIsFood(pSnake ps, pSnakeNode nNode);//判断当前位置是否是食物
void EatFood(pSnake ps, pSnakeNode nNode);//有食物吃食物，增加结点
void NoFood(pSnake ps, pSnakeNode nNode);//无食物不吃
int SnakeRun(pSnake ps);//控制方向
int KillBySelf(pSnake ps);//撞蛇身死亡
int KillByWall(pSnake ps);//撞墙死亡
