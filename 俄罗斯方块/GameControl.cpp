#include "GameControl.h"
void GameControl::initGame(TetrisManager* manager, TetrisControl* control)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE }; // 光标信息

	g_hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台输出句柄
	SetConsoleCursorInfo(g_hConsoleOutput, &cursorInfo); // 设置光标隐藏

	restartGame(manager, control);
}

// =============================================================================
// 重新开始游戏
void GameControl::restartGame(TetrisManager* manager, TetrisControl* control)
{
	memset(manager, 0, sizeof(TetrisManager)); // 全部置0

	// 初始化游戏池
	memcpy(manager->pool, gs_uInitialTetrisPool, sizeof(uint16_t[28]));
	srand((unsigned)time(NULL)); // 设置随机种子

	manager->type[1] = rand() % 7; // 下一个
	manager->orientation[1] = rand() & 3;

	manager->type[2] = rand() % 7; // 下下一个
	manager->orientation[2] = rand() & 3;

	memset(control, 0, sizeof(TetrisControl)); // 全部置0

	logic_G.giveTetris(manager); // 给下一个方块
	graph_G.setPoolColor(manager, control); // 设置颜色
}
void GameControl::horzMoveTetris(TetrisManager* manager, TetrisControl* control)
{
	int x = manager->x; // 记录原列位置

	logic_G.removeTetris(manager); // 移走当前方块
	control->direction == 0 ? (--manager->x) : (++manager->x); // 左/右移动

	if (logic_G.checkCollision(manager)) // 检测到碰撞
	{
		manager->x = x; // 恢复为原列位置
		logic_G.insertTetris(manager); // 放入当前方块。由于位置没改变，不需要设置颜色
	}
	else
	{
		logic_G.insertTetris(manager); // 放入当前方块
		graph_G.setPoolColor(manager, control); // 设置颜色
		graph_G.printCurrentTetris(manager, control); // 显示当前方块
	}
}

// =============================================================================
// 向下移动方块
void GameControl::moveDownTetris(TetrisManager* manager, TetrisControl* control)
{
	int8_t y = manager->y; // 记录原行位置

	logic_G.removeTetris(manager); // 移走当前方块
	++manager->y; // 向下移动

	if (logic_G.checkCollision(manager)) // 检测到碰撞
	{
		manager->y = y; // 恢复为原行位置
		logic_G.insertTetris(manager); // 放入当前方块。由于位置没改变，不需要设置颜色
		if (logic_G.checkErasing(manager, control)) // 检测到消行
		{
			graph_G.printTetrisPool(manager, control); // 显示游戏池
		}
	}
	else
	{
		logic_G.insertTetris(manager); // 放入当前方块
		graph_G.setPoolColor(manager, control); // 设置颜色
		graph_G.printCurrentTetris(manager, control); // 显示当前方块
	}
}
void GameControl::rotateTetris(TetrisManager* manager, TetrisControl* control)
{
	int8_t ori = manager->orientation[0]; // 记录原旋转状态

	logic_G.removeTetris(manager); // 移走当前方块

	// 顺/逆时针旋转
	manager->orientation[0] = (control->clockwise) ? ((ori + 1) & 3) : ((ori + 3) & 3);

	if (logic_G.checkCollision(manager)) // 检测到碰撞
	{
		manager->orientation[0] = ori; // 恢复为原旋转状态
		logic_G.insertTetris(manager); // 放入当前方块。由于状态没改变，不需要设置颜色
	}
	else
	{
		logic_G.insertTetris(manager); // 放入当前方块
		graph_G.setPoolColor(manager, control); // 设置颜色
		graph_G.printCurrentTetris(manager, control); // 显示当前方块
	}
}
// =============================================================================
// 方块直接落地
void GameControl::dropDownTetris(TetrisManager* manager, TetrisControl* control)
{
	logic_G.removeTetris(manager); // 移走当前方块
	for (; manager->y < ROW_END; ++manager->y) // 从上往下
	{
		if (logic_G.checkCollision(manager)) // 检测到碰撞
		{
			break;
		}
	}
	--manager->y; // 上移一格当然没有碰撞

	logic_G.insertTetris(manager); // 放入当前方块
	graph_G.setPoolColor(manager, control); // 设置颜色

	logic_G.checkErasing(manager, control); // 检测消行
	graph_G.printTetrisPool(manager, control); // 显示游戏池
}
void GameControl::keydownControl(TetrisManager* manager, TetrisControl* control, int key)
{
	if (key == 13) // 暂停/解除暂停
	{
		control->pause = !control->pause;
	}

	if (control->pause) // 暂停状态，不作处理
	{
		return;
	}

	switch (key)
	{
	case 'w': case 'W': case '8': case 72: // 上
		control->clockwise = true; // 顺时针旋转
		rotateTetris(manager, control); // 旋转方块
		break;
	case 'a': case 'A': case '4': case 75: // 左
		control->direction = 0; // 向左移动
		horzMoveTetris(manager, control); // 水平移动方块
		break;
	case 'd': case 'D': case '6': case 77: // 右
		control->direction = 1; // 向右移动
		horzMoveTetris(manager, control); // 水平移动方块
		break;
	case 's': case 'S': case '2': case 80: // 下
		moveDownTetris(manager, control); // 向下移动方块
		break;
	case ' ': // 直接落地
		dropDownTetris(manager, control);
		break;
	case '0': // 反转
		control->clockwise = false; // 逆时针旋转
		rotateTetris(manager, control); // 旋转方块
		break;
	default:
		break;
	}
}
void GameControl::runGame(TetrisManager* manager, TetrisControl* control)
{
	clock_t clockLast, clockNow;

	clockLast = clock(); // 计时
	graph_G.printTetrisPool(manager, control); // 显示游戏池

	while (!manager->dead) // 没挂
	{
		while (_kbhit()) // 有键按下
		{
			keydownControl(manager, control, _getch()); // 处理按键
		}

		if (!control->pause) // 未暂停
		{
			clockNow = clock(); // 计时
			// 两次记时的间隔超过0.45秒
			if (clockNow - clockLast > 0.45F * CLOCKS_PER_SEC)
			{
				clockLast = clockNow;
				keydownControl(manager, control, 80); // 方块往下移
			}
		}
	}
}

// =============================================================================
// 再来一次
bool GameControl::ifPlayAgain()
{
	int ch;

	SetConsoleTextAttribute(g_hConsoleOutput, 0xF0);
	logic_G.gotoxyWithFullwidth(15, 10);
	printf("游戏结束");
	logic_G.gotoxyWithFullwidth(13, 11);
	printf("按Y重玩，按N退出");

	do
	{
		ch = _getch();
		if (ch == 'Y' || ch == 'y')
		{
			return true;
		}
		else if (ch == 'N' || ch == 'n')
		{
			return false;
		}
	} while (1);
}