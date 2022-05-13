#include "Logic.h"
void Logic::giveTetris(TetrisManager* manager)
{
	Graph graph_L;
	uint16_t tetris;

	manager->type[0] = manager->type[1]; // 下一个方块置为当前
	manager->orientation[0] = manager->orientation[1];

	manager->type[1] = manager->type[2];// 下下一个置方块为下一个
	manager->orientation[1] = manager->orientation[2];

	manager->type[2] = rand() % 7;// 随机生成下下一个方块
	manager->orientation[2] = rand() & 3;

	tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]]; // 当前方块

	// 设置当前方块y坐标，保证刚给出时只显示方块最下面一行
	// 这种实现使得玩家可以以很快的速度将方块落在不显示出来的顶部4行内
	if (tetris & 0xF000)
	{
		manager->y = 0;
	}
	else
	{
		manager->y = (tetris & 0xFF00) ? 1 : 2;
	}
	manager->x = 6; // 设置当前方块x坐标

	if (checkCollision(manager)) // 检测到碰撞
	{
		manager->dead = true; // 标记游戏结束
	}
	else // 未检测到碰撞
	{
		insertTetris(manager); // 将当前方块加入游戏池
	}

	++manager->tetrisTotal; // 方块总数
	++manager->tetrisCount[manager->type[0]]; // 相应方块数

	graph_L.printNextTetris(manager); // 显示下一个方块
	graph_L.printScore(manager); // 显示得分信息
}

// =============================================================================
// 碰撞检测
bool Logic::checkCollision(const TetrisManager* manager)
{
	// 当前方块
	uint16_t tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];
	uint16_t dest = 0;

	// 获取当前方块在游戏池中的区域：
	// 游戏池坐标x y处小方格信息，按低到高存放在16位无符号数中
	dest |= (((manager->pool[manager->y + 0] >> manager->x) << 0x0) & 0x000F);
	dest |= (((manager->pool[manager->y + 1] >> manager->x) << 0x4) & 0x00F0);
	dest |= (((manager->pool[manager->y + 2] >> manager->x) << 0x8) & 0x0F00);
	dest |= (((manager->pool[manager->y + 3] >> manager->x) << 0xC) & 0xF000);

	// 若当前方块与目标区域存在重叠（碰撞），则位与的结果不为0
	return ((dest & tetris) != 0);
}

// =============================================================================
// 插入方块
void Logic::insertTetris(TetrisManager* manager)
{
	// 当前方块
	uint16_t tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

	// 当前方块每4位取出，位或到游戏池相应位置，即完成插入方块
	manager->pool[manager->y + 0] |= (((tetris >> 0x0) & 0x000F) << manager->x);
	manager->pool[manager->y + 1] |= (((tetris >> 0x4) & 0x000F) << manager->x);
	manager->pool[manager->y + 2] |= (((tetris >> 0x8) & 0x000F) << manager->x);
	manager->pool[manager->y + 3] |= (((tetris >> 0xC) & 0x000F) << manager->x);
}

// =============================================================================
// 移除方块
void Logic::removeTetris(TetrisManager* manager)
{
	// 当前方块
	uint16_t tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

	// 当前方块每4位取出，按位取反后位与到游戏池相应位置，即完成移除方块
	manager->pool[manager->y + 0] &= ~(((tetris >> 0x0) & 0x000F) << manager->x);
	manager->pool[manager->y + 1] &= ~(((tetris >> 0x4) & 0x000F) << manager->x);
	manager->pool[manager->y + 2] &= ~(((tetris >> 0x8) & 0x000F) << manager->x);
	manager->pool[manager->y + 3] &= ~(((tetris >> 0xC) & 0x000F) << manager->x);
}
bool Logic::checkErasing(TetrisManager* manager, TetrisControl* control)
{
	Graph graph_L;
	static const unsigned scores[5] = { 0, 10, 30, 90, 150 }; // 消行得分
	int8_t count = 0;
	int8_t k = 0, y = manager->y + 3; // 从下往上检测

	do
	{
		if (y < ROW_END && manager->pool[y] == 0xFFFFU) // 有效区域内且一行已填满
		{
			++count;
			// 消除一行方块
			memmove(manager->pool + 1, manager->pool, sizeof(uint16_t) * y);
			// 颜色数组的元素随之移动
			memmove(control->color[1], control->color[0], sizeof(int8_t[16]) * y);
		}
		else
		{
			--y;
			++k;
		}
	} while (y >= manager->y && k < 4);

	manager->erasedTotal += count; // 消行总数
	manager->score += scores[count]; // 得分

	if (count > 0)
	{
		++manager->erasedCount[count - 1]; // 消行
	}

	giveTetris(manager); // 给下一个方块
	graph_L.setPoolColor(manager, control); // 设置颜色

	return (count > 0);
}
void Logic::gotoxyWithFullwidth(short x, short y)
{
	static COORD cd;

	cd.X = (short)(x << 1);
	cd.Y = y;
	SetConsoleCursorPosition(g_hConsoleOutput, cd);
}
