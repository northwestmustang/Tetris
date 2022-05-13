#pragma once
#ifndef GRAPH_H
#define GRAPH_H


#include "main.h"
#include"Logic.h"

class Graph
{
public:
	void setPoolColor(const TetrisManager* manager, TetrisControl* control); // 设置颜色
	void printPoolBorder(); // 显示游戏池边界
	void printTetrisPool(const TetrisManager* manager, const TetrisControl* control); // 显示游戏池
	void printCurrentTetris(const TetrisManager* manager, const TetrisControl* control); // 显示当前方块
	void printNextTetris(const TetrisManager* manager); // 显示下一个和下下一个方块
	void printScore(const TetrisManager* manager); // 显示得分信息
	void printPrompting(); // 显示提示信息
private:
	//Logic logic_g;
};
#endif // !GRAPH_H