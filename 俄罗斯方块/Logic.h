#pragma once
#ifndef LOGIC_H
#define LOGIC_H


#include "main.h"
#include"graph.h"
//class Graph;
class Logic
{
public:
	void giveTetris(TetrisManager* manager); // 给一个方块
	bool checkCollision(const TetrisManager* manager); // 碰撞检测
	void insertTetris(TetrisManager* manager); // 插入方块
	void removeTetris(TetrisManager* manager); // 移除方块
	bool checkErasing(TetrisManager* manager, TetrisControl* control); // 消行检测
	void gotoxyWithFullwidth(short x, short y); // 以全角定位
private:
	/*Graph graph_L;*/
};

#endif // !LOGIC_H