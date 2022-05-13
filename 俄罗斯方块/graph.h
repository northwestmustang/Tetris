#pragma once
#ifndef GRAPH_H
#define GRAPH_H


#include "main.h"
#include"Logic.h"

class Graph
{
public:
	void setPoolColor(const TetrisManager* manager, TetrisControl* control); // ������ɫ
	void printPoolBorder(); // ��ʾ��Ϸ�ر߽�
	void printTetrisPool(const TetrisManager* manager, const TetrisControl* control); // ��ʾ��Ϸ��
	void printCurrentTetris(const TetrisManager* manager, const TetrisControl* control); // ��ʾ��ǰ����
	void printNextTetris(const TetrisManager* manager); // ��ʾ��һ��������һ������
	void printScore(const TetrisManager* manager); // ��ʾ�÷���Ϣ
	void printPrompting(); // ��ʾ��ʾ��Ϣ
private:
	//Logic logic_g;
};
#endif // !GRAPH_H