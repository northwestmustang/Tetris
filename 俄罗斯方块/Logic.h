#pragma once
#ifndef LOGIC_H
#define LOGIC_H


#include "main.h"
#include"graph.h"
//class Graph;
class Logic
{
public:
	void giveTetris(TetrisManager* manager); // ��һ������
	bool checkCollision(const TetrisManager* manager); // ��ײ���
	void insertTetris(TetrisManager* manager); // ���뷽��
	void removeTetris(TetrisManager* manager); // �Ƴ�����
	bool checkErasing(TetrisManager* manager, TetrisControl* control); // ���м��
	void gotoxyWithFullwidth(short x, short y); // ��ȫ�Ƕ�λ
private:
	/*Graph graph_L;*/
};

#endif // !LOGIC_H