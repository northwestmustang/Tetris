#pragma once
#ifndef _GAMECONTROL_H_
#define _GAMECONTROL_H_


#include "main.h"
#include"Logic.h"
#include"graph.h"
class GameControl
{
public:
	void initGame(TetrisManager* manager, TetrisControl* control); // ��ʼ����Ϸ
	void restartGame(TetrisManager* manager, TetrisControl* control); // ���¿�ʼ��Ϸ
	void horzMoveTetris(TetrisManager* manager, TetrisControl* control); // ˮƽ�ƶ�����
    void moveDownTetris(TetrisManager* manager, TetrisControl* control); // �����ƶ�����
	void rotateTetris(TetrisManager* manager, TetrisControl* control); // ��ת����
	void dropDownTetris(TetrisManager* manager, TetrisControl* control); // ����ֱ�����
	void keydownControl(TetrisManager* manager, TetrisControl* control, int key); // ������
	void runGame(TetrisManager* manager, TetrisControl* control); // ������Ϸ
	bool ifPlayAgain(); // ����һ��
private:
	Logic logic_G;
	Graph graph_G;
};

#endif // !GAMECONTROL_H