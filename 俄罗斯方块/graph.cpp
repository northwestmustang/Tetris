#include"graph.h"

// =============================================================================
// 设置颜色
void Graph::setPoolColor(const TetrisManager* manager, TetrisControl* control)
{
	// 由于显示游戏池时，先要在游戏池里判断某一方格有方块才显示相应方格的颜色
	// 这里只作设置即可，没必要清除
	// 当移动方块或给一个方块时调用

	int8_t i, x, y;

	// 当前方块
	uint16_t tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

	for (i = 0; i < 16; ++i)
	{
		y = (i >> 2) + manager->y; // 待设置的列
		if (y > ROW_END) // 超过底部限制
		{
			break;
		}
		x = (i & 3) + manager->x; // 待设置的行
		if ((tetris >> i) & 1) // 检测的到小方格属于当前方块区域
		{
			control->color[y][x] = (manager->type[0] | 8); // 设置颜色
		}
	}
}



// =============================================================================
// 显示游戏池边界
void Graph::printPoolBorder()
{
	Logic logic_g;
	int8_t y;

	SetConsoleTextAttribute(g_hConsoleOutput, 0xF0);
	for (y = ROW_BEGIN; y < ROW_END; ++y) // 不显示顶部4行和底部2行
	{
		logic_g.gotoxyWithFullwidth(10, y - 3);
		printf("%2s", "");
		logic_g.gotoxyWithFullwidth(23, y - 3);
		printf("%2s", "");
	}

	logic_g.gotoxyWithFullwidth(10, y - 3); // 底部边界
	printf("%28s", "");
}

// 定位到游戏池中的方格
#define gotoxyInPool(x, y) gotoxyWithFullwidth(x + 9, y - 3)

// =============================================================================
// 显示游戏池
void Graph::printTetrisPool(const TetrisManager* manager, const TetrisControl* control)
{
	Logic logic_g;
	int8_t x, y;

	for (y = ROW_BEGIN; y < ROW_END; ++y) // 不显示顶部4行和底部2行
	{
		logic_g.gotoxyInPool(2, y); // 定点到游戏池中的方格
		for (x = COL_BEGIN; x < COL_END; ++x) // 不显示左右边界
		{
			if ((manager->pool[y] >> x) & 1) // 游戏池该方格有方块
			{
				// 用相应颜色，显示一个实心方块
				SetConsoleTextAttribute(g_hConsoleOutput, control->color[y][x]);
				printf("■");
			}
			else // 没有方块，显示空白
			{
				SetConsoleTextAttribute(g_hConsoleOutput, 0);
				printf("%2s", "");
			}
		}
	}
}

// =============================================================================
// 显示当前方块
void Graph::printCurrentTetris(const TetrisManager* manager, const TetrisControl* control)
{
	Logic logic_g;
	int8_t x, y;

	// 显示当前方块是在移动后调用的，为擦去移动前的方块，需要扩展显示区域
	// 由于不可能向上移动，故不需要向下扩展
	y = (manager->y > ROW_BEGIN) ? (manager->y - 1) : ROW_BEGIN; // 向上扩展一格
	for (; y < ROW_END && y < manager->y + 4; ++y)
	{
		x = (manager->x > COL_BEGIN) ? (manager->x - 1) : COL_BEGIN; // 向左扩展一格
		for (; x < COL_END && x < manager->x + 5; ++x) // 向右扩展一格
		{
			logic_g.gotoxyInPool(x, y); // 定点到游戏池中的方格
			if ((manager->pool[y] >> x) & 1) // 游戏池该方格有方块
			{
				// 用相应颜色，显示一个实心方块
				SetConsoleTextAttribute(g_hConsoleOutput, control->color[y][x]);
				printf("■");
			}
			else // 没有方块，显示空白
			{
				SetConsoleTextAttribute(g_hConsoleOutput, 0);
				printf("%2s", "");
			}
		}
	}
}

// =============================================================================
// 显示下一个和下下一个方块
void Graph::printNextTetris(const TetrisManager* manager)
{
	Logic logic_g;
	int8_t i;
	uint16_t tetris;

	// 边框
	SetConsoleTextAttribute(g_hConsoleOutput, 0xF);
	logic_g.gotoxyWithFullwidth(26, 1);
	printf("┏━━━━┳━━━━┓");
	logic_g.gotoxyWithFullwidth(26, 2);
	printf("┃%8s┃%8s┃", "", "");
	logic_g.gotoxyWithFullwidth(26, 3);
	printf("┃%8s┃%8s┃", "", "");
	logic_g.gotoxyWithFullwidth(26, 4);
	printf("┃%8s┃%8s┃", "", "");
	logic_g.gotoxyWithFullwidth(26, 5);
	printf("┃%8s┃%8s┃", "", "");
	logic_g.gotoxyWithFullwidth(26, 6);
	printf("┗━━━━┻━━━━┛");

	// 下一个，用相应颜色显示
	tetris = gs_uTetrisTable[manager->type[1]][manager->orientation[1]];
	SetConsoleTextAttribute(g_hConsoleOutput, manager->type[1] | 8);
	for (i = 0; i < 16; ++i)
	{
		logic_g.gotoxyWithFullwidth((i & 3) + 27, (i >> 2) + 2);
		((tetris >> i) & 1) ? printf("■") : printf("%2s", "");
	}

	// 下下一个，不显示彩色
	tetris = gs_uTetrisTable[manager->type[2]][manager->orientation[2]];
	SetConsoleTextAttribute(g_hConsoleOutput, 8);
	for (i = 0; i < 16; ++i)
	{
		logic_g.gotoxyWithFullwidth((i & 3) + 32, (i >> 2) + 2);
		((tetris >> i) & 1) ? printf("■") : printf("%2s", "");
	}
}

// =============================================================================
// 显示得分信息
void Graph::printScore(const TetrisManager* manager)
{
	Logic logic_g;
	static const char* tetrisName = "ITLJZSO";
	int8_t i;

	SetConsoleTextAttribute(g_hConsoleOutput, 0xE);

	logic_g.gotoxyWithFullwidth(2, 2);
	printf("■得分：%u", manager->score);

	logic_g.gotoxyWithFullwidth(1, 6);
	printf("■消行总数：%u", manager->erasedTotal);
	for (i = 0; i < 4; ++i)
	{
		logic_g.gotoxyWithFullwidth(2, 8 + i);
		printf("□消%d：%u", i + 1, manager->erasedCount[i]);
	}

	logic_g.gotoxyWithFullwidth(1, 15);
	printf("■方块总数：%u", manager->tetrisTotal);

	for (i = 0; i < 7; ++i)
	{
		logic_g.gotoxyWithFullwidth(2, 17 + i);
		printf("□%c形：%u", tetrisName[i], manager->tetrisCount[i]);
	}
}

// =============================================================================
// 显示提示信息
void Graph::printPrompting()
{
	Logic logic_g;
	SetConsoleTextAttribute(g_hConsoleOutput, 0xB);
	logic_g.gotoxyWithFullwidth(26, 10);
	printf("■控制：");
	logic_g.gotoxyWithFullwidth(27, 12);
	printf("□向左移动：← A 4");
	logic_g.gotoxyWithFullwidth(27, 13);
	printf("□向右移动：→ D 6");
	logic_g.gotoxyWithFullwidth(27, 14);
	printf("□向下移动：↓ S 2");
	logic_g.gotoxyWithFullwidth(27, 15);
	printf("□顺时针转：↑ W 8");
	logic_g.gotoxyWithFullwidth(27, 16);
	printf("□逆时针转：0");
	logic_g.gotoxyWithFullwidth(27, 17);
	printf("□直接落地：空格");
	logic_g.gotoxyWithFullwidth(27, 18);
	printf("□暂停游戏：回车");
	logic_g.gotoxyWithFullwidth(25, 23);
}

