#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define FOOD "��"
#define INIT_X 24
#define INIT_Y 4

//�߽��
typedef struct node
{
	int x;
	int y;
	struct node *next;
}SnakeNode, *pSnakeNode;

//�߱���
typedef struct snake
{
	pSnakeNode _pSnake;//��ͷָ��
	pSnakeNode _pFood;//ʳ��
	enum DIRECTION _Dir;//���߷���
	enum Status _Status;//��ǰ״̬
	int _SleepTime;//ÿ��һ��ͣ����ʱ��
	//��������ͼ���
}Snake, *pSnake;

//�ߵ�״̬
enum Status
{
	OK,
	KILL_BY_SELF,
	KILL_BY_WALL
};

//����
enum DIRECTION
{
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};


void SetPos(int x, int y);//���ù��λ��
void DrawMap(void);//����ͼ
void InitSnake(pSnake ps);//��ʼ��
void CreatFood(pSnake ps);//����ʳ��
void SnakeMove(pSnake ps);//�ƶ�
int NextIsFood(pSnake ps, pSnakeNode nNode);//�жϵ�ǰλ���Ƿ���ʳ��
void EatFood(pSnake ps, pSnakeNode nNode);//��ʳ���ʳ����ӽ��
void NoFood(pSnake ps, pSnakeNode nNode);//��ʳ�ﲻ��
int SnakeRun(pSnake ps);//���Ʒ���
int KillBySelf(pSnake ps);//ײ��������
int KillByWall(pSnake ps);//ײǽ����
