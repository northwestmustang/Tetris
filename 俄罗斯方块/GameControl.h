#pragma once
#ifndef _GAMECONTROL_H_
#define _GAMECONTROL_H_


#include "main.h"
#include"Logic.h"
#include"graph.h"
class GameControl
{
public:
	void initGame(TetrisManager* manager, TetrisControl* control); // 初始化游戏
	void restartGame(TetrisManager* manager, TetrisControl* control); // 重新开始游戏
	void horzMoveTetris(TetrisManager* manager, TetrisControl* control); // 水平移动方块
    void moveDownTetris(TetrisManager* manager, TetrisControl* control); // 向下移动方块
	void rotateTetris(TetrisManager* manager, TetrisControl* control); // 旋转方块
	void dropDownTetris(TetrisManager* manager, TetrisControl* control); // 方块直接落地
	void keydownControl(TetrisManager* manager, TetrisControl* control, int key); // 键按下
	void runGame(TetrisManager* manager, TetrisControl* control); // 运行游戏
	bool ifPlayAgain(); // 再来一次
private:
	Logic logic_G;
	Graph graph_G;
};

#endif // !GAMECONTROL_H